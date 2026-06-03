#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string gestures = "HPS";
    int mode = rnd.next(0, 5);
    int n = 1;
    vector<char> fj;

    if (mode == 0) {
        n = 1;
        fj.assign(n, rnd.any(gestures));
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        char gesture = rnd.any(gestures);
        fj.assign(n, gesture);
    } else if (mode == 2) {
        n = rnd.next(3, 60);
        int period = rnd.next(2, 3);
        int offset = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            fj.push_back(gestures[(offset + i) % period]);
        }
    } else if (mode == 3) {
        n = rnd.next(4, 80);
        int split = rnd.next(1, n - 1);
        char left = rnd.any(gestures);
        char right = rnd.any(gestures);
        while (right == left) {
            right = rnd.any(gestures);
        }
        for (int i = 0; i < split; ++i) {
            fj.push_back(left);
        }
        for (int i = split; i < n; ++i) {
            fj.push_back(right);
        }
    } else if (mode == 4) {
        n = rnd.next(5, 120);
        char common = rnd.any(gestures);
        char rare = rnd.any(gestures);
        while (rare == common) {
            rare = rnd.any(gestures);
        }
        int rareChance = rnd.next(5, 25);
        for (int i = 0; i < n; ++i) {
            fj.push_back(rnd.next(1, 100) <= rareChance ? rare : common);
        }
    } else {
        n = rnd.next(6, 150);
        for (int i = 0; i < n; ++i) {
            fj.push_back(rnd.any(gestures));
        }
    }

    println(n);
    for (char gesture : fj) {
        println(string(1, gesture));
    }

    return 0;
}
