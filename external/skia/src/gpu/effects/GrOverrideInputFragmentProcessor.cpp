/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**************************************************************************************************
 *** This file was autogenerated from GrOverrideInputFragmentProcessor.fp; do not modify.
 *** NOTE: This was generated in origin/master and cherry-picked to android/next-release.
 *** The .fp file that generated it relies on SkSL .fp features that are not present in
 *** in android/next-release and thus were not cherry-picked.
 **************************************************************************************************/
#include "GrOverrideInputFragmentProcessor.h"
#include "glsl/GrGLSLFragmentProcessor.h"
#include "glsl/GrGLSLFragmentShaderBuilder.h"
#include "glsl/GrGLSLProgramBuilder.h"
#include "GrTexture.h"
#include "SkSLCPP.h"
#include "SkSLUtil.h"
class GrGLSLOverrideInputFragmentProcessor : public GrGLSLFragmentProcessor {
public:
    GrGLSLOverrideInputFragmentProcessor() {}
    void emitCode(EmitArgs& args) override {
        GrGLSLFPFragmentBuilder* fragBuilder = args.fFragBuilder;
        const GrOverrideInputFragmentProcessor& _outer =
                args.fFp.cast<GrOverrideInputFragmentProcessor>();
        (void)_outer;
        auto useUniform = _outer.useUniform;
        (void)useUniform;
        auto uniformColor = _outer.uniformColor;
        (void)uniformColor;
        auto literalColor = _outer.literalColor;
        (void)literalColor;
        if (useUniform) {
            uniformColorVar = args.fUniformHandler->addUniform(kFragment_GrShaderFlag,
                                                               kHalf4_GrSLType, "uniformColor");
        }
        fragBuilder->codeAppendf(
                "half4 constColor;\n@if (%s) {\n    constColor = %s;\n} else {\n    constColor = "
                "half4(%f, %f, %f, %f);\n}",
                (_outer.useUniform ? "true" : "false"),
                uniformColorVar.isValid() ? args.fUniformHandler->getUniformCStr(uniformColorVar)
                                          : "half4(0)",
                _outer.literalColor.fR, _outer.literalColor.fG, _outer.literalColor.fB,
                _outer.literalColor.fA);
        SkString _input0("constColor");
        SkString _child0("_child0");
        this->emitChild(_outer.fp_index, _input0.c_str(), &_child0, args);
        fragBuilder->codeAppendf("\n%s = %s;\n", args.fOutputColor, _child0.c_str());
    }

private:
    void onSetData(const GrGLSLProgramDataManager& pdman,
                   const GrFragmentProcessor& _proc) override {
        const GrOverrideInputFragmentProcessor& _outer =
                _proc.cast<GrOverrideInputFragmentProcessor>();
        {
            if (uniformColorVar.isValid()) {
                pdman.set4fv(uniformColorVar, 1, (_outer.uniformColor).vec());
            }
        }
    }
    UniformHandle uniformColorVar;
};
GrGLSLFragmentProcessor* GrOverrideInputFragmentProcessor::onCreateGLSLInstance() const {
    return new GrGLSLOverrideInputFragmentProcessor();
}
void GrOverrideInputFragmentProcessor::onGetGLSLProcessorKey(const GrShaderCaps& caps,
                                                             GrProcessorKeyBuilder* b) const {
    b->add32((int32_t)useUniform);
    if (!useUniform) {
        uint16_t red = SkFloatToHalf(literalColor.fR);
        uint16_t green = SkFloatToHalf(literalColor.fG);
        uint16_t blue = SkFloatToHalf(literalColor.fB);
        uint16_t alpha = SkFloatToHalf(literalColor.fA);
        b->add32(((uint32_t)red << 16) | green);
        b->add32(((uint32_t)blue << 16) | alpha);
    }
}
bool GrOverrideInputFragmentProcessor::onIsEqual(const GrFragmentProcessor& other) const {
    const GrOverrideInputFragmentProcessor& that = other.cast<GrOverrideInputFragmentProcessor>();
    (void)that;
    if (useUniform != that.useUniform) return false;
    if (uniformColor != that.uniformColor) return false;
    if (literalColor != that.literalColor) return false;
    return true;
}
GrOverrideInputFragmentProcessor::GrOverrideInputFragmentProcessor(
        const GrOverrideInputFragmentProcessor& src)
        : INHERITED(kGrOverrideInputFragmentProcessor_ClassID, src.optimizationFlags())
        , fp_index(src.fp_index)
        , useUniform(src.useUniform)
        , uniformColor(src.uniformColor)
        , literalColor(src.literalColor) {
    this->registerChildProcessor(src.childProcessor(fp_index).clone());
}
std::unique_ptr<GrFragmentProcessor> GrOverrideInputFragmentProcessor::clone() const {
    return std::unique_ptr<GrFragmentProcessor>(new GrOverrideInputFragmentProcessor(*this));
}
