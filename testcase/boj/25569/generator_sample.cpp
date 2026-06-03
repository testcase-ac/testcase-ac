#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode <= 3) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(8, 25);
    }

    vector<pair<int, int>> editors;
    editors.reserve(n);

    for (int i = 0; i < n; ++i) {
        int a = 1;
        int b = 1;

        if (mode == 0) {
            int v = rnd.next(1, 6);
            a = v;
            b = v;
        } else if (mode == 1) {
            a = rnd.next(1, 12);
            b = rnd.next(1, 12);
        } else if (mode == 2) {
            if (rnd.next(0, 1) == 0) {
                a = 1;
                b = rnd.any(vector<int>{1, 2, 3, 10, 1000, 300000});
            } else {
                a = rnd.any(vector<int>{1, 2, 3, 10, 1000, 300000});
                b = 1;
            }
        } else if (mode == 3) {
            int hi = rnd.any(vector<int>{20, 100, 1000, 300000});
            a = rnd.next(1, hi);
            b = rnd.next(1, hi);
        } else if (mode == 4) {
            a = rnd.next(299990, 300000);
            b = rnd.next(299990, 300000);
        } else {
            int pattern = rnd.next(0, 3);
            if (pattern == 0) {
                a = rnd.next(1, 5);
                b = rnd.next(1, 300000);
            } else if (pattern == 1) {
                a = rnd.next(1, 300000);
                b = rnd.next(1, 5);
            } else if (pattern == 2) {
                a = rnd.next(1, 50);
                b = rnd.next(1, 50);
            } else {
                a = rnd.next(299950, 300000);
                b = rnd.next(299950, 300000);
            }
        }

        editors.emplace_back(a, b);
    }

    if (rnd.next(0, 1) == 1) {
        shuffle(editors.begin(), editors.end());
    }

    println(n);
    for (const auto& editor : editors) {
        println(editor.first, editor.second);
    }

    return 0;
}
