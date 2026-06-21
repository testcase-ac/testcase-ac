#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    set<int> values;

    if (mode == 0) {
        int t = rnd.next(1, 12);
        int start = rnd.next(1, 20);
        for (int i = 0; i < t && start + i <= 5000; ++i) {
            values.insert(start + i);
        }
    } else if (mode == 1) {
        int t = rnd.next(2, 18);
        int parity = rnd.next(0, 1);
        int cur = parity + 1;
        while ((int)values.size() < t && cur <= 5000) {
            values.insert(cur);
            cur += 2 * rnd.next(1, 6);
        }
    } else if (mode == 2) {
        int t = rnd.next(1, 20);
        while ((int)values.size() < t) {
            values.insert(rnd.next(1, 120));
        }
    } else if (mode == 3) {
        int t = rnd.next(2, 16);
        while ((int)values.size() < t) {
            values.insert(rnd.next(4800, 5000));
        }
    } else if (mode == 4) {
        int t = rnd.next(20, 80);
        while ((int)values.size() < t) {
            values.insert(rnd.next(1, 5000));
        }
    } else {
        int t = rnd.next(1, 25);
        values.insert(1);
        values.insert(2);
        values.insert(4999);
        values.insert(5000);
        while ((int)values.size() < t) {
            values.insert(rnd.next(1, 5000));
        }
    }

    vector<int> n(values.begin(), values.end());
    println((int)n.size());
    println(n);

    return 0;
}
