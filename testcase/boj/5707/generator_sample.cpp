#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(2, 5);
    for (int tc = 0; tc < testCases; ++tc) {
        int mode = rnd.next(5);
        int n = rnd.next(2, 10);
        int r = rnd.next(2, 8);
        int c = rnd.next(2, 8);
        int k = rnd.next(1, 12);

        if (mode == 1) {
            n = rnd.next(2, 4);
            r = rnd.next(2, 5);
            c = rnd.next(2, 5);
            k = rnd.next(8, 25);
        } else if (mode == 2) {
            n = rnd.next(8, 20);
            r = rnd.next(2, 4);
            c = rnd.next(2, 5);
            k = rnd.next(1, 4);
        } else if (mode == 3) {
            n = rnd.next(2, 6);
            r = rnd.next(6, 10);
            c = rnd.next(2, 4);
            k = rnd.next(1, 10);
        }

        println(n, r, c, k);
        for (int i = 0; i < r; ++i) {
            vector<int> row;
            row.reserve(c);
            for (int j = 0; j < c; ++j) {
                int value;
                if (mode == 0) {
                    value = rnd.next(n);
                } else if (mode == 1) {
                    value = (i + j + rnd.next(2)) % n;
                } else if (mode == 2) {
                    value = rnd.next(max(1, n - 3), n - 1);
                    if (rnd.next(4) == 0) {
                        value = rnd.next(0, min(n - 1, 2));
                    }
                } else if (mode == 3) {
                    value = i % n;
                    if (rnd.next(5) == 0) {
                        value = (value + 1) % n;
                    }
                } else {
                    value = ((i / 2) + (j / 2) + rnd.next(3)) % n;
                }
                row.push_back(value);
            }
            println(row);
        }
    }

    println(0, 0, 0, 0);
    return 0;
}
