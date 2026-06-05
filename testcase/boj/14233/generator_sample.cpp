#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

static void addUnique(vector<int>& a, set<int>& used, int x) {
    if (1 <= x && x <= 1000000000 && used.insert(x).second) {
        a.push_back(x);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 30);
    vector<int> a;
    set<int> used;

    if (mode == 0) {
        int start = rnd.next(1, 20);
        int step = rnd.next(1, 5);
        n = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            addUnique(a, used, start + i * step);
        }
    } else if (mode == 1) {
        int k = rnd.next(1, 1000000);
        n = rnd.next(2, 25);
        for (int i = 1; i <= n; ++i) {
            int slack = rnd.next(0, min(1000, k));
            addUnique(a, used, i * k + slack);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 18);
        for (int i = 0; i < n; ++i) {
            addUnique(a, used, 1000000000 - i * rnd.next(1, 1000));
        }
    } else if (mode == 3) {
        n = rnd.next(1, 30);
        while ((int)a.size() < n) {
            addUnique(a, used, rnd.next(1, 200));
        }
    } else {
        n = rnd.next(5, 40);
        while ((int)a.size() < n) {
            addUnique(a, used, rnd.next(1, 1000000000));
        }
    }

    shuffle(a.begin(), a.end());
    println((int)a.size());
    println(a);

    return 0;
}
