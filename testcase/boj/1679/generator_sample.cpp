#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int k = 1;
    set<int> values;
    values.insert(1);

    if (mode == 0) {
        n = rnd.next(1, 4);
        k = rnd.next(1, 8);
        for (int x = 2; (int)values.size() < n; ++x) {
            values.insert(x);
        }
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = rnd.next(1, 15);
        int limit = rnd.next(n, 30);
        while ((int)values.size() < n) {
            values.insert(rnd.next(2, limit));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        k = rnd.next(10, 50);
        int current = 1;
        while ((int)values.size() < n) {
            current += rnd.next(1, 80);
            values.insert(min(current, 1000));
            if (current >= 1000) {
                while ((int)values.size() < n) {
                    values.insert(rnd.next(2, 1000));
                }
            }
        }
    } else if (mode == 3) {
        n = rnd.next(2, 15);
        k = rnd.next(1, 50);
        while ((int)values.size() < n) {
            if (rnd.next(0, 2) == 0) {
                values.insert(rnd.next(2, 40));
            } else {
                values.insert(rnd.next(900, 1000));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(20, 60);
        k = rnd.next(1, 50);
        while ((int)values.size() < n) {
            values.insert(rnd.next(2, 1000));
        }
    } else {
        n = rnd.next(2, 25);
        k = rnd.next(1, 50);
        int step = rnd.next(2, 20);
        int start = rnd.next(1, step);
        for (int x = start; x <= 1000 && (int)values.size() < n; x += step) {
            values.insert(x);
        }
        while ((int)values.size() < n) {
            values.insert(rnd.next(2, 1000));
        }
    }

    vector<int> a(values.begin(), values.end());
    println((int)a.size());
    println(a);
    println(k);

    return 0;
}
