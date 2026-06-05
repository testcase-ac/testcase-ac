#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 5);
    int k = rnd.next(1, 4);

    vector<int> a(n, 0);
    int canMode = rnd.next(4);
    if (canMode == 0) {
        for (int i = 0; i < 2 * k; ++i) {
            ++a[rnd.next(n)];
        }
    } else if (canMode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 8);
        }
    } else if (canMode == 2) {
        int favorite = rnd.next(n);
        a[favorite] = rnd.next(2 * k, 8);
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, min(8, 2 * k));
        }
    }

    while (accumulate(a.begin(), a.end(), 0) < 2 * k) {
        int idx = rnd.next(n);
        if (a[idx] < 8) {
            ++a[idx];
        }
    }

    int prefMode = rnd.next(5);
    vector<vector<int>> r(k, vector<int>(n));
    vector<vector<int>> m(k, vector<int>(n));
    for (int day = 0; day < k; ++day) {
        for (int can = 0; can < n; ++can) {
            if (prefMode == 0) {
                r[day][can] = rnd.next(1, 100);
                m[day][can] = rnd.next(1, 100);
            } else if (prefMode == 1) {
                int base = rnd.next(1, 100);
                r[day][can] = base;
                m[day][can] = base;
            } else if (prefMode == 2) {
                r[day][can] = can + 1;
                m[day][can] = n - can;
            } else if (prefMode == 3) {
                int good = rnd.next(n);
                r[day][can] = (can == good ? 100 : rnd.next(1, 20));
                m[day][can] = (can == good ? 100 : rnd.next(1, 20));
            } else {
                r[day][can] = rnd.next(80, 100);
                m[day][can] = rnd.next(1, 25);
            }
        }
    }

    println(n, k);
    println(a);
    for (const auto& row : r) {
        println(row);
    }
    for (const auto& row : m) {
        println(row);
    }

    return 0;
}
