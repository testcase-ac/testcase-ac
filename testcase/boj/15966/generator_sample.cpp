#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    vector<int> a;

    if (mode == 0) {
        int start = rnd.next(1, 1000000 - n + 1);
        for (int i = 0; i < n; ++i) a.push_back(start + i);
    } else if (mode == 1) {
        int runLen = rnd.next(1, n);
        int start = rnd.next(1, 1000000 - runLen + 1);
        int noiseBase = rnd.next(1, 999900);
        for (int i = 0; i < runLen; ++i) {
            a.push_back(start + i);
            if ((int)a.size() < n && rnd.next(0, 1)) {
                a.push_back(min(1000000, noiseBase + rnd.next(0, 100)));
            }
        }
        while ((int)a.size() < n) a.push_back(rnd.next(1, 1000000));
    } else if (mode == 2) {
        int start = rnd.next(1, 999990);
        for (int i = 0; i < n; ++i) {
            int offset = rnd.next(0, min(9, n + 2));
            a.push_back(start + offset);
        }
    } else if (mode == 3) {
        int start = rnd.next(n, 1000000);
        for (int i = 0; i < n; ++i) a.push_back(start - i);
    } else if (mode == 4) {
        int runLen = rnd.next(1, n);
        int start = rnd.next(1, 1000000 - runLen + 1);
        vector<int> run;
        for (int i = 0; i < runLen; ++i) run.push_back(start + i);
        shuffle(run.begin(), run.end());
        a = run;
        while ((int)a.size() < n) a.push_back(rnd.any(run));
    } else {
        int base = rnd.next(0, 1) ? rnd.next(1, 20) : rnd.next(999980, 1000000);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-10, 10);
            a.push_back(max(1, min(1000000, base + delta)));
        }
    }

    a.resize(n);
    println(n);
    println(a);

    return 0;
}
