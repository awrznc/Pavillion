#include <sys/stat.h>

#include "pavillion.hxx"

void Pavillion::make_directry() {
    char *username = getenv(USERNAME_ENV_STR);
    char pavillion_dir_path[MAX_SIZE_OF_A_DIRNAME*2];
    sprintf(pavillion_dir_path, "%s%s%s%s", PAVILLION_DIR_PREFIX, username, PAVILLION_DIR_SUFIX, PAVILLION);

    // If the directory does not exist, make it.
    struct stat statBuf;
    if (stat(pavillion_dir_path, &statBuf) != 0) {
        if (_mkdir(pavillion_dir_path) == 0) {
            printf("make \"%s\"\n", pavillion_dir_path);
        }
    }
}

void Pavillion::load_preferences() {
}

void Pavillion::run() {
    window->draw();
}

Pavillion::Pavillion() {
    make_directry();
    window = new Window(PAVILLION);
}

Pavillion::~Pavillion() { }

int main(){
    Pavillion* pavillion = new Pavillion();
    pavillion->run();
    return 0;
}
