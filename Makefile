BUILD_TYPE = Release
BUILD_DIR = build
CMAKE_DIR = $(CURDIR)

.PHONY: init clean build

all: build

init:
	mkdir $(BUILD_DIR)
	cd $(BUILD_DIR) && \
	cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) $(CMAKE_OPTS) $(CMAKE_DIR)

build: init
	$(MAKE) -C $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
