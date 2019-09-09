/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2014-2019 Inviwo Foundation
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

#include <warn/push>
#include <warn/ignore/all>
#include <gtest/gtest.h>
#include <warn/pop>

#include <inviwo/core/util/indexmapper.h>
#include <inviwo/core/util/indexmapper2.h>

namespace inviwo {

TEST(indexmapper, indexEquivalence2D) {
    util::VectorN<2, size_t> dimensions1{16, 16};
    auto indexMapper1 = util::makeIndexMapperN(dimensions1);
    const auto index1 = indexMapper1({9, 8});

    Vector<2, size_t> dimensions2(16, 16);
    auto indexMapper2 = util::IndexMapper<2, size_t>(dimensions2);
    const auto index2 = indexMapper2(9, 8);

    EXPECT_EQ(index1, index2);
}

TEST(indexmapper, indexEquivalence3D) {
    util::VectorN<3, size_t> dimensions1{16, 16, 16};
    auto indexMapper1 = util::makeIndexMapperN(dimensions1);
    const auto index1 = indexMapper1({9, 8, 7});

    Vector<3, size_t> dimensions2(16, 16, 16);
    auto indexMapper2 = util::IndexMapper<3, size_t>(dimensions2);
    const auto index2 = indexMapper2(9, 8, 7);

    EXPECT_EQ(index1, index2);
}

TEST(indexmapper, posEquivalence2D) {
    util::VectorN<2, size_t> dimensions1{16, 16};
    auto indexMapper1 = util::makeIndexMapperN(dimensions1);
    const auto pos1 = indexMapper1(25);

    Vector<2, size_t> dimensions2(16, 16);
    auto indexMapper2 = util::IndexMapper<2, size_t>(dimensions2);
    const auto pos2 = indexMapper2(25);

    EXPECT_EQ(pos1[0], pos2[0]);
    EXPECT_EQ(pos1[1], pos2[1]);
}

TEST(indexmapper, posEquivalence3D) {
    util::VectorN<3, size_t> dimensions1{16, 16, 16};
    auto indexMapper1 = util::makeIndexMapperN(dimensions1);
    const auto pos1 = indexMapper1(255);

    Vector<3, size_t> dimensions2(16, 16, 16);
    auto indexMapper2 = util::IndexMapper<3, size_t>(dimensions2);
    const auto pos2 = indexMapper2(255);

    EXPECT_EQ(pos1[0], pos2[0]);
    EXPECT_EQ(pos1[1], pos2[1]);
    EXPECT_EQ(pos1[2], pos2[2]);
}

TEST(indexmapper, posEquivalence4D) {
    util::VectorN<4, size_t> dimensions1{16, 16, 16, 16};
    auto indexMapper1 = util::makeIndexMapperN(dimensions1);
    const auto pos1 = indexMapper1(255);

    auto map4D = [](const Vector<4, size_t>& dimensions, const size_t index) -> auto {
        return Vector<4, size_t>{
            index % dimensions.x, (index / dimensions.x) % dimensions.y,
            (index / (dimensions.x * dimensions.y)) % dimensions.z,
            (index / (dimensions.x * dimensions.y * dimensions.z)) % dimensions.w};
    };

    Vector<4, size_t> dimensions2(16, 16, 16, 16);
    
    const auto pos2 = map4D(dimensions2, 255);

    EXPECT_EQ(pos1[0], pos2[0]);
    EXPECT_EQ(pos1[1], pos2[1]);
    EXPECT_EQ(pos1[2], pos2[2]);
    EXPECT_EQ(pos1[3], pos2[3]);
}

}  // namespace inviwo
