#pragma once
#include <filesystem>
#include <functional>

class AppState {
public:
    std::filesystem::path assetsDir;
    std::filesystem::path pythonRootDir;

    std::filesystem::path dataDir;
    std::filesystem::path destDir;
    std::string lang = "cn";

    std::function<void(std::string)> addLog;

    bool gracefulExit;
    bool appShallExit;

    AppState(){
        addLog = [](std::string message) {
            std::cout << message << std::endl;
        };
    };
};
