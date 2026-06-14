#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 20);
    } else if (mode == 2) {
        n = rnd.next(2, 25);
    } else if (mode == 3) {
        n = rnd.next(3, 31);
    } else if (mode == 4) {
        n = rnd.next(4, 30);
    } else {
        n = rnd.next(2, 35);
    }

    vector<int> parent(n + 1, 0);
    if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = i - 1;
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = 1;
        }
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = i / 2;
        }
    } else if (mode == 4) {
        int spine = rnd.next(2, n - 1);
        for (int i = 2; i <= spine; ++i) {
            parent[i] = i - 1;
        }
        for (int i = spine + 1; i <= n; ++i) {
            parent[i] = rnd.next(1, spine);
        }
    } else if (mode == 5) {
        int bias = rnd.next(-3, 3);
        for (int i = 2; i <= n; ++i) {
            parent[i] = rnd.wnext(i - 1, bias) + 1;
        }
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    vector<int> output_parent(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        output_parent[label[i]] = label[parent[i]];
    }

    println(n);
    println(vector<int>(output_parent.begin() + 1, output_parent.end()));

    return 0;
}
