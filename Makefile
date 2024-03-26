.PHONY: all
all: build

.PHONY: build
ifeq ($(OS),Windows_NT)
build:
	mkdir -p build
	cmake --preset=default
	cmake --build build/Windows --config Release
else
build:
	mkdir -p build
	cmake --preset=default
	cmake --build build/Darwin --config release -v
endif
