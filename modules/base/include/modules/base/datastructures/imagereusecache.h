/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2017-2019 Inviwo Foundation
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

#ifndef IVW_BASE_DATASTRUCTUES_IMAGECACHE_H
#define IVW_BASE_DATASTRUCTUES_IMAGECACHE_H

#include <modules/base/basemoduledefine.h>
#include <inviwo/core/common/inviwo.h>

#include <inviwo/core/datastructures/image/image.h>
#include <inviwo/core/datastructures/image/layer.h>
#include <inviwo/core/datastructures/image/layerram.h>
#include <inviwo/core/datastructures/image/layerramprecision.h>

namespace inviwo {

class IVW_MODULE_BASE_API ImageReuseCache {
public:
    ImageReuseCache() = default;

    std::shared_ptr<Image> getUnused();

    template <typename T>
    std::pair<std::shared_ptr<Image>, LayerRAMPrecision<T>*> getTypedUnused(const size2_t& dim);
    void add(std::shared_ptr<Image> image);

private:
    std::vector<std::shared_ptr<Image>> imageCache_;
};

template <typename T>
std::pair<std::shared_ptr<Image>, LayerRAMPrecision<T>*> ImageReuseCache::getTypedUnused(
    const size2_t& dim) {

    std::pair<std::shared_ptr<Image>, LayerRAMPrecision<T>*> res;

    auto reuse = getUnused();

    if (reuse && reuse->getDataFormat() == DataFormat<T>::get() && reuse->getDimensions() == dim) {
        res.first = reuse;
        res.second = static_cast<LayerRAMPrecision<T>*>(
            reuse->getColorLayer()->getEditableRepresentation<LayerRAM>());
    } else {
        auto sDstRepr = std::make_shared<LayerRAMPrecision<T>>(dim);
        auto dstLayer = std::make_shared<Layer>(sDstRepr);
        res.second = sDstRepr.get();
        res.first = std::make_shared<Image>(dstLayer);
    }
    return res;
}

}  // namespace inviwo

#endif  // IVW_BASE_DATASTRUCTUES_IMAGECACHE_H
