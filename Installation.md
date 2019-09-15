## Inviwo - Interactive Visualization Workshop
### Installation
#### Prerequisites
##### Visual Studio
Tested with VS 2017
##### Qt
Tested with version 5.13.1
Assuming Qt will be installed to C:\Qt:
1.  Select the OpenSource installer from `<https://www.qt.io/download>`
1.  Run installer
1.  Select 5.13.1->MSVC2017 64-bit  

After installation:
1.  Add environment variable `CMAKE_PREFIX_PATH` and set to `C:\Qt\5.13.1\msvc2017_64\lib\cmake` (needed by CMake)
1.  Add `D:\Qt\5.13.1\msvc2017_64\lib\cmake` to the Windows PATH (Needed to find DLL's when running)

##### git
Latest version
##### CMake
Latest version
#### Cloning repo
`git clone <https://github.com/NissimHadar/inviwo.git>`
`cd unviwo`
`git submodule sync --recursive` (very quick)
`git submodule update --init --recursive` (takes some time)
#### Make
Create `build` folder outside of inviwo folder.
(Assuming build is next to inviwo folder) 'Cmake ..\build -G "Visual Studio 15 Win64"
#### Build
Select `build\inviwo-projects.sln`. All four configurations can be built with no warnings or errors.