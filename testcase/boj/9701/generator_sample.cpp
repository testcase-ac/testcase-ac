#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 25);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        vector<int> counts(9);
        int mode = rnd.next(0, 5);

        if (mode == 0) {
            int digit = rnd.next(0, 3);
            counts[digit * 2 + 1] = rnd.next(0, 9);
        } else if (mode == 1) {
            for (int i = 1; i < 9; i += 2) {
                counts[i] = rnd.next(0, 2);
            }
        } else if (mode == 2) {
            for (int i = 1; i < 9; i += 2) {
                counts[i] = rnd.next(7, 9);
            }
        } else if (mode == 3) {
            int first = rnd.next(0, 3) * 2 + 1;
            int second = rnd.next(0, 3) * 2 + 1;
            counts[first] = rnd.next(1, 9);
            counts[second] = rnd.next(1, 9);
        } else if (mode == 4) {
            for (int i = 1; i < 9; i += 2) {
                counts[i] = rnd.next(0, 9);
            }
        } else {
            for (int i = 1; i < 9; i += 2) {
                counts[i] = rnd.wnext(10, -2);
            }
        }

        println(counts);
    }

    return 0;
}
