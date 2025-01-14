/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2016-2019 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#ifndef IVW_SCATTERPLOTGL_H
#define IVW_SCATTERPLOTGL_H

#include <modules/plottinggl/plottingglmoduledefine.h>
#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/datastructures/transferfunction.h>
#include <inviwo/core/datastructures/buffer/buffer.h>
#include <inviwo/core/interaction/pickingmapper.h>
#include <inviwo/core/properties/transferfunctionproperty.h>
#include <inviwo/core/ports/imageport.h>
#include <modules/opengl/texture/textureutils.h>
#include <modules/opengl/shader/shader.h>
#include <modules/base/algorithm/dataminmax.h>

#include <inviwo/dataframe/datastructures/dataframe.h>
#include <modules/plotting/properties/marginproperty.h>
#include <modules/plotting/properties/axisproperty.h>
#include <modules/plotting/properties/axisstyleproperty.h>

#include <modules/plottinggl/utils/axisrenderer.h>

namespace inviwo {

class Processor;
class PickingEvent;
class BufferObjectArray;

namespace plot {

class IVW_MODULE_PLOTTINGGL_API ScatterPlotGL {
public:
    class Properties : public CompositeProperty {
    public:
        virtual std::string getClassIdentifier() const override;
        static const std::string classIdentifier;

        Properties(std::string identifier, std::string displayName,
                   InvalidationLevel invalidationLevel = InvalidationLevel::InvalidResources,
                   PropertySemantics semantics = PropertySemantics::Default);

        Properties(const Properties &rhs);
        virtual Properties *clone() const override;
        virtual ~Properties() = default;

        BoolProperty useCircle_;
        FloatProperty radiusRange_;
        FloatProperty minRadius_;
        TransferFunctionProperty tf_;
        FloatVec4Property color_;
        FloatVec4Property hoverColor_;
        MarginProperty margins_;
        FloatProperty axisMargin_;

        FloatProperty borderWidth_;
        FloatVec4Property borderColor_;

        BoolProperty hovering_;

        AxisStyleProperty axisStyle_;
        AxisProperty xAxis_;
        AxisProperty yAxis_;

    private:
        auto props() {
            return std::tie(radiusRange_, useCircle_, minRadius_, tf_, color_, hoverColor_,
                            margins_, axisMargin_, borderWidth_, borderColor_, hovering_,
                            axisStyle_, xAxis_, yAxis_);
        }
        auto props() const {
            return std::tie(radiusRange_, useCircle_, minRadius_, tf_, color_, hoverColor_,
                            margins_, axisMargin_, borderWidth_, borderColor_, hovering_,
                            axisStyle_, xAxis_, yAxis_);
        }
    };

    explicit ScatterPlotGL(Processor *processor = nullptr);
    virtual ~ScatterPlotGL() = default;

    void plot(Image &dest, IndexBuffer *indices = nullptr, bool useAxisRanges = false);
    void plot(Image &dest, const Image &src, IndexBuffer *indices = nullptr,
              bool useAxisRanges = false);
    void plot(ImageOutport &dest, IndexBuffer *indices = nullptr, bool useAxisRanges = false);
    void plot(ImageOutport &dest, ImageInport &src, IndexBuffer *indices = nullptr,
              bool useAxisRanges = false);
    void plot(const ivec2 &start, const ivec2 &size, IndexBuffer *indices = nullptr,
              bool useAxisRanges = false);

    void setXAxisLabel(const std::string &label);

    void setYAxisLabel(const std::string &label);

    void setXAxis(std::shared_ptr<const Column> col);

    void setYAxis(std::shared_ptr<const Column> col);

    void setXAxisData(std::shared_ptr<const BufferBase> buffer);
    void setYAxisData(std::shared_ptr<const BufferBase> buffer);
    void setColorData(std::shared_ptr<const BufferBase> buffer);
    void setRadiusData(std::shared_ptr<const BufferBase> buffer);
    void setIndexColumn(std::shared_ptr<const TemplateColumn<uint32_t>> indexcol);

    Properties properties_;
    Shader shader_;

protected:
    void plot(const size2_t &dims, IndexBuffer *indices, bool useAxisRanges);
    void renderAxis(const size2_t &dims);

    void objectPicked(PickingEvent *p);
    uint32_t getGlobalPickId(uint32_t localIndex) const;

    std::shared_ptr<const BufferBase> xAxis_;
    std::shared_ptr<const BufferBase> yAxis_;
    std::shared_ptr<const BufferBase> color_;
    std::shared_ptr<const BufferBase> radius_;
    std::shared_ptr<const TemplateColumn<uint32_t>> indexColumn_;

    std::shared_ptr<BufferBase> pickIds_;

    vec2 minmaxX_;
    vec2 minmaxY_;
    vec2 minmaxC_;
    vec2 minmaxR_;

    std::array<AxisRenderer, 2> axisRenderers_;

    PickingMapper picking_;
    std::set<uint32_t> hoveredIndices_;

    std::unique_ptr<IndexBuffer> indices_;
    std::unique_ptr<BufferObjectArray> boa_;

    Processor *processor_;
};

}  // namespace plot

}  // namespace inviwo

#endif  // IVW_SCATTERPLOT_H
