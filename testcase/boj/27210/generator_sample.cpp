#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 3);
        a.assign(n, rnd.next(1, 2));
    } else if (mode == 1) {
        n = rnd.next(4, 30);
        int first = rnd.next(1, 2);
        for (int i = 0; i < n; ++i) {
            a.push_back((i % 2 == 0) ? first : 3 - first);
        }
    } else if (mode == 2) {
        n = rnd.next(5, 45);
        int cur = rnd.next(1, 2);
        while ((int)a.size() < n) {
            int run = rnd.next(1, 8);
            for (int i = 0; i < run && (int)a.size() < n; ++i) {
                a.push_back(cur);
            }
            cur = 3 - cur;
        }
    } else if (mode == 3) {
        n = rnd.next(10, 60);
        int dominant = rnd.next(1, 2);
        int flips = rnd.next(1, n / 3);
        a.assign(n, dominant);
        for (int i = 0; i < flips; ++i) {
            a[rnd.next(0, n - 1)] = 3 - dominant;
        }
    } else if (mode == 4) {
        n = rnd.next(8, 55);
        int preferred = rnd.next(1, 2);
        int preferredPercent = rnd.next(55, 85);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 100) <= preferredPercent ? preferred : 3 - preferred);
        }
    } else {
        n = rnd.next(12, 70);
        int cur = rnd.next(1, 2);
        while ((int)a.size() < n) {
            int len = rnd.next(1, 10);
            int noise = rnd.next(0, 2);
            for (int i = 0; i < len && (int)a.size() < n; ++i) {
                if (noise > 0 && rnd.next(1, 100) <= 20) {
                    a.push_back(3 - cur);
                } else {
                    a.push_back(cur);
                }
            }
            cur = 3 - cur;
        }
    }

    println(n);
    println(a);

    return 0;
}
