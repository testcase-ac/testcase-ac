#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> dice;

    if (mode == 0) {
        int n = rnd.next(1, 80);
        for (int i = 0; i < n; ++i) {
            dice.push_back(rnd.next(1, 6));
        }
    } else if (mode == 1) {
        int games = rnd.next(1, 12);
        for (int g = 0; g < games; ++g) {
            int len = rnd.next(1, 8);
            for (int i = 0; i < len; ++i) {
                dice.push_back(rnd.next(2, 6));
            }
            dice.push_back(1);
        }
    } else if (mode == 2) {
        int sixes = rnd.next(5, 14);
        for (int i = 0; i < sixes; ++i) {
            dice.push_back(6);
        }
        if (rnd.next(0, 1)) {
            dice.push_back(1);
        }
        int tail = rnd.next(0, 20);
        for (int i = 0; i < tail; ++i) {
            dice.push_back(rnd.next(1, 6));
        }
    } else if (mode == 3) {
        int blocks = rnd.next(1, 6);
        for (int b = 0; b < blocks; ++b) {
            int run = rnd.next(1, 4);
            for (int i = 0; i < run; ++i) {
                dice.push_back(rnd.any(vector<int>{3, 4, 4, 5}));
            }
            if (rnd.next(0, 2) == 0) {
                dice.push_back(1);
            }
        }
    } else if (mode == 4) {
        int n = rnd.next(20, 120);
        int preferred = rnd.next(2, 6);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 65) {
                dice.push_back(preferred);
            } else {
                dice.push_back(rnd.next(1, 6));
            }
        }
    } else {
        int n = rnd.next(30, 160);
        int current = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 75) {
                dice.push_back(current);
            } else {
                current = rnd.next(1, 6);
                dice.push_back(current);
            }
        }
    }

    println((int)dice.size());
    println(dice);

    return 0;
}
