#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int k = 1;
    vector<int> capacity;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(n, n + 20);
        capacity.assign(n, 0);
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        k = rnd.next(n, n * 4 + 8);
        int portion = rnd.next(1, 300);
        capacity.resize(n);
        for (int i = 0; i < n; ++i) {
            int pieces = rnd.next(0, 5);
            capacity[i] = portion * pieces;
        }
        if (*max_element(capacity.begin(), capacity.end()) == 0) {
            capacity[rnd.next(n)] = portion * rnd.next(1, 5);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        int target = rnd.next(1, 250);
        k = rnd.next(n, n * 5 + 10);
        capacity.resize(n);
        for (int i = 0; i < n; ++i) {
            int pieces = rnd.next(0, 4);
            capacity[i] = target * pieces + rnd.next(0, target - 1);
        }
    } else if (mode == 3) {
        n = rnd.next(1, 6);
        k = rnd.next(n, n + 12);
        capacity.assign(n, 0);
        capacity[rnd.next(n)] = rnd.next(1000000000, 2147483647);
    } else if (mode == 4) {
        n = rnd.next(3, 12);
        k = rnd.next(n, 100);
        capacity.resize(n);
        for (int i = 0; i < n; ++i) {
            capacity[i] = rnd.next(0, 1000);
        }
    } else {
        n = rnd.next(1, 12);
        k = rnd.next(n, 1000000);
        capacity.resize(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                capacity[i] = 0;
            } else {
                capacity[i] = rnd.next(1, 5000);
            }
        }
    }

    shuffle(capacity.begin(), capacity.end());

    println(n, k);
    for (int x : capacity) {
        println(x);
    }

    return 0;
}
