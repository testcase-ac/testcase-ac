#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int p = rnd.next(1, 12);
    println(p);

    for (int tc = 1; tc <= p; ++tc) {
        int mode = rnd.next(0, 5);
        int hi = rnd.next(3, 30);
        vector<int> a(12, 0);

        if (mode == 0) {
            int value = rnd.next(0, hi);
            fill(a.begin() + 1, a.end() - 1, value);
        } else if (mode == 1) {
            for (int i = 1; i <= 10; ++i) {
                a[i] = rnd.next(0, hi);
            }
            sort(a.begin() + 1, a.end() - 1);
            if (rnd.next(0, 1)) {
                reverse(a.begin() + 1, a.end() - 1);
            }
        } else if (mode == 2) {
            int low = rnd.next(0, min(4, hi - 1));
            int high = rnd.next(low + 1, hi);
            for (int i = 1; i <= 10; ++i) {
                a[i] = (i % 2 == 0) ? high : low;
                if (rnd.next(0, 3) == 0) {
                    a[i] = rnd.next(low, high);
                }
            }
        } else if (mode == 3) {
            int blocks = rnd.next(2, 5);
            vector<int> cuts;
            for (int i = 1; i <= 9; ++i) {
                cuts.push_back(i);
            }
            shuffle(cuts.begin(), cuts.end());
            cuts.resize(blocks - 1);
            sort(cuts.begin(), cuts.end());
            cuts.push_back(10);

            int prev = 0;
            int pos = 1;
            for (int b = 0; b < blocks; ++b) {
                int value = rnd.next(0, hi);
                int len = cuts[b] - prev;
                for (int i = 0; i < len; ++i) {
                    a[pos++] = value;
                }
                prev = cuts[b];
            }
        } else if (mode == 4) {
            int cur = rnd.next(0, hi);
            for (int i = 1; i <= 10; ++i) {
                cur += rnd.next(0, 6) - 3;
                cur = max(0, min(hi, cur));
                a[i] = cur;
            }
        } else {
            for (int i = 1; i <= 10; ++i) {
                a[i] = rnd.next(0, hi);
            }
            if (rnd.next(0, 4) == 0) {
                a[rnd.next(1, 10)] = rnd.next(1000, 1000000000);
            }
        }

        int k = rnd.next(1, 1000000000);
        vector<int> line;
        line.push_back(k);
        line.insert(line.end(), a.begin(), a.end());
        println(line);
    }

    return 0;
}
