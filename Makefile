COMPILER=g++ -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
BUILD_DIR=build


.PHONY = all makeDIr

all: makeDir main.exe
	@echo Everything Compiled

makeDir:
ifeq (,$(wildcard ./$(BUILD_DIR)))
	mkdir $(BUILD_DIR)
endif


main.exe: $(BUILD_DIR)/main.o $(BUILD_DIR)/mergeSort.o
	@echo Compiling main.exe
	@echo ------------------
	@$(COMPILER) $^ -o $@


$(BUILD_DIR)/main.o: main.cpp
	@echo Compiling main.o
	@echo ----------------
	@$(COMPILER) -c $< -o $@

$(BUILD_DIR)/mergeSort.o: mergeSort.cpp mergeSort.h
	@echo Compiling mergeSort.o
	@echo ---------------------
	@$(COMPILER) -c $< -o $@
