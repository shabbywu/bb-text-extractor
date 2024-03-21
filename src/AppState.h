#pragma once
#include <filesystem>


class AppState {
public:
    std::filesystem::path dataDir;
    std::filesystem::path destDir;

    AppState(){};
};