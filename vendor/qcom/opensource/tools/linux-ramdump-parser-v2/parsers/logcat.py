# Copyright (c) 2019 The Linux Foundation. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 and
# only version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.


from parser_util import register_parser, RamParser, cleanupString
from mmu import Armv8MMU
from print_out import print_out_str


def parse_locat(ramdump):
    offset_comm = ramdump.field_offset('struct task_struct', 'comm')
    mm_offset = ramdump.field_offset('struct task_struct', 'mm')
    f_path_offset = ramdump.field_offset('struct file', 'f_path')
    dentry_offset = ramdump.field_offset('struct path', 'dentry')
    d_iname_offset = ramdump.field_offset('struct dentry', 'd_iname')

    for task in ramdump.for_each_process():
        task_name = task + offset_comm
        task_name = cleanupString(ramdump.read_cstring(task_name, 16))
        if task_name == 'logd':
            mm_addr = ramdump.read_word(task + mm_offset)
            mmap = ramdump.read_structure_field(mm_addr, 'struct mm_struct',
                                                'mmap')
            pgd = ramdump.read_structure_field(mm_addr, 'struct mm_struct',
                                               'pgd')
            pgdp = ramdump.virt_to_phys(pgd)
            va_start = ramdump.read_structure_field(mmap,
                                    'struct vm_area_struct', 'vm_start')
            max = 0
            count = 0
            while mmap != 0:
                if count == 3:
                    va_start = ramdump.read_structure_field(mmap,
                                        'struct vm_area_struct', 'vm_start')
                    count = count + 1
                file = ramdump.read_structure_field(mmap,
                                        'struct vm_area_struct', 'vm_file')
                if file != 0:
                    dentry = ramdump.read_word(file + f_path_offset +
                                               dentry_offset)
                    file_name = cleanupString(ramdump.read_cstring(dentry +
                                            d_iname_offset, 16))
                    if file_name == "logd":
                        count = count + 1
                    if file_name.find("linker") == 0:
                        va_end = ramdump.read_structure_field(mmap,
                                            'struct vm_area_struct', 'vm_end')
                        if va_end > max:
                            max = va_end
                mmap = ramdump.read_structure_field(mmap, 'struct '
                                                'vm_area_struct', 'vm_next')
            size = max - va_start
            if size > 0x4000000:
                size = 0x4000000
            break
    mmu = Armv8MMU(ramdump,pgdp)
    print_out_str("logcat.bin base address is {0:x}".format(va_start))
    with ramdump.open_file("logcat.bin", 'ab') as out_file:
        max = va_start + size
        while(va_start <= max):
            phys = mmu.virt_to_phys(va_start)
            if phys is None:
                va_start = va_start + 0x1000
                out_file.write(b'\x00' * 0x1000)
                continue
            out_file.write(ramdump.read_physical(phys, 0x1000))
            va_start = va_start + 0x1000
    return


@register_parser('--logcat', 'Extract logcat logs from ramdump ')
class Logcat(RamParser):

    def parse(self):
        parse_locat(self.ramdump)
