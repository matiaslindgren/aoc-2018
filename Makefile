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

.PHONY: all
all: $(OUT_FILES)

.PHONY: clean
clean:
	rm -rv $(OUT)

$(OUT):
	mkdir -p $@

$(OUT_FILES): $(OUT)/%: src/%.cc | $(OUT)
	$(CLANG) $(CXXFLAGS) $(INCLUDES) -o $@ $^

RUN_TARGETS := $(addprefix run,$(BIN_FILES))

.PHONY: $(RUN_TARGETS)
$(RUN_TARGETS): run% : txt/input/% $(OUT)/%
	@cat $< | $(OUT)/$*

TEST_TARGETS := $(addprefix test,$(BIN_FILES))

.PHONY: test
test: $(TEST_TARGETS)

.PHONY: $(TEST_TARGETS)
$(TEST_TARGETS): test% : $(OUT)/%
	@echo $*; \
	result=$$(make run$*); \
	expect=$$(cat txt/correct/$*); \
	if [[ "$$result" != "$$expect" ]]; then \
		echo result: $$result; \
		echo expect: $$expect; \
		exit 1; \
	fi
