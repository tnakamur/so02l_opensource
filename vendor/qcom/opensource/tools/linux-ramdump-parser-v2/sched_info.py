# Copyright (c) 2019, The Linux Foundation. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 and
# only version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

from parser_util import register_parser, RamParser
from print_out import print_out_str

DEFAULT_MIGRATION_NR=32
DEFAULT_MIGRATION_COST=500000

def verify_active_cpus(ramdump):
    core_sib_off = ramdump.field_offset('struct cpu_topology', 'core_sibling')
    cpu_topology_addr = ramdump.address_of('cpu_topology')
    cpu_topology_size = ramdump.sizeof('struct cpu_topology')

    if (ramdump.kernel_version >= (4, 19, 0)):
        cluster_id_off = ramdump.field_offset('struct cpu_topology', 'package_id')
    else:
        cluster_id_off = ramdump.field_offset('struct cpu_topology', 'cluster_id')

    if (ramdump.kernel_version >= (4, 9, 0)):
        cpu_online_bits = ramdump.read_word('__cpu_online_mask')
    else:
        cpu_online_bits = ramdump.read_word('cpu_online_bits')
    if (ramdump.kernel_version >= (4, 9, 0)):
        cpu_isolated_bits = ramdump.read_word('__cpu_isolated_mask')
    elif (ramdump.kernel_version >= (4, 4, 0)):
        cpu_isolated_bits = ramdump.read_word('cpu_isolated_bits')
    else:
        cpu_isolated_bits = 0

    if(cpu_isolated_bits is None): #QCS404/None handling
        cpu_isolated_bits = 0

    nr_cpus = ramdump.get_num_cpus()

    if (cluster_id_off is None):
        print_out_str("\n Invalid cluster topology detected\n")

    # INFO: from 4.19 onwards, core_sibling mask contains only online cpus,
    #       find out cluster cpus dynamically.

    cluster_nrcpus = [0]
    for j in range(0, nr_cpus):
        c_id = ramdump.read_int(cpu_topology_addr + (j * cpu_topology_size) + cluster_id_off)
        if len(cluster_nrcpus) <= c_id :
            cluster_nrcpus.extend([0])
        cluster_nrcpus[c_id] += 1

    next_cluster_cpu = 0
    for i in range(0, len(cluster_nrcpus)):
        cluster_cpus = ramdump.read_word(cpu_topology_addr +
                                        (next_cluster_cpu * cpu_topology_size) + core_sib_off)
        cluster_online_cpus = cpu_online_bits & cluster_cpus
        cluster_nr_oncpus = bin(cluster_online_cpus).count('1')
        cluster_isolated_cpus = cpu_isolated_bits & cluster_cpus
        cluster_nr_isocpus = bin(cluster_isolated_cpus).count('1')

        #print_out_str("Cluster fist cpu {0} cpu_mask {1:b}".format(next_cluster_cpu , cluster_cpus))
        next_cluster_cpu += cluster_nrcpus[i]

        if (cluster_nrcpus[i] > 2):
            min_req_cpus = 2
        else:
            min_req_cpus = 1

        if ((cluster_nr_oncpus - cluster_nr_isocpus) < min_req_cpus):
                print_out_str("\n************ WARNING **************\n")
                print_out_str("\tMinimum active cpus are not available in the cluster {0} \n".format(i))
                print_out_str("\tCluster cpus: {0:b}  Online cpus: {1:b} Isolated cpus: {2:b}\n".format(
                                cluster_cpus, cluster_online_cpus, cluster_isolated_cpus))
                print_out_str("\n***********************************\n")

@register_parser('--sched-info', 'Verify scheduler\'s various parameter status')
class Schedinfo(RamParser):
    def parse(self):
        # Active cpu check verified by default!
        #verify_active_cpus(self.ramdump)

        # verify nr_migrates
        sched_nr_migrate = self.ramdump.read_u32('sysctl_sched_nr_migrate')
        if (sched_nr_migrate != DEFAULT_MIGRATION_NR):
            print_out_str("\n************ WARNING **************\n")
            print_out_str("\t sysctl_sched_nr_migrate has changed!!\n")
            print_out_str("\t If it is single digit, scheduler's load balancer has broken in the dump\n")

        # verify migration cost
        sched_migration_cost = self.ramdump.read_u32('sysctl_sched_migration_cost')
        if (sched_migration_cost != DEFAULT_MIGRATION_COST):
            print_out_str("\n************ WARNING **************\n")
            print_out_str("\t sysctl_sched_migration_cost has changed!!\n")
            print_out_str("\t\tDefault: 500000 and Value in dump:{0}\n".format(sched_migration_cost))

        # verify CFS BANDWIDTH enabled
        cfs_bandwidth_enabled = self.ramdump.read_u32('sysctl_sched_cfs_bandwidth_slice')
        if cfs_bandwidth_enabled is not None:
            print_out_str("\n************ INFORMATION **************\n")
            print_out_str("\tCFS_BANDWIDTH is enabled in the dump!!\n")
            print_out_str("\tBandwidth slice: {0}\n".format(cfs_bandwidth_enabled))
