#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int s;
    int e;
    int t;
    vector<string> a;

    if (mode == 0) {
        n = 1;
        s = e = 1;
        t = rnd.next(1, 30);
        a.assign(1, string(1, char('0' + rnd.next(0, 5))));
    } else {
        n = rnd.next(2, 10);
        s = rnd.next(1, n);
        e = rnd.next(1, n);
        a.assign(n, string(n, '0'));

        if (mode == 1) {
            t = rnd.next(1, 25);
            for (int i = 0; i + 1 < n; ++i) {
                a[i][i + 1] = char('1' + rnd.next(0, 4));
            }
            for (int i = 0; i < n; ++i) {
                if (rnd.next(0, 1)) {
                    a[i][i] = char('1' + rnd.next(0, 4));
                }
            }
        } else if (mode == 2) {
            t = rnd.next(1, 80);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (rnd.next(0, 99) < 25) {
                        a[i][j] = char('1' + rnd.next(0, 4));
                    }
                }
            }
        } else if (mode == 3) {
            t = rnd.next(1, 200);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (rnd.next(0, 99) < 75) {
                        a[i][j] = char('1' + rnd.next(0, 4));
                    }
                }
            }
        } else if (mode == 4) {
            t = rnd.next(100000000, 1000000000);
            for (int i = 0; i < n; ++i) {
                int next = (i + 1) % n;
                a[i][next] = char('1' + rnd.next(0, 4));
                if (rnd.next(0, 2) == 0) {
                    a[i][i] = char('1' + rnd.next(0, 4));
                }
            }
        } else {
            t = rnd.next(1, 1000000000);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    int weight = rnd.next(0, 5);
                    a[i][j] = char('0' + weight);
                }
            }
        }
    }

    println(n, s, e, t);
    for (const string& row : a) {
        println(row);
    }

    return 0;
}
