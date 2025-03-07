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

#ifndef IVW_BUILDINFO_H
#define IVW_BUILDINFO_H

#include <inviwo/core/common/inviwocoredefine.h>
#include <inviwo/core/common/inviwo.h>

#include <vector>
#include <utility>
#include <string>

namespace inviwo {

namespace util {

/**
 * \struct BuildInfo
 * \brief Provides information on build time and date as well as git hashes
 */
struct IVW_CORE_API BuildInfo {
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;

    std::vector<std::pair<std::string, std::string>> githashes;

#ifdef CMAKE_BUILD_TYPE
    std::string configuration = CMAKE_BUILD_TYPE;
#else
    std::string configuration = "Unknown";
#endif

#ifdef CMAKE_GENERATOR
    std::string generator = CMAKE_GENERATOR;
#else
    std::string generator = "Unknown";
#endif

#ifdef CMAKE_CXX_COMPILER_ID
    std::string compiler = CMAKE_CXX_COMPILER_ID;
#else
    std::string compiler = "Unknown";
#endif

#ifdef CMAKE_CXX_COMPILER_VERSION
    std::string compilerVersion = CMAKE_CXX_COMPILER_VERSION;
#else
    std::string compilerVersion = "Unknown";
#endif

    std::string getDate() const {
        std::stringstream ss;
        ss << year << "-" << std::setfill('0') << std::setw(2) << month << "-" << std::setfill('0')
           << std::setw(2) << day << " " << std::setfill('0') << std::setw(2) << hour << ":"
           << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0')
           << std::setw(2) << second;
        return ss.str();
    }
};

/**
 * \brief Accesses build information via an INI file or compile-time definitions
 *
 * @return build information
 */
BuildInfo IVW_CORE_API getBuildInfo();

}  // namespace util

}  // namespace inviwo

#endif  // IVW_BUILDINFO_H
