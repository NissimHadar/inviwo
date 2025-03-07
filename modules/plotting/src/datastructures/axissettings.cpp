/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2019 Inviwo Foundation
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

#include <modules/plotting/datastructures/axissettings.h>

namespace inviwo {

namespace plot {

bool AxisSettings::isVertical() const { return getOrientation() == Orientation::Vertical; }

bool operator==(const AxisSettings& a, const AxisSettings& b) {
    return a.getCaption() == b.getCaption() && a.getLabels() == b.getLabels() &&
           a.getVisible() == b.getVisible() && a.getFlipped() == b.getFlipped() &&
           a.getColor() == b.getColor() && a.getWidth() == b.getWidth() &&
           a.getUseDataRange() == b.getUseDataRange() && a.getRange() == b.getRange() &&
           a.getOrientation() == b.getOrientation() && a.getPlacement() == b.getPlacement() &&
           a.getCaptionSettings() == b.getCaptionSettings() &&
           a.getLabelSettings() == b.getLabelSettings() && a.getMajorTicks() == b.getMajorTicks() &&
           a.getMinorTicks() == b.getMinorTicks();
}

bool operator!=(const AxisSettings& a, const AxisSettings& b) { return !(a == b); }

}  // namespace plot

}  // namespace inviwo
