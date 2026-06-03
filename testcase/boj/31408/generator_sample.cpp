#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a.push_back(rnd.next(1, 100000));
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        int dominant = rnd.next(1, 100000);
        int other = dominant == 100000 ? 99999 : dominant + 1;
        int cnt = (n + 1) / 2;

        a.assign(cnt, dominant);
        while ((int)a.size() < n) a.push_back(other);
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        int dominant = rnd.next(1, 100000);
        int other = dominant == 100000 ? 99999 : dominant + 1;
        int cnt = (n + 1) / 2 + 1;

        a.assign(cnt, dominant);
        while ((int)a.size() < n) a.push_back(other);
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        int start = rnd.next(1, 100000 - n + 1);
        for (int i = 0; i < n; ++i) a.push_back(start + i);
        shuffle(a.begin(), a.end());
    } else {
        n = rnd.next(3, 40);
        int kinds = rnd.next(2, min(n, 8));
        vector<int> labels;
        while ((int)labels.size() < kinds) {
            int x = rnd.next(1, 100000);
            bool seen = false;
            for (int y : labels) {
                if (x == y) {
                    seen = true;
                    break;
                }
            }
            if (!seen) labels.push_back(x);
        }

        int cap = mode == 4 ? (n + 1) / 2 : n;
        vector<int> counts(kinds, 1);
        int remaining = n - kinds;
        while (remaining > 0) {
            int i = rnd.next(0, kinds - 1);
            if (counts[i] == cap) continue;
            ++counts[i];
            --remaining;
        }

        for (int i = 0; i < kinds; ++i) {
            for (int j = 0; j < counts[i]; ++j) a.push_back(labels[i]);
        }
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
    return 0;
}
