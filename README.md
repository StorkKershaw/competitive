# competitive

A competitive programming environment setup for Windows.

## Prerequisites

- PowerShell 7
  - `$ winget install --id Microsoft.Powershell --exact --source winget`
- Git for Windows
  - `$ winget install --id Git.Git --exact --source winget`
- CMake
  - `$ winget install --id Kitware.CMake --exact --source winget`
- Just
  - `$ winget install --id Casey.Just --exact --source winget`
- Python (for online-judge-tools)
  - `$ winget install --id Python.Python.3.11 --exact --source winget`

## Help

```shell
$ just help
Usage: just <recipe>
Available recipes:
    download problem_url # download problem [alias: d]
    help                 # show help message
    init                 # initialize environment
    test                 # build and test main.cpp [alias: t]
    update               # update templates
```

## Setup

```shell
$ just init
```

## Download test cases

```shell
$ just download <Problem URL>
# e.g. just download https://atcoder.jp/contests/abc421/tasks/abc421_d
```

## Run tests

```shell
$ just test
```
