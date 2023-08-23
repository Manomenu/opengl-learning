#include "WindowApp.h"

int main(int argc, char** argv)
{
    WindowApp* app = new WindowApp();
    app->run_loop();

    return EXIT_SUCCESS;
}
