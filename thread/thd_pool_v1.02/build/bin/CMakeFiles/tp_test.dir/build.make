# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lucid/work/test/thread/thd_pool_v1.02

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lucid/work/test/thread/thd_pool_v1.02/build

# Include any dependencies generated for this target.
include bin/CMakeFiles/tp_test.dir/depend.make

# Include the progress variables for this target.
include bin/CMakeFiles/tp_test.dir/progress.make

# Include the compile flags for this target's objects.
include bin/CMakeFiles/tp_test.dir/flags.make

bin/CMakeFiles/tp_test.dir/tsqueue.o: bin/CMakeFiles/tp_test.dir/flags.make
bin/CMakeFiles/tp_test.dir/tsqueue.o: ../src/tsqueue.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lucid/work/test/thread/thd_pool_v1.02/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object bin/CMakeFiles/tp_test.dir/tsqueue.o"
	cd /home/lucid/work/test/thread/thd_pool_v1.02/build/bin && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tp_test.dir/tsqueue.o   -c /home/lucid/work/test/thread/thd_pool_v1.02/src/tsqueue.c

bin/CMakeFiles/tp_test.dir/tsqueue.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp_test.dir/tsqueue.i"
	cd /home/lucid/work/test/thread/thd_pool_v1.02/build/bin && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/lucid/work/test/thread/thd_pool_v1.02/src/tsqueue.c > CMakeFiles/tp_test.dir/tsqueue.i

bin/CMakeFiles/tp_test.dir/tsqueue.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp_test.dir/tsqueue.s"
	cd /home/lucid/work/test/thread/thd_pool_v1.02/build/bin && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/lucid/work/test/thread/thd_pool_v1.02/src/tsqueue.c -o CMakeFiles/tp_test.dir/tsqueue.s

bin/CMakeFiles/tp_test.dir/tsqueue.o.requires:
.PHONY : bin/CMakeFiles/tp_test.dir/tsqueue.o.requires

bin/CMakeFiles/tp_test.dir/tsqueue.o.provides: bin/CMakeFiles/tp_test.dir/tsqueue.o.requires
	$(MAKE) -f bin/CMakeFiles/tp_test.dir/build.make bin/CMakeFiles/tp_test.dir/tsqueue.o.provides.build
.PHONY : bin/CMakeFiles/tp_test.dir/tsqueue.o.provides

bin/CMakeFiles/tp_test.dir/tsqueue.o.provides.build: bin/CMakeFiles/tp_test.dir/tsqueue.o

bin/CMakeFiles/tp_test.dir/thread_pool.o: bin/CMakeFiles/tp_test.dir/flags.make
bin/CMakeFiles/tp_test.dir/thread_pool.o: ../src/thread_pool.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lucid/work/test/thread/thd_pool_v1.02/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object bin/CMakeFiles/tp_test.dir/thread_pool.o"
	cd /home/lucid/work/test/thread/thd_pool_v1.02/build/bin && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tp_test.dir/thread_pool.o   -c /home/lucid/work/test/thread/thd_pool_v1.02/src/thread_pool.c

bin/CMakeFiles/tp_test.dir/thread_pool.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp_test.dir/thread_pool.i"
	cd /home/lucid/work/test/thread/thd_pool_v1.02/build/bin && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/lucid/work/test/thread/thd_pool_v1.02/src/thread_pool.c > CMakeFiles/tp_test.dir/thread_pool.i

bin/CMakeFiles/tp_test.dir/thread_pool.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp_test.dir/thread_pool.s"
	cd /home/lucid/work/test/thread/thd_pool_v1.02/build/bin && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/lucid/work/test/thread/thd_pool_v1.02/src/thread_pool.c -o CMakeFiles/tp_test.dir/thread_pool.s

bin/CMakeFiles/tp_test.dir/thread_pool.o.requires:
.PHONY : bin/CMakeFiles/tp_test.dir/thread_pool.o.requires

bin/CMakeFiles/tp_test.dir/thread_pool.o.provides: bin/CMakeFiles/tp_test.dir/thread_pool.o.requires
	$(MAKE) -f bin/CMakeFiles/tp_test.dir/build.make bin/CMakeFiles/tp_test.dir/thread_pool.o.provides.build
.PHONY : bin/CMakeFiles/tp_test.dir/thread_pool.o.provides

bin/CMakeFiles/tp_test.dir/thread_pool.o.provides.build: bin/CMakeFiles/tp_test.dir/thread_pool.o

bin/CMakeFiles/tp_test.dir/tp_test.o: bin/CMakeFiles/tp_test.dir/flags.make
bin/CMakeFiles/tp_test.dir/tp_test.o: ../src/tp_test.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lucid/work/test/thread/thd_pool_v1.02/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object bin/CMakeFiles/tp_test.dir/tp_test.o"
	cd /home/lucid/work/test/thread/thd_pool_v1.02/build/bin && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tp_test.dir/tp_test.o   -c /home/lucid/work/test/thread/thd_pool_v1.02/src/tp_test.c

bin/CMakeFiles/tp_test.dir/tp_test.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp_test.dir/tp_test.i"
	cd /home/lucid/work/test/thread/thd_pool_v1.02/build/bin && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/lucid/work/test/thread/thd_pool_v1.02/src/tp_test.c > CMakeFiles/tp_test.dir/tp_test.i

bin/CMakeFiles/tp_test.dir/tp_test.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp_test.dir/tp_test.s"
	cd /home/lucid/work/test/thread/thd_pool_v1.02/build/bin && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/lucid/work/test/thread/thd_pool_v1.02/src/tp_test.c -o CMakeFiles/tp_test.dir/tp_test.s

bin/CMakeFiles/tp_test.dir/tp_test.o.requires:
.PHONY : bin/CMakeFiles/tp_test.dir/tp_test.o.requires

bin/CMakeFiles/tp_test.dir/tp_test.o.provides: bin/CMakeFiles/tp_test.dir/tp_test.o.requires
	$(MAKE) -f bin/CMakeFiles/tp_test.dir/build.make bin/CMakeFiles/tp_test.dir/tp_test.o.provides.build
.PHONY : bin/CMakeFiles/tp_test.dir/tp_test.o.provides

bin/CMakeFiles/tp_test.dir/tp_test.o.provides.build: bin/CMakeFiles/tp_test.dir/tp_test.o

# Object files for target tp_test
tp_test_OBJECTS = \
"CMakeFiles/tp_test.dir/tsqueue.o" \
"CMakeFiles/tp_test.dir/thread_pool.o" \
"CMakeFiles/tp_test.dir/tp_test.o"

# External object files for target tp_test
tp_test_EXTERNAL_OBJECTS =

bin/tp_test: bin/CMakeFiles/tp_test.dir/tsqueue.o
bin/tp_test: bin/CMakeFiles/tp_test.dir/thread_pool.o
bin/tp_test: bin/CMakeFiles/tp_test.dir/tp_test.o
bin/tp_test: bin/CMakeFiles/tp_test.dir/build.make
bin/tp_test: bin/CMakeFiles/tp_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable tp_test"
	cd /home/lucid/work/test/thread/thd_pool_v1.02/build/bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tp_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/CMakeFiles/tp_test.dir/build: bin/tp_test
.PHONY : bin/CMakeFiles/tp_test.dir/build

bin/CMakeFiles/tp_test.dir/requires: bin/CMakeFiles/tp_test.dir/tsqueue.o.requires
bin/CMakeFiles/tp_test.dir/requires: bin/CMakeFiles/tp_test.dir/thread_pool.o.requires
bin/CMakeFiles/tp_test.dir/requires: bin/CMakeFiles/tp_test.dir/tp_test.o.requires
.PHONY : bin/CMakeFiles/tp_test.dir/requires

bin/CMakeFiles/tp_test.dir/clean:
	cd /home/lucid/work/test/thread/thd_pool_v1.02/build/bin && $(CMAKE_COMMAND) -P CMakeFiles/tp_test.dir/cmake_clean.cmake
.PHONY : bin/CMakeFiles/tp_test.dir/clean

bin/CMakeFiles/tp_test.dir/depend:
	cd /home/lucid/work/test/thread/thd_pool_v1.02/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lucid/work/test/thread/thd_pool_v1.02 /home/lucid/work/test/thread/thd_pool_v1.02/src /home/lucid/work/test/thread/thd_pool_v1.02/build /home/lucid/work/test/thread/thd_pool_v1.02/build/bin /home/lucid/work/test/thread/thd_pool_v1.02/build/bin/CMakeFiles/tp_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/CMakeFiles/tp_test.dir/depend

