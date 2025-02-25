<h1 align="center">Matrix</h1>

## Description

 Implementation of the matrix.

## How to integrate
 
 use [storage](https://github.com/baitim/ConanPackages), project = "matrix", version = "1.0", user = "baitim"

## Requirements

* Cmake >= 3.30
* Conan >= 2.12

## How to run

1. Clone <br>
    <code>git clone https://github.com/baitim/Matrix.git</code>

2. Go to folder <br>
    <code>cd Matrix</code>

3. Prepare conan <br>
    <code>uv sync --group dev; source .venv/bin/activate</code><br>
    <code>conan profile detect --force</code>

4. Init dependencies <br>
    <code>conan install . --build=missing -s compiler.cppstd=gnu20</code><br>
    maybe you will need these flags for the conan <code>-s build_type=Debug</code>

5. Build <br>
    <code>cmake --preset release</code><br>
    <code>cmake --build build/Release</code>

6. Run <br>
    <code>./build/Release/src/matrix</code>

## How to test

* Testing
    - End to end & Unit<br>
        <code>ctest --test-dir build/Release --output-on-failure</code>

<p align="center"><img src="https://github.com/baitim/Matrix/blob/main/images/cat.gif" width="40%"></p>

## Support
**This project is created by [baitim](https://t.me/bai_tim)**