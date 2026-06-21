#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(3, 12);
    vector<vector<int>> a(n, vector<int>(n, 0));

    auto setEdge = [&](int i, int j, int value) {
        a[i][j] = value;
        a[j][i] = value;
    };

    if (mode == 0) {
        int low = rnd.next(1, 20);
        int high = rnd.next(low, 100);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                setEdge(i, j, rnd.next(low, high));
            }
        }
    } else if (mode == 1) {
        int weak = rnd.next(1, 10);
        int strong = rnd.next(weak + 1, weak + 50);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                setEdge(i, j, (i % 2 == j % 2) ? strong + rnd.next(0, 5)
                                                : weak + rnd.next(0, 3));
            }
        }
    } else if (mode == 2) {
        int weak = rnd.next(1, 15);
        int strong = rnd.next(weak + 10, weak + 80);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int value = strong + rnd.next(0, 10);
                if ((j == i + 1) || (i == 0 && j == n - 1)) {
                    value = weak + rnd.next(0, 4);
                }
                setEdge(i, j, value);
            }
        }
    } else if (mode == 3) {
        int pivot = rnd.next(2, n - 1);
        int weak = rnd.next(1, 30);
        int medium = rnd.next(weak + 1, weak + 30);
        int strong = rnd.next(medium + 1, medium + 70);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int value = (i < pivot && j < pivot) || (i >= pivot && j >= pivot)
                                ? strong + rnd.next(0, 8)
                                : medium + rnd.next(0, 8);
                if (rnd.next(5) == 0) {
                    value = weak + rnd.next(0, 4);
                }
                setEdge(i, j, value);
            }
        }
    } else {
        int base = rnd.next(1, 1000000 - 200);
        vector<int> labels(n);
        for (int i = 0; i < n; ++i) {
            labels[i] = rnd.next(0, 20);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int spread = abs(labels[i] - labels[j]) * rnd.next(1, 7);
                setEdge(i, j, min(1000000, base + spread + rnd.next(0, 15)));
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
