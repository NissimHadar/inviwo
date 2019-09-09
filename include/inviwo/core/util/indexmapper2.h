/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2015-2019 Inviwo Foundation
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

#ifndef IVW_IndexMapperN2_H
#define IVW_IndexMapperN2_H

#include <array>
#include <iostream>
#include <type_traits>
#include <algorithm>
#include <numeric>

namespace inviwo {
namespace util {
template <size_t N, typename T>
struct VectorN {
    constexpr VectorN() = default;
    constexpr VectorN(std::initializer_list<T> l);
    constexpr VectorN(std::array<T, N> a);
    constexpr VectorN(const VectorN<N + 1, T>& vec) {
        data_ = std::array<T, N>{};
        std::copy(vec.data().begin(), vec.data().begin() + N, data_.begin());
    }                                                      // Copy and reduction constructor
    constexpr VectorN(const VectorN<N - 1, T>& vec, T v);  // Expansion constructor

    ~VectorN() = default;

    const auto& data() const { return data_; }
    constexpr auto size() const { return data_.size(); }
    constexpr T operator[](const size_t index) const { return data_[index]; }
    constexpr T prod() const {
        T prod{1};
        for (size_t i{0}; i < N; ++i) {
            prod *= data_[i];
        }
        return prod;
    }

	void set(size_t i, T t) { data_[i] = t; }

private:
    std::array<T, N> data_;
};

template <size_t N, typename T>
constexpr VectorN<N, T>::VectorN(std::initializer_list<T> l) {
    std::copy(l.begin(), l.end(), data_.begin());
}

template <size_t N, typename T>
constexpr VectorN<N, T>::VectorN(std::array<T, N> a) : data_(std::move(a)) {}

// Expansion constructor
template <size_t N, typename T>
constexpr VectorN<N, T>::VectorN(const VectorN<N - 1, T>& vec, T v) : data_({}) {
    std::copy(vec.data().begin(), vec.data().end(), data_.begin());
    data_[N - 1] = v;
}

template <size_t N, typename IndexType>
struct IndexMapperN {
    constexpr IndexMapperN() = delete;
    constexpr IndexMapperN(const VectorN<N, IndexType>& dim) : dimensions_(dim) {
        for (size_t i{0}; i < N; ++i) {  // Generate coefficients
            IndexType coeff{1};
            for (size_t j{0}; j < N - i - 1; ++j) {
                coeff *= dimensions_[j];
            }
            coeffArray_[i] = coeff;
        }

        std::reverse(std::begin(coeffArray_),
                     std::end(coeffArray_));  // Reverse so we can simply compute the inner product
                                              // of the coefficient array and the position array.
    };

    constexpr IndexType operator()(const VectorN<N, IndexType>& pos) const noexcept {
        const auto& posArray = pos.data();
        return std::inner_product(std::cbegin(coeffArray_), std::cend(coeffArray_),
                                  std::cbegin(posArray), 0);
    }

    constexpr VectorN<N, IndexType> operator()(IndexType i);

private:
    VectorN<N, IndexType> dimensions_;
    std::array<IndexType, N> coeffArray_;
};

template <size_t N, typename IndexType>
auto makeIndexMapperN(const VectorN<N, IndexType>& dim) {
    return IndexMapperN<N, IndexType>(dim);
}

namespace detail {
// Needed to put this here because otherwise the template arguments were conflicting
 template <size_t N, typename IndexType>
 constexpr VectorN<N, IndexType> getPosFromIndex(IndexType i, const VectorN<N, IndexType>& d) {
    if constexpr (N <= 1)
        return VectorN<1, IndexType>{i};
    else {
        constexpr auto L2 = N - 1;
        return VectorN<N, IndexType>(
            getPosFromIndex<L2, IndexType>(i % d[L2], VectorN<L2, IndexType>(d)),
            i / d[L2]);
    }
}

template <size_t N, typename IndexType>
constexpr VectorN<N, IndexType> getPosFromIndex2(IndexType i, const VectorN<N, IndexType>& d) {
    VectorN<N, IndexType> result;
    IndexType prod{1};
    constexpr auto L2 = N - 1;

    for (size_t j{0}; j < N; ++j) {
        result.set(j,(i / prod) % d[L2]);
        prod *= d[L2 - 1];
    }

	return result;
}

}  // namespace detail

template <size_t N, typename IndexType>
constexpr VectorN<N, IndexType> IndexMapperN<N, IndexType>::operator()(const IndexType i) {
    return detail::getPosFromIndex2<N, IndexType>(i, dimensions_);
}

using IndexMapper2DN = IndexMapperN<2, size_t>;
using IndexMapper3DN = IndexMapperN<3, size_t>;
using IndexMapper4DN = IndexMapperN<4, size_t>;

}  // namespace util
}  // namespace inviwo

#endif  // IVW_IndexMapperN2_H
