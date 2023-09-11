COMPILER=g++ -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
BUILD_DIR=build
COMP_DIR=comparator
BUFF_DIR=buffer
SORT_DIR=mergeSort

.PHONY = all makeDIr

all: makeDirs main.exe
	@echo Everything Compiled

makeDirs:
ifeq (,$(wildcard ./$(BUILD_DIR)))
	mkdir $(BUILD_DIR)
endif
ifeq (,$(wildcard ./$(BUILD_DIR)/$(COMP_DIR)))
	mkdir $(COMP_DIR)
endif
ifeq (,$(wildcard ./$(BUILD_DIR)/$(BUFF_DIR)))
	mkdir $(BUFF_DIR)
endif
ifeq (,$(wildcard ./$(BUILD_DIR)/$(SORT_DIR)))
	mkdir $(SORT_DIR)
endif


main.exe: $(BUILD_DIR)/main.o $(BUILD_DIR)/mergeSort.o $(BUILD_DIR)/buffer.o $(BUILD_DIR)/comparator.o
	@echo Compiling main.exe
	@echo ------------------
	@$(COMPILER) $^ -o $@


$(BUILD_DIR)/main.o: main.cpp main.h
	@echo Compiling main.o
	@echo ----------------
	@$(COMPILER) -c $< -o $@

$(BUILD_DIR)/mergeSort.o: $(BUILD_DIR)/$(SORT_DIR)/mergeSort.cpp $(BUILD_DIR)/$(SORT_DIR)/mergeSort.h
	@echo Compiling mergeSort.o
	@echo ---------------------
	@$(COMPILER) -c $< -o $@

$(BUILD_DIR)/comparator.o: $(BUILD_DIR)/$(COMP_DIR)/comparator.cpp $(BUILD_DIR)/$(COMP_DIR)/comparator.h
	@echo Compiling comparator.o
	@echo ----------------------
	@$(COMPILER) -c $< -o $@

$(BUILD_DIR)/buffer.o: $(BUILD_DIR)/$(BUFF_DIR)/buffer.cpp $(BUILD_DIR)/$(BUFF_DIR)/buffer.h
	@echo Compiling buffer.o
	@echo ------------------
	@$(COMPILER) -c $< -o $@
