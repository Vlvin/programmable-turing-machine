CPPC=clang++
CPPFLAGS=-lm $(RAYLIB_FLAGS) $(ENTT_FLAGS) -Isrc
# RAYLIB_FLAGS=-Llib/raylib/lib -l:libraylib.a -Ilib/raylib/include
# ENTT_FLAGS=-Ilib/entt/single_include/entt
SRC=main.cpp src/*.cpp src/**/*.cpp 
TESTS_DIR=tests
BUILD_FOLDER=build/

# CMD args
SEPARATE_BUILD?=0

ifeq ($(SEPARATE_BUILD), 0)
build: $(SRC)
	mkdir -p $(BUILD_FOLDER)
	echo "" > unity_build.cpp
	for file in $$(ls src/**/*.cpp); do	echo "#include \"$$file\"" >> unity_build.cpp;	done
	echo "#include \"main.cpp\"" >> unity_build.cpp
	$(CPPC) unity_build.cpp $(CPPFLAGS) -o $(BUILD_FOLDER)main
	rm unity_build.cpp
else
build: $(SRC)
	mkdir -p $(BUILD_FOLDER)
	$(CPPC) $^ $(CPPFLAGS) -o $(BUILD_FOLDER)main
endif

build_debug: $(SRC)
	mkdir -p $(BUILD_FOLDER)
	$(CPPC) $^ $(CPPFLAGS) -ggdb -o $(BUILD_FOLDER)main

genbuilddb: $(SRC)
	$(CPPC) -MJ compile_commands.json $^ $(CPPFLAGS)
	echo "[ $$(cat compile_commands.json) ]" > compile_commands.json


debug: build_debug
	gdb main

run: build
	$(BUILD_FOLDER)main

build_tests: tests/*
	mkdir -p built_tests
	for file in $^ ; do\
		$(CPPC) $(CPPFLAGS) -ggdb $${file} -o "built_"$${file: 0 : -2} ; \
	done

run_tests: build_tests
	for file in $$(ls "built_"$(TESTS_DIR)) ; do\
		echo $${file} ;\
		"built_"$(TESTS_DIR)/$${file} ;\
	done
