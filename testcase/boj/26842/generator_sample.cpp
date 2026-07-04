#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;

    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 25);
    } else if (mode == 2) {
        n = rnd.next(2, 30);
    } else if (mode == 3) {
        n = rnd.next(3, 31);
    } else if (mode == 4) {
        n = rnd.next(4, 35);
    } else if (mode == 5) {
        n = rnd.next(5, 32);
    } else {
        n = rnd.next(6, 36);
    }

    int k;
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = n;
    } else if (kMode == 2) {
        k = max(1, n / 2 + rnd.next(-1, 1));
    } else if (kMode == 3) {
        k = rnd.next(1, min(n, 5));
    } else {
        k = rnd.next(1, n);
    }

    println(n, k);

    vector<int> parent(n + 1);
    for (int employee = 2; employee <= n; ++employee) {
        if (mode == 0) {
            parent[employee] = rnd.next(1, employee - 1);
        } else if (mode == 1) {
            parent[employee] = employee - 1;
        } else if (mode == 2) {
            parent[employee] = 1;
        } else if (mode == 3) {
            parent[employee] = employee / 2;
        } else if (mode == 4) {
            parent[employee] = rnd.wnext(employee - 1, -2) + 1;
        } else if (mode == 5) {
            int chainEnd = max(2, n / 2);
            parent[employee] = employee <= chainEnd ? employee - 1 : rnd.next(1, chainEnd);
        } else {
            int block = max(2, rnd.next(2, 5));
            int blockRoot = max(1, employee - (employee - 2) % block - 1);
            parent[employee] = rnd.next(max(1, blockRoot), employee - 1);
        }
    }

    for (int employee = 2; employee <= n; ++employee) {
        println(parent[employee]);
    }

    return 0;
}
