# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/d/0-Facu/2022-1C-MetNum/tp1/MN2022/tp1/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/0-Facu/2022-1C-MetNum/tp1/MN2022/tp1/src/build

# Include any dependencies generated for this target.
include CMakeFiles/tp1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tp1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tp1.dir/flags.make

CMakeFiles/tp1.dir/Main.cpp.o: CMakeFiles/tp1.dir/flags.make
CMakeFiles/tp1.dir/Main.cpp.o: ../Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/0-Facu/2022-1C-MetNum/tp1/MN2022/tp1/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tp1.dir/Main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tp1.dir/Main.cpp.o -c /mnt/d/0-Facu/2022-1C-MetNum/tp1/MN2022/tp1/src/Main.cpp

CMakeFiles/tp1.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tp1.dir/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/0-Facu/2022-1C-MetNum/tp1/MN2022/tp1/src/Main.cpp > CMakeFiles/tp1.dir/Main.cpp.i

CMakeFiles/tp1.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tp1.dir/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/0-Facu/2022-1C-MetNum/tp1/MN2022/tp1/src/Main.cpp -o CMakeFiles/tp1.dir/Main.cpp.s

# Object files for target tp1
tp1_OBJECTS = \
"CMakeFiles/tp1.dir/Main.cpp.o"

# External object files for target tp1
tp1_EXTERNAL_OBJECTS =

tp1: CMakeFiles/tp1.dir/Main.cpp.o
tp1: CMakeFiles/tp1.dir/build.make
tp1: CMakeFiles/tp1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/0-Facu/2022-1C-MetNum/tp1/MN2022/tp1/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tp1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tp1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tp1.dir/build: tp1

.PHONY : CMakeFiles/tp1.dir/build

CMakeFiles/tp1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tp1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tp1.dir/clean

CMakeFiles/tp1.dir/depend:
	cd /mnt/d/0-Facu/2022-1C-MetNum/tp1/MN2022/tp1/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/0-Facu/2022-1C-MetNum/tp1/MN2022/tp1/src /mnt/d/0-Facu/2022-1C-MetNum/tp1/MN2022/tp1/src /mnt/d/0-Facu/2022-1C-MetNum/tp1/MN2022/tp1/src/build /mnt/d/0-Facu/2022-1C-MetNum/tp1/MN2022/tp1/src/build /mnt/d/0-Facu/2022-1C-MetNum/tp1/MN2022/tp1/src/build/CMakeFiles/tp1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tp1.dir/depend

