#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We need exactly 10 dice rolls between 1 and 5.
    vector<int> dice(10);

    // Choose one of several patterns to introduce variability and edge cases.
    int pattern = rnd.next(0, 5);
    switch (pattern) {
        // 0: all same value
        case 0: {
            int v = rnd.next(1, 5);
            for (int &x : dice) x = v;
            break;
        }
        // 1: cyclic increasing 1,2,3,4,5,1,2,...
        case 1: {
            for (int i = 0; i < 10; i++) {
                dice[i] = (i % 5) + 1;
            }
            break;
        }
        // 2: a few random runs of constant values
        case 2: {
            int runs = rnd.next(2, 5);
            int rem = 10;
            for (int r = 0; r < runs; r++) {
                int len = (r == runs - 1 ? rem : rnd.next(1, rem - (runs - r - 1)));
                int v = rnd.next(1, 5);
                for (int k = 0; k < len; k++) {
                    dice[10 - rem + k] = v;
                }
                rem -= len;
            }
            break;
        }
        // 3: alternating between two distinct values
        case 3: {
            int a = rnd.next(1, 5), b;
            do { b = rnd.next(1, 5); } while (b == a);
            for (int i = 0; i < 10; i++) {
                dice[i] = (i % 2 == 0 ? a : b);
            }
            break;
        }
        // 4: weighted toward extremes using wnext
        case 4: {
            vector<int> ts = { -2, -1, 1, 2 };
            int t = rnd.any(ts);
            for (int i = 0; i < 10; i++) {
                // rnd.wnext(5, t) gives 0..4 biased; +1 shifts to 1..5
                dice[i] = rnd.wnext(5, t) + 1;
            }
            break;
        }
        // 5: uniform random
        case 5: {
            for (int &x : dice) x = rnd.next(1, 5);
            break;
        }
    }

    // Output the 10 dice rolls
    println(dice);

    return 0;
}
