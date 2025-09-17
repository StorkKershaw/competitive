set shell := ["pwsh", "-NoProfile", "-Command", "$ProgressPreference='SilentlyContinue';"]
set dotenv-load := false

include := 'include'
build := 'build'

[private]
@default: help

# show help message
@help:
    Write-Output 'Usage: just <recipe>'
    just --list

# initialize environment
@init:
    Remove-Item -Path {{include}} -Recurse -Force | Out-Null
    New-Item -Path {{include}} -ItemType Directory -Force | Out-Null
    git clone --branch 'master' --no-progress 'https://github.com/atcoder/ac-library.git' 'downloads/ac-library' | Out-Null
    Copy-Item -Path 'downloads/ac-library/atcoder' -Destination {{include}} -Recurse -Force
    Remove-Item -Path 'downloads' -Recurse -Force | Out-Null

    Remove-Item -Path {{build}} -Recurse -Force | Out-Null
    New-Item -Path {{build}} -ItemType Directory -Force | Out-Null
    Copy-Item -Path 'templates/header.cpp' -Destination 'main.cpp' -Force | Out-Null
    cmake -B {{build}} -S . -DCMAKE_BUILD_TYPE=Debug -G 'MinGW Makefiles' -DCMAKE_CXX_STANDARD=20 -DCMAKE_CXX_STANDARD_REQUIRED=ON
    pip install --disable-pip-version-check --upgrade online-judge-tools

alias d := download
# download problem
@download problem_url:
    Remove-Item -Path 'test' -Recurse -Force | Out-Null
    oj download {{problem_url}}

alias t := test
# build and test main.cpp
@test:
    cmake --build {{build}}
    -oj test

# update templates
@update:
    git add .
    git commit -m 'update templates'
    git push
