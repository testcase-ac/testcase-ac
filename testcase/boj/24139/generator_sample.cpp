#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 14);

    vector<int> parent(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        if (mode == 0) {
            parent[i] = i - 1;
        } else if (mode == 1) {
            parent[i] = 1;
        } else if (mode == 2) {
            parent[i] = i / 2;
        } else if (mode == 3) {
            parent[i] = rnd.next(max(1, i - 3), i - 1);
        } else if (mode == 4) {
            parent[i] = rnd.next(1, i - 1);
        } else {
            parent[i] = rnd.wnext(i - 1, -2) + 1;
        }
    }

    int valueMode = rnd.next(0, 5);
    vector<int> motivation(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (valueMode == 0) {
            motivation[i] = rnd.next(-5, 5);
        } else if (valueMode == 1) {
            motivation[i] = rnd.next(-100, -1);
        } else if (valueMode == 2) {
            motivation[i] = rnd.next(1, 100);
        } else if (valueMode == 3) {
            motivation[i] = (i % 2 == 0) ? rnd.next(-100, -20) : rnd.next(20, 100);
        } else if (valueMode == 4) {
            motivation[i] = rnd.any(vector<int>{-100, -1, 0, 1, 100});
        } else {
            motivation[i] = rnd.next(-100, 100);
        }
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        println(parent[i], motivation[i]);
    }

    return 0;
}
