#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string all = "UDPC";
    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 40);
    string v;

    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) v += rnd.any(all);
    } else if (mode == 1) {
        n = rnd.next(1, 60);
        char c = rnd.any(all);
        v.assign(n, c);
    } else if (mode == 2) {
        n = rnd.next(2, 80);
        string letters = rnd.next(0, 1) ? "UC" : "DP";
        for (int i = 0; i < n; ++i) v += rnd.any(letters);
    } else if (mode == 3) {
        int uc = rnd.next(1, 40);
        int dp = rnd.next(max(1, uc - 3), uc + 3);
        for (int i = 0; i < uc; ++i) v += rnd.any(string("UC"));
        for (int i = 0; i < dp; ++i) v += rnd.any(string("DP"));
        shuffle(v.begin(), v.end());
    } else if (mode == 4) {
        vector<int> cnt(4);
        int base = rnd.next(1, 20);
        for (int i = 0; i < 4; ++i) cnt[i] = max(0, base + rnd.next(-2, 2));
        for (int i = 0; i < 4; ++i) v += string(cnt[i], all[i]);
        shuffle(v.begin(), v.end());
    } else if (mode == 5) {
        n = rnd.next(30, 120);
        char major = rnd.any(all);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                v += rnd.any(all);
            } else {
                v += major;
            }
        }
    } else if (mode == 6) {
        n = rnd.next(80, 500);
        for (int i = 0; i < n; ++i) v += rnd.any(all);
    } else {
        n = 100000;
        string pattern = rnd.next(0, 1) ? "UDPC" : "UCDP";
        for (int i = 0; i < n; ++i) v += pattern[i % 4];
    }

    println(v);
    return 0;
}
