#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 25);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int classDaysTarget;
        if (mode == 0) {
            classDaysTarget = 1;
        } else if (mode == 1) {
            classDaysTarget = 7;
        } else if (mode == 2) {
            classDaysTarget = rnd.next(2, 3);
        } else if (mode == 3) {
            classDaysTarget = rnd.next(4, 6);
        } else {
            classDaysTarget = rnd.next(1, 7);
        }

        vector<int> days(7, 0);
        vector<int> positions = {0, 1, 2, 3, 4, 5, 6};
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < classDaysTarget; ++i) {
            days[positions[i]] = 1;
        }

        int kMode = rnd.next(0, 5);
        int k;
        if (kMode == 0) {
            k = 1;
        } else if (kMode == 1) {
            k = rnd.next(2, 20);
        } else if (kMode == 2) {
            int weeks = rnd.next(1, 1000);
            int offset = rnd.next(0, classDaysTarget - 1);
            k = weeks * classDaysTarget - offset;
        } else if (kMode == 3) {
            int weeks = rnd.next(1, 1000);
            int offset = rnd.next(0, classDaysTarget);
            k = weeks * classDaysTarget + offset;
        } else if (kMode == 4) {
            k = rnd.next(99999900, 100000000);
        } else {
            k = rnd.next(1, 100000000);
        }

        println(k);
        println(days);
    }

    return 0;
}
