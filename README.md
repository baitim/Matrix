<h1 align="center">Matrix</h1>

## Description

 Implementation of the matrix.

## How to run

1. Clone <br>
    <code>git clone https://github.com/baitim/Matrix.git</code>

2. Go to folder <br>
    <code>cd Matrix</code>

3. Prepare conan <br>
    <code>conan profile detect --force</code>

4. Init dependencies <br>
    <code>conan install . --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True -s compiler.cppstd=gnu20</code> <br>
    maybe you will need these flags for the conan <code>-s build_type=Debug</code>

5. Build <br>
    <code>cmake . -B build -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake; cmake --build build</code>

6. Run <br>
    <code>./build/src/matrix</code>

## How to test

* Testing
    - End to end & Unit<br>
        <code>ctest --test-dir build --output-on-failure</code>

<p align="center"><img src="https://github.com/baitim/Matrix/blob/main/images/cat.gif" width="40%"></p>

## Support
**This project is created by [baitim](https://t.me/bai_tim)**