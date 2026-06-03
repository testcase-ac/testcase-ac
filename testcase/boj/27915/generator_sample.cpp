#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> parent;

    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 25);
    } else if (mode == 2) {
        n = rnd.next(4, 25);
    } else if (mode == 3) {
        n = rnd.next(5, 40);
    } else if (mode == 4) {
        n = rnd.next(6, 45);
    } else if (mode == 5) {
        n = rnd.next(8, 60);
    } else {
        n = rnd.next(20, 100);
    }

    parent.assign(n + 1, 0);

    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = rnd.next(1, i - 1);
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = 1;
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = i - 1;
        }
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = i / 2;
        }
    } else if (mode == 4) {
        int spine = rnd.next(2, max(2, n / 2));
        for (int i = 2; i <= spine; ++i) {
            parent[i] = i - 1;
        }
        for (int i = spine + 1; i <= n; ++i) {
            parent[i] = rnd.next(1, spine);
        }
    } else if (mode == 5) {
        int hubs = rnd.next(2, min(8, n - 1));
        for (int i = 2; i <= hubs + 1; ++i) {
            parent[i] = 1;
        }
        for (int i = hubs + 2; i <= n; ++i) {
            parent[i] = rnd.next(2, hubs + 1);
        }
    } else {
        int bias = rnd.next(-3, 3);
        for (int i = 2; i <= n; ++i) {
            parent[i] = rnd.wnext(i - 1, bias) + 1;
        }
    }

    println(n);
    if (n > 1) {
        vector<int> line;
        for (int i = 2; i <= n; ++i) {
            line.push_back(parent[i]);
        }
        println(line);
    }

    return 0;
}
