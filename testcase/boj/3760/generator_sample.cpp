#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(1, 4);
    for (int tc = 0; tc < datasets; ++tc) {
        int n = rnd.next(1, 8);
        int mode = rnd.next(0, 4);
        int c = rnd.next(0, 40);

        if (mode == 1) {
            c = rnd.next(0, 5);
        } else if (mode == 2) {
            c = rnd.next(25, 100);
        }

        println(c);
        println(n);

        for (int y = 1; y <= n; ++y) {
            vector<int> row;
            for (int z = y; z <= n; ++z) {
                int span = z - y + 1;
                int value = 0;

                if (mode == 0) {
                    value = rnd.next(0, 30);
                } else if (mode == 1) {
                    value = span * rnd.next(0, 8) + rnd.next(0, 3);
                } else if (mode == 2) {
                    value = rnd.next(0, 12) + y + z;
                } else if (mode == 3) {
                    value = max(0, 60 - 7 * span + rnd.next(-5, 10));
                } else {
                    value = (y == z ? rnd.next(0, 12) : rnd.next(20, 80));
                }

                row.push_back(value);
            }
            println(row);
        }
    }

    return 0;
}
