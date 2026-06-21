#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> rungs;

    if (mode == 0) {
        n = 1;
    } else {
        n = rnd.next(2, 15);
        int maxRungs = rnd.next(1, 40);

        if (mode == 1) {
            int a = rnd.next(1, n - 1);
            int m = rnd.next(1, maxRungs);
            rungs.assign(m, a);
        } else if (mode == 2) {
            int start = rnd.next(1, n - 1);
            int m = rnd.next(1, maxRungs);
            for (int i = 0; i < m; ++i) {
                rungs.push_back((start + i - 1) % (n - 1) + 1);
            }
        } else if (mode == 3) {
            int current = rnd.next(1, n - 1);
            int m = rnd.next(1, maxRungs);
            for (int i = 0; i < m; ++i) {
                rungs.push_back(current);
                if (n > 2) {
                    int delta = rnd.next(0, 2) - 1;
                    current += delta;
                    if (current < 1) current = 1;
                    if (current > n - 1) current = n - 1;
                }
            }
        } else {
            int m = rnd.next(0, maxRungs);
            for (int i = 0; i < m; ++i) {
                rungs.push_back(rnd.next(1, n - 1));
            }
        }
    }

    println(n, static_cast<int>(rungs.size()));
    for (int a : rungs) {
        println(a);
    }

    return 0;
}
