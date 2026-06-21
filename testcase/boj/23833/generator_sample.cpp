#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 30);
    int q = rnd.next(1, 80);
    int maxColor = rnd.next(1, 100);

    vector<int> flowers(n);
    if (mode == 0) {
        fill(flowers.begin(), flowers.end(), rnd.next(1, maxColor));
    } else if (mode == 1) {
        int first = rnd.next(1, maxColor);
        int second = rnd.next(1, maxColor);
        for (int i = 0; i < n; ++i) {
            flowers[i] = (i % 2 == 0 ? first : second);
        }
    } else if (mode == 2) {
        int current = rnd.next(1, maxColor);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && rnd.next(0, 99) < 35) {
                current = rnd.next(1, maxColor);
            }
            flowers[i] = current;
        }
    } else {
        for (int i = 0; i < n; ++i) {
            flowers[i] = rnd.next(1, maxColor);
        }
    }

    println(n, q);
    println(flowers);

    bool hasQuery = false;
    for (int i = 0; i < q; ++i) {
        bool forceQuery = (i == q - 1 && !hasQuery);
        bool makeQuery = forceQuery || rnd.next(0, 99) < 60;

        if (makeQuery) {
            int a = rnd.next(1, n);
            int b;
            if (rnd.next(0, 99) < 25) {
                b = a;
            } else if (rnd.next(0, 99) < 35) {
                b = n;
            } else {
                b = rnd.next(a, n);
            }
            println(1, a, b);
            hasQuery = true;
        } else {
            int a = rnd.next(1, n);
            int color;
            if (rnd.next(0, 99) < 30) {
                color = flowers[a - 1];
            } else if (n > 1 && rnd.next(0, 99) < 45) {
                int neighbor = a - 1;
                if (a == 1) {
                    neighbor = 1;
                } else if (a == n) {
                    neighbor = n - 2;
                } else {
                    neighbor += rnd.next(0, 1) == 0 ? -1 : 1;
                }
                color = flowers[neighbor];
            } else {
                color = rnd.next(1, maxColor);
            }
            println(2, a, color);
            flowers[a - 1] = color;
        }
    }

    return 0;
}
