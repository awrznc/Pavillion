#pragma comment(lib, "winmm.lib")

#include <fstream>
#include <direct.h>

#include "window.hxx"

#ifdef _WIN32

#define PAVILLION               "Pavillion"
#define PAVILLION_DIR_PREFIX    "C:\\Users\\"
#define PAVILLION_DIR_SUFIX     "\\AppData\\Local\\"
#define CONFIG_FILENAME         "lion.conf"
#define USERNAME_ENV_STR        "USERNAME"

#define MAX_SIZE_OF_A_DIRNAME 256

#endif

class Pavillion {

private:
    Window* window;
    void make_directry();
    void load_preferences();

public:
    Pavillion();
    ~Pavillion();
    void run();
};
