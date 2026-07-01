#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> gnumbers = {2, 3, 5, 7, 10, 11, 12, 14, 16, 20, 21, 23, 25, 29,
                            30, 32, 34, 38, 41, 43, 47, 49, 50, 52, 56, 58,
                            61, 65, 67, 70, 74, 76, 83, 85, 89, 92, 94, 98};
    vector<int> primePowers = {4, 8, 9, 16, 25, 27, 32, 49, 64, 81, 121, 125,
                               128, 169, 243, 256, 343, 512, 625, 729};
    vector<int> boundary = {2, 3, 4, 30, 999, 1000};

    int t = rnd.next(1, 100);
    println(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 5);
        int n;

        if (mode == 0) {
            n = rnd.any(gnumbers);
        } else if (mode == 1) {
            n = rnd.any(primePowers);
        } else if (mode == 2) {
            n = rnd.any(boundary);
        } else if (mode == 3) {
            int a = rnd.next(2, 31);
            int b = rnd.next(2, 31);
            n = a * b;
        } else if (mode == 4) {
            int base = rnd.any(vector<int>{6, 10, 12, 18, 20, 24, 30, 36});
            int multiplier = rnd.next(1, 1000 / base);
            n = base * multiplier;
        } else {
            n = rnd.next(2, 1000);
        }

        println(n);
    }

    return 0;
}
