#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

#define CNFG_IMPLEMENTATION
#include "rawdraw_sf.h"


void HandleKey(int keycode, int bDown) { }
void HandleButton(int x, int y, int button, int bDown) { }
void HandleMotion(int x, int y, int mask) { }
int HandleDestroy() { return 0; }

int main(int argc, char **argv) {
    CNFGSetup("Simple Christmas", 1024, 768);

    struct timeval tv;

    gettimeofday(&tv, NULL);

    struct tm christmas = {0};
    christmas.tm_year = (((((tv.tv_sec / 60) / 60) / 24) / 365) + 1970) - 1900;
    christmas.tm_mon = 11; // WHY????
    christmas.tm_mday = 25;

    time_t target = mktime(&christmas);

    while(CNFGHandleInput()) {
        CNFGBGColor = 0x000080ff;

        CNFGClearFrame();

        gettimeofday(&tv, NULL);

        double seconds = difftime(target, tv.tv_sec);

        char buffer[100];

        int minutes = (int)seconds / 60;
        int hours = minutes / 60;
        int days = hours / 24;
        snprintf(buffer, 100, "Days: %d, Hours: %d, Minutes: %d, Seconds: %d", days, hours % 24, minutes % 60, (int)seconds % 60);

        CNFGColor(0xffffffff);
        CNFGPenX = 1; CNFGPenY = 1;
        CNFGDrawText(buffer, 5);

        CNFGSwapBuffers();
    }
}