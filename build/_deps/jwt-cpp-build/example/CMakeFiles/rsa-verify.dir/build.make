# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/leandro/Área de Trabalho/BitFakeCoin"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/leandro/Área de Trabalho/BitFakeCoin/build"

# Include any dependencies generated for this target.
include _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/flags.make

_deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/rsa-verify.cpp.o: _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/flags.make
_deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/rsa-verify.cpp.o: _deps/jwt-cpp-src/example/rsa-verify.cpp
_deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/rsa-verify.cpp.o: _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/leandro/Área de Trabalho/BitFakeCoin/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/rsa-verify.cpp.o"
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build/example" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/rsa-verify.cpp.o -MF CMakeFiles/rsa-verify.dir/rsa-verify.cpp.o.d -o CMakeFiles/rsa-verify.dir/rsa-verify.cpp.o -c "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-src/example/rsa-verify.cpp"

_deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/rsa-verify.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rsa-verify.dir/rsa-verify.cpp.i"
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build/example" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-src/example/rsa-verify.cpp" > CMakeFiles/rsa-verify.dir/rsa-verify.cpp.i

_deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/rsa-verify.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rsa-verify.dir/rsa-verify.cpp.s"
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build/example" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-src/example/rsa-verify.cpp" -o CMakeFiles/rsa-verify.dir/rsa-verify.cpp.s

# Object files for target rsa-verify
rsa__verify_OBJECTS = \
"CMakeFiles/rsa-verify.dir/rsa-verify.cpp.o"

# External object files for target rsa-verify
rsa__verify_EXTERNAL_OBJECTS =

_deps/jwt-cpp-build/example/rsa-verify: _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/rsa-verify.cpp.o
_deps/jwt-cpp-build/example/rsa-verify: _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/build.make
_deps/jwt-cpp-build/example/rsa-verify: /usr/lib/x86_64-linux-gnu/libssl.so
_deps/jwt-cpp-build/example/rsa-verify: /usr/lib/x86_64-linux-gnu/libcrypto.so
_deps/jwt-cpp-build/example/rsa-verify: _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/leandro/Área de Trabalho/BitFakeCoin/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rsa-verify"
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build/example" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rsa-verify.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/build: _deps/jwt-cpp-build/example/rsa-verify
.PHONY : _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/build

_deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/clean:
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build/example" && $(CMAKE_COMMAND) -P CMakeFiles/rsa-verify.dir/cmake_clean.cmake
.PHONY : _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/clean

_deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/depend:
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/leandro/Área de Trabalho/BitFakeCoin" "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-src/example" "/home/leandro/Área de Trabalho/BitFakeCoin/build" "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build/example" "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : _deps/jwt-cpp-build/example/CMakeFiles/rsa-verify.dir/depend

