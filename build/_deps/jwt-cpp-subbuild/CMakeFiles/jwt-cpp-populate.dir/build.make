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
CMAKE_SOURCE_DIR = "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild"

# Utility rule file for jwt-cpp-populate.

# Include any custom commands dependencies for this target.
include CMakeFiles/jwt-cpp-populate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/jwt-cpp-populate.dir/progress.make

CMakeFiles/jwt-cpp-populate: CMakeFiles/jwt-cpp-populate-complete

CMakeFiles/jwt-cpp-populate-complete: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-install
CMakeFiles/jwt-cpp-populate-complete: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-mkdir
CMakeFiles/jwt-cpp-populate-complete: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-download
CMakeFiles/jwt-cpp-populate-complete: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-update
CMakeFiles/jwt-cpp-populate-complete: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-patch
CMakeFiles/jwt-cpp-populate-complete: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-configure
CMakeFiles/jwt-cpp-populate-complete: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-build
CMakeFiles/jwt-cpp-populate-complete: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-install
CMakeFiles/jwt-cpp-populate-complete: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Completed 'jwt-cpp-populate'"
	/usr/bin/cmake -E make_directory "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/CMakeFiles"
	/usr/bin/cmake -E touch "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/CMakeFiles/jwt-cpp-populate-complete"
	/usr/bin/cmake -E touch "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-done"

jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-update:
.PHONY : jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-update

jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-build: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'jwt-cpp-populate'"
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build" && /usr/bin/cmake -E echo_append
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build" && /usr/bin/cmake -E touch "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-build"

jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-configure: jwt-cpp-populate-prefix/tmp/jwt-cpp-populate-cfgcmd.txt
jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-configure: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'jwt-cpp-populate'"
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build" && /usr/bin/cmake -E echo_append
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build" && /usr/bin/cmake -E touch "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-configure"

jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-download: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-gitinfo.txt
jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-download: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'jwt-cpp-populate'"
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps" && /usr/bin/cmake -P "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/tmp/jwt-cpp-populate-gitclone.cmake"
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps" && /usr/bin/cmake -E touch "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-download"

jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-install: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'jwt-cpp-populate'"
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build" && /usr/bin/cmake -E echo_append
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build" && /usr/bin/cmake -E touch "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-install"

jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'jwt-cpp-populate'"
	/usr/bin/cmake -E make_directory "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-src"
	/usr/bin/cmake -E make_directory "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build"
	/usr/bin/cmake -E make_directory "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix"
	/usr/bin/cmake -E make_directory "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/tmp"
	/usr/bin/cmake -E make_directory "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp"
	/usr/bin/cmake -E make_directory "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/src"
	/usr/bin/cmake -E make_directory "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp"
	/usr/bin/cmake -E touch "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-mkdir"

jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-patch: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'jwt-cpp-populate'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-patch"

jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-update:
.PHONY : jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-update

jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-test: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'jwt-cpp-populate'"
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build" && /usr/bin/cmake -E echo_append
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-build" && /usr/bin/cmake -E touch "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-test"

jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-update: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Performing update step for 'jwt-cpp-populate'"
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-src" && /usr/bin/cmake -P "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/jwt-cpp-populate-prefix/tmp/jwt-cpp-populate-gitupdate.cmake"

jwt-cpp-populate: CMakeFiles/jwt-cpp-populate
jwt-cpp-populate: CMakeFiles/jwt-cpp-populate-complete
jwt-cpp-populate: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-build
jwt-cpp-populate: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-configure
jwt-cpp-populate: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-download
jwt-cpp-populate: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-install
jwt-cpp-populate: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-mkdir
jwt-cpp-populate: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-patch
jwt-cpp-populate: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-test
jwt-cpp-populate: jwt-cpp-populate-prefix/src/jwt-cpp-populate-stamp/jwt-cpp-populate-update
jwt-cpp-populate: CMakeFiles/jwt-cpp-populate.dir/build.make
.PHONY : jwt-cpp-populate

# Rule to build all files generated by this target.
CMakeFiles/jwt-cpp-populate.dir/build: jwt-cpp-populate
.PHONY : CMakeFiles/jwt-cpp-populate.dir/build

CMakeFiles/jwt-cpp-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jwt-cpp-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jwt-cpp-populate.dir/clean

CMakeFiles/jwt-cpp-populate.dir/depend:
	cd "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild" "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild" "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild" "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild" "/home/leandro/Área de Trabalho/BitFakeCoin/build/_deps/jwt-cpp-subbuild/CMakeFiles/jwt-cpp-populate.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/jwt-cpp-populate.dir/depend

