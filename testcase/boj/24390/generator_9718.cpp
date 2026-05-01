#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = 0;

    int mode = rnd.next(0, 4);

    if (mode == 0) {
        // Small and very tricky times
        vector<int> cand = {
            10, 20, 30, 40, 50,
            60, 70, 80, 90, 100,
            110, 120, 130, 140, 150,
            160, 170, 180, 190, 200
        };
        T = rnd.any(cand);
    } else if (mode == 1) {
        // Around multiples of 30 with small offsets
        while (true) {
            int k = rnd.next(1, 120); // 30*k up to 3600
            static int deltas[] = {-60, -30, -20, -10, 0, 10, 20, 30, 60};
            int delta = rnd.any(vector<int>(deltas, deltas + 9));
            T = 30 * k + delta;
            if (T >= 10 && T <= 3600 && T % 10 == 0)
                break;
        }
    } else if (mode == 2) {
        // Near interesting bases (minutes and tens of minutes)
        vector<int> bases = {
            60, 120, 180, 240, 300,
            600, 900, 1200, 1500, 1800,
            2100, 2400, 2700, 3000, 3300, 3600
        };
        while (true) {
            int base = rnd.any(bases);
            int delta = 10 * rnd.next(-12, 12); // -120 .. 120
            T = base + delta;
            if (T >= 10 && T <= 3600 && T % 10 == 0)
                break;
        }
    } else if (mode == 3) {
        // Completely random multiple of 10
        T = 10 * rnd.next(1, 360); // 10 .. 3600
    } else {
        // Hand-picked special tricky values, including extremes
        vector<int> special = {
            10, 20, 30, 40, 50,
            60, 70, 80, 90, 100,
            110, 120, 130, 140, 150,
            170, 190, 200, 220, 250,
            290, 300, 310, 330, 340,
            350, 360, 370, 380, 390,
            400, 410, 430, 450, 480,
            510, 550, 580, 600, 610,
            620, 630, 640, 650, 660,
            670, 680, 690, 700, 710,
            740, 770, 800, 830, 900,
            1000, 1230, 1250, 1270, 1300,
            1790, 1800, 1810, 1990, 2000, 2010,
            3500, 3540, 3590, 3600
        };
        T = rnd.any(special);
    }

    int M = T / 60;
    int S = T % 60;

    printf("%02d:%02d\n", M, S);
    return 0;
}
