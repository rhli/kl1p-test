# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/unix/UnixMakefile_x64Release

# Include any dependencies generated for this target.
include CMakeFiles/CompressedSensingExample64.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CompressedSensingExample64.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CompressedSensingExample64.dir/flags.make

CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o: CMakeFiles/CompressedSensingExample64.dir/flags.make
CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o: ../../CompressedSensingExample.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/unix/UnixMakefile_x64Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o"
	/usr/sbin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o -c /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/CompressedSensingExample.cpp

CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.i"
	/usr/sbin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/CompressedSensingExample.cpp > CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.i

CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.s"
	/usr/sbin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/CompressedSensingExample.cpp -o CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.s

CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o.requires:

.PHONY : CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o.requires

CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o.provides: CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o.requires
	$(MAKE) -f CMakeFiles/CompressedSensingExample64.dir/build.make CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o.provides.build
.PHONY : CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o.provides

CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o.provides.build: CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o


CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o: CMakeFiles/CompressedSensingExample64.dir/flags.make
CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/unix/UnixMakefile_x64Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o"
	/usr/sbin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o -c /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/unix/main.cpp

CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.i"
	/usr/sbin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/unix/main.cpp > CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.i

CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.s"
	/usr/sbin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/unix/main.cpp -o CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.s

CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o.requires:

.PHONY : CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o.requires

CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o.provides: CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/CompressedSensingExample64.dir/build.make CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o.provides.build
.PHONY : CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o.provides

CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o.provides.build: CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o


# Object files for target CompressedSensingExample64
CompressedSensingExample64_OBJECTS = \
"CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o" \
"CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o"

# External object files for target CompressedSensingExample64
CompressedSensingExample64_EXTERNAL_OBJECTS =

/home/steve/src/cpp_src/kl1p_dev/bin/unix/CompressedSensingExample64: CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o
/home/steve/src/cpp_src/kl1p_dev/bin/unix/CompressedSensingExample64: CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o
/home/steve/src/cpp_src/kl1p_dev/bin/unix/CompressedSensingExample64: CMakeFiles/CompressedSensingExample64.dir/build.make
/home/steve/src/cpp_src/kl1p_dev/bin/unix/CompressedSensingExample64: CMakeFiles/CompressedSensingExample64.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/unix/UnixMakefile_x64Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /home/steve/src/cpp_src/kl1p_dev/bin/unix/CompressedSensingExample64"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CompressedSensingExample64.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CompressedSensingExample64.dir/build: /home/steve/src/cpp_src/kl1p_dev/bin/unix/CompressedSensingExample64

.PHONY : CMakeFiles/CompressedSensingExample64.dir/build

CMakeFiles/CompressedSensingExample64.dir/requires: CMakeFiles/CompressedSensingExample64.dir/CompressedSensingExample.cpp.o.requires
CMakeFiles/CompressedSensingExample64.dir/requires: CMakeFiles/CompressedSensingExample64.dir/unix/main.cpp.o.requires

.PHONY : CMakeFiles/CompressedSensingExample64.dir/requires

CMakeFiles/CompressedSensingExample64.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CompressedSensingExample64.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CompressedSensingExample64.dir/clean

CMakeFiles/CompressedSensingExample64.dir/depend:
	cd /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/unix/UnixMakefile_x64Release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/unix/UnixMakefile_x64Release /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/unix/UnixMakefile_x64Release /home/steve/src/cpp_src/kl1p_dev/examples/CompressedSensingExample/unix/UnixMakefile_x64Release/CMakeFiles/CompressedSensingExample64.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CompressedSensingExample64.dir/depend

