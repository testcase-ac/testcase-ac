#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int HH, MM;

    int mode = rnd.next(1, 6); // choose pattern

    if (mode == 1) {
        // Earliest possible time (sample 1)
        HH = 9;
        MM = 0;
    } else if (mode == 2) {
        // Latest possible time (sample 2)
        HH = 11;
        MM = 59;
    } else if (mode == 3) {
        // Boundary minutes with any valid hour
        HH = rnd.next(9, 11);
        int mins[2] = {0, 59};
        MM = mins[rnd.next(0, 1)];
    } else if (mode == 4) {
        // Times around the start (9:xx, small minutes)
        HH = 9;
        if (rnd.next(0, 1) == 0) {
            MM = rnd.next(1, 10);  // early minutes
        } else {
            MM = rnd.next(50, 59); // close to 10:00
        }
    } else if (mode == 5) {
        // Times in middle hour (10:xx), varied minutes
        HH = 10;
        if (rnd.next(0, 1) == 0) {
            MM = rnd.next(0, 59);
        } else {
            // Prefer near boundaries inside this hour
            int candidates[] = {0, 1, 2, 30, 57, 58, 59};
            MM = candidates[rnd.next(0, 6)];
        }
    } else {
        // Fully random valid time
        HH = rnd.next(9, 11);
        MM = rnd.next(0, 59);
    }

    println(HH, MM);
    return 0;
}
