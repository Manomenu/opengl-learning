#include "WindowApp.h"
#include <filesystem>
#include <iostream>

int main(int argc, char** argv)
{
    std::cout << std::filesystem::current_path().string() << std::endl;

    WindowApp* app = new WindowApp();
    app->run_loop();

    return EXIT_SUCCESS;
}
