#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int current;
    vector<int> dims;

    if (mode == 0) {
        n = rnd.next(2, 6);
        current = rnd.next(1, 12);
        dims.assign(n + 1, current);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        current = rnd.next(n + 1, 40);
        dims.push_back(current);
        for (int i = 0; i < n; ++i) {
            current -= rnd.next(0, min(4, current - 1));
            dims.push_back(current);
        }
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        current = rnd.next(20, 200);
        dims.push_back(current);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 35) {
                current = rnd.next(1, current);
            } else {
                current -= rnd.next(0, min(10, current - 1));
            }
            dims.push_back(current);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 15);
        current = rnd.next(1000, 10000);
        dims.push_back(current);
        for (int i = 0; i < n; ++i) {
            int low = max(1, current / 3);
            current = rnd.next(low, current);
            dims.push_back(current);
        }
    } else if (mode == 4) {
        n = rnd.next(20, 80);
        current = rnd.next(50, 500);
        dims.push_back(current);
        for (int i = 0; i < n; ++i) {
            current -= rnd.next(0, min(3, current - 1));
            dims.push_back(current);
        }
    } else {
        n = rnd.next(2, 8);
        current = rnd.next(9000, 10000);
        dims.push_back(current);
        for (int i = 0; i < n - 1; ++i) {
            current = rnd.next(2, current);
            dims.push_back(current);
        }
        dims.push_back(1);
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(dims[i], dims[i + 1]);
    }

    return 0;
}
