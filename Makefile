SHELL := /bin/sh
LLVM_BUILD := ./llvm-build
CLANG := $(LLVM_BUILD)/bin/clang-15
CXXFLAGS := \
	-lc++ \
	-std=c++2b \
	-O3 \
	-Wall \
	-Wpedantic \
	-Werror \
	-fmodules \
	-fsanitize=address \
	-fsanitize=undefined
INCLUDES := \
	-nostdinc++ \
	-nostdlib++ \
	-isystem $(LLVM_BUILD)/include/c++/v1 \
	-L $(LLVM_BUILD)/lib \
	-Wl,-rpath,$(LLVM_BUILD)/lib
ifeq ($(shell uname),Darwin)
	INCLUDES += -isysroot $(shell xcrun --show-sdk-path)
endif

OUT ?= out
SRC_FILES := $(wildcard src/*.cc)
BIN_FILES := $(notdir $(basename $(SRC_FILES)))
OUT_FILES := $(addprefix $(OUT)/,$(BIN_FILES))

.PHONY: all clean

all: $(OUT_FILES)

clean:
	rm -rv $(OUT)

$(OUT):
	mkdir -p $@

$(OUT_FILES): $(OUT)/%: src/%.cc | $(OUT)
	$(CLANG) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(addprefix run,$(BIN_FILES)): run% : txt/input/% $(OUT)/%
	@cat $< | $(OUT)/$*
