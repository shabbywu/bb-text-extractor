.PHONY: all
all: build

.PHONY: build
ifeq ($(OS),Windows_NT)
build:
	mkdir -p build
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CONFIGURATION_TYPES="Release" -B build -A Win32
	cmake --build build --config Release
else
build:
	mkdir -p build
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CONFIGURATION_TYPES="Release" -DHELLOIMGUI_MACOS_NO_BUNDLE="ON" -DHELLOIMGUI_USE_FREETYPE="OFF" -B build
	cmake --build build --config Release -v
endif
