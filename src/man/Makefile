# Where the build output will be placed relative to here
BUILD_DIR = ../../build/man
# Here relative to the build dir
SRC_DIR = ../../src/man

CROSS_FILE = $(BUILD_DIR)/cross

.PHONY: build
build:  $(BUILD_DIR)/Makefile
	$(MAKE) -C $(BUILD_DIR) --no-print-directory

.PHONY: cross
cross:  $(CROSS_FILE)
	cd $(BUILD_DIR); \
	cmake  $(CMAKE_CROSS_FLAGS) $(SRC_DIR); \
	ccmake $(SRC_DIR)

$(CROSS_FILE):
	mkdir -p $(BUILD_DIR)
	@touch $(CROSS_FILE)
