# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /home/pau/.cache/JetBrains/RemoteDev/dist/3c8ecd31118eb_CLion-2023.1.1/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/pau/.cache/JetBrains/RemoteDev/dist/3c8ecd31118eb_CLion-2023.1.1/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pau/C/PCTR_Entregas

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pau/C/PCTR_Entregas/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PCTR_Entregas.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PCTR_Entregas.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PCTR_Entregas.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PCTR_Entregas.dir/flags.make

CMakeFiles/PCTR_Entregas.dir/src/main.cpp.o: CMakeFiles/PCTR_Entregas.dir/flags.make
CMakeFiles/PCTR_Entregas.dir/src/main.cpp.o: /home/pau/C/PCTR_Entregas/src/main.cpp
CMakeFiles/PCTR_Entregas.dir/src/main.cpp.o: CMakeFiles/PCTR_Entregas.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pau/C/PCTR_Entregas/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PCTR_Entregas.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PCTR_Entregas.dir/src/main.cpp.o -MF CMakeFiles/PCTR_Entregas.dir/src/main.cpp.o.d -o CMakeFiles/PCTR_Entregas.dir/src/main.cpp.o -c /home/pau/C/PCTR_Entregas/src/main.cpp

CMakeFiles/PCTR_Entregas.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PCTR_Entregas.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pau/C/PCTR_Entregas/src/main.cpp > CMakeFiles/PCTR_Entregas.dir/src/main.cpp.i

CMakeFiles/PCTR_Entregas.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PCTR_Entregas.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pau/C/PCTR_Entregas/src/main.cpp -o CMakeFiles/PCTR_Entregas.dir/src/main.cpp.s

CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.o: CMakeFiles/PCTR_Entregas.dir/flags.make
CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.o: /home/pau/C/PCTR_Entregas/src/filosofo.cpp
CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.o: CMakeFiles/PCTR_Entregas.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pau/C/PCTR_Entregas/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.o -MF CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.o.d -o CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.o -c /home/pau/C/PCTR_Entregas/src/filosofo.cpp

CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pau/C/PCTR_Entregas/src/filosofo.cpp > CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.i

CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pau/C/PCTR_Entregas/src/filosofo.cpp -o CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.s

# Object files for target PCTR_Entregas
PCTR_Entregas_OBJECTS = \
"CMakeFiles/PCTR_Entregas.dir/src/main.cpp.o" \
"CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.o"

# External object files for target PCTR_Entregas
PCTR_Entregas_EXTERNAL_OBJECTS =

PCTR_Entregas: CMakeFiles/PCTR_Entregas.dir/src/main.cpp.o
PCTR_Entregas: CMakeFiles/PCTR_Entregas.dir/src/filosofo.cpp.o
PCTR_Entregas: CMakeFiles/PCTR_Entregas.dir/build.make
PCTR_Entregas: CMakeFiles/PCTR_Entregas.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pau/C/PCTR_Entregas/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable PCTR_Entregas"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PCTR_Entregas.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PCTR_Entregas.dir/build: PCTR_Entregas
.PHONY : CMakeFiles/PCTR_Entregas.dir/build

CMakeFiles/PCTR_Entregas.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PCTR_Entregas.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PCTR_Entregas.dir/clean

CMakeFiles/PCTR_Entregas.dir/depend:
	cd /home/pau/C/PCTR_Entregas/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pau/C/PCTR_Entregas /home/pau/C/PCTR_Entregas /home/pau/C/PCTR_Entregas/cmake-build-debug /home/pau/C/PCTR_Entregas/cmake-build-debug /home/pau/C/PCTR_Entregas/cmake-build-debug/CMakeFiles/PCTR_Entregas.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PCTR_Entregas.dir/depend

