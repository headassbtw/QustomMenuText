# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /data/Programs/CLion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /data/Programs/CLion/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/headass/cppProjects/QustomMenuText

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/headass/cppProjects/QustomMenuText/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/QustomMenuText.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/QustomMenuText.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/QustomMenuText.dir/flags.make

CMakeFiles/QustomMenuText.dir/src/main.cpp.o: CMakeFiles/QustomMenuText.dir/flags.make
CMakeFiles/QustomMenuText.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/headass/cppProjects/QustomMenuText/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/QustomMenuText.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/QustomMenuText.dir/src/main.cpp.o -c /home/headass/cppProjects/QustomMenuText/src/main.cpp

CMakeFiles/QustomMenuText.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QustomMenuText.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/headass/cppProjects/QustomMenuText/src/main.cpp > CMakeFiles/QustomMenuText.dir/src/main.cpp.i

CMakeFiles/QustomMenuText.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QustomMenuText.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/headass/cppProjects/QustomMenuText/src/main.cpp -o CMakeFiles/QustomMenuText.dir/src/main.cpp.s

# Object files for target QustomMenuText
QustomMenuText_OBJECTS = \
"CMakeFiles/QustomMenuText.dir/src/main.cpp.o"

# External object files for target QustomMenuText
QustomMenuText_EXTERNAL_OBJECTS =

libQustomMenuText.so: CMakeFiles/QustomMenuText.dir/src/main.cpp.o
libQustomMenuText.so: CMakeFiles/QustomMenuText.dir/build.make
libQustomMenuText.so: CMakeFiles/QustomMenuText.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/headass/cppProjects/QustomMenuText/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libQustomMenuText.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/QustomMenuText.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/QustomMenuText.dir/build: libQustomMenuText.so
.PHONY : CMakeFiles/QustomMenuText.dir/build

CMakeFiles/QustomMenuText.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/QustomMenuText.dir/cmake_clean.cmake
.PHONY : CMakeFiles/QustomMenuText.dir/clean

CMakeFiles/QustomMenuText.dir/depend:
	cd /home/headass/cppProjects/QustomMenuText/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/headass/cppProjects/QustomMenuText /home/headass/cppProjects/QustomMenuText /home/headass/cppProjects/QustomMenuText/cmake-build-debug /home/headass/cppProjects/QustomMenuText/cmake-build-debug /home/headass/cppProjects/QustomMenuText/cmake-build-debug/CMakeFiles/QustomMenuText.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/QustomMenuText.dir/depend

