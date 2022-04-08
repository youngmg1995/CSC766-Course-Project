# CSC766-Project

## step 1: install emsdk

```
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

verify your installation is correct
```
emcc -v
cd upstream/emscripten
tests/runner test_loop
```

## step 2: download this repo and run example

```
git clone https://github.ncsu.edu/mgyoung/CSC766-Project
cd examples/example_simd
make comp
make run
cd ../example_pthread
make comp
make run
make comp2
make run
```

## Tree Transformations

Here is some info on how to install, build, and run each of the projects (directories) in the tree-transformations folder.

### Installation

No installation is required for the [baseline](tree-transformation/baseline/) project once the files are downloaded. 

The [mu](tree-transformation/multi-threading/) project, however, requires installation of the [nlohmann_json](https://github.com/nlohmann/json) C++ package. To install, follow the directions in the package repo to install the library through your chosen package manager (Ex: I installed it using homebrew for my Mac). Once this is done, no other installation is required, as the package is automatically linked into the project build through make using the `pkg-config nlohmann_json --cflags` command.

### Building

Each project and its subcomponents can be built using variations of the `make build` by appending the compilation target and the desired test to be run. If building a web target (Ex: web-wasm), you will need to start the emsdk environment prior to running the build command. To install emsdk, see the instructions above. To start the environment for the compiler, run the below command (replacing "~" with the directory that contains the emsdk project):

```bash
source ~/emsdk/emsdk_env.sh
```

There are currently 5 different compilation targets, described below:

- _native-c_: Compiles the code into binary that is intended to be run natively.
- _native-js_: Compiles into javascript that is intended to be run natively through nodejs.
- _native-wasm_: Compiles into javascript and WASM that is intended to be run natively through nodejs.
- _web-js_: Compiles into html and javascript that is intended to be run in the browser.
- _web-wasm_: Compiles into html, javascript, and WASM that is intended to be run in the browser.

Additionally, there are two subcomponents of each project that can be built seperately or together. These subcomponents include the following:

- _test_: Meant to serve as unit tests for the project. Main for this can be found in the "src/test/tests.cpp" file.
- _exp_: This is the actual tool run to capture data for the experiments. Namely, it run the tree-transformations for each of the provided tree files. Main for this can be found in the "src/test/tests.cpp" file.

Below are a few examples for building the projects for reference:

- Building everything in project (so both test and exp, and for all compilation targets native-c, native-js, web-wasm, etc.):

    ```bash
    make build
    ```

- Building both test and exp for only the native-c target in the project:

    ```bash
    make build-native-c
    ```

- Building just the exp executable for the WASM browser target:

    ```bash
    make build-web-wasm-exp
    ```

### Usage

For the executables intended to be run natively, these can be run using the `make run` command, appending the compilation target and test tool according to the same format shwon above when building. Note that this command will also re-build the executables and their object files if they have changed (i.e. it runs the associated build command). Also note that the native-js and native-wasm commands run through nodejs and supply the necessary parameters.

Below are a few examples of running the native tools using these make commands:

- Running the unit tests for the native-js:

    ```bash
    make run-native-js-test
    ```

- Running the experiments for the native-c:

    ```bash
    make run-native-c-exp
    ```

For the executables intended to be run in the browser, one must first start up the provided python server using the below command:

```bash
python3 wasm-server.py
```

This will start up a server for accessing and running files in the browser at [http://localhost:8000](http://localhost:8000). Opening this page in the browser will show a file directory in which the user can navigate to the desired executable that needs to be run. These executables are located in the "/bin" directory and under the sub-directory with the targets name (Ex: web-wasm). The files that should be opened/run are either "test.html" or "exp.html" for their associated tests.