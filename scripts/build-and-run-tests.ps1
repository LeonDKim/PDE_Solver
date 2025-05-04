$Build="build"

cmake -S . -B $Build
cmake --build $Build

Set-Location $Build
ctest --output-on-failure
Set-Location ..