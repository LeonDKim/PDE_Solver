$Build="build"
if (-not (Test-Path -Path $Build)) {
    New-Item -ItemType Directory -Path $Build
}

Set-Location .\build
cmake ..
cmake --build .

.\bin\Debug\PDE_SOLVER.exe
Set-Location ..