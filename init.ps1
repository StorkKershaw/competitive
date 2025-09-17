param(
    [Parameter(Mandatory = $false)]
    [string]
    $IncludeDirectory = 'include',
    [Parameter(Mandatory = $false)]
    [string]
    $BuildDirectory = 'build'
)

if (Test-Path -Path $IncludeDirectory) {
    Remove-Item -Path $IncludeDirectory -Recurse -Force | Out-Null
}
New-Item -ItemType Directory -Path $IncludeDirectory -Force | Out-Null
$TempDirectory = [System.IO.Path]::Join($env:TEMP, 'ac-library')
git.exe clone --branch 'master' 'https://github.com/atcoder/ac-library.git' $TempDirectory
Copy-Item -Path "$TempDirectory\atcoder" -Destination $IncludeDirectory -Recurse -Force
Remove-Item -Recurse -Force $TempDirectory

if (Test-Path -Path $BuildDirectory) {
    Remove-Item -Path $BuildDirectory -Recurse -Force | Out-Null
}
New-Item -ItemType Directory -Path $BuildDirectory -Force | Out-Null
Copy-Item -Path 'template/header.cpp' -Destination 'main.cpp'
cmake.exe -B $BuildDirectory -S . -DCMAKE_BUILD_TYPE=Debug -G 'MinGW Makefiles' -DCMAKE_CXX_STANDARD=20 -DCMAKE_CXX_STANDARD_REQUIRED=ON
pip.exe install 'git+ssh://git@github.com/StorkKershaw/oj.git'
