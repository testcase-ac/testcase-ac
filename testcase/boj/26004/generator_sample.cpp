#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string need = "HIARC";
    const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string noise = "BDEFGJKLMNOPQSTUVWXYZ";

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    } else if (mode == 1) {
        int copies = rnd.next(1, 8);
        for (int i = 0; i < copies; ++i) s += need;
        int extra = rnd.next(0, 20);
        for (int i = 0; i < extra; ++i) s += rnd.any(alphabet);
        shuffle(s.begin(), s.end());
    } else if (mode == 2) {
        int missing = rnd.next(0, 4);
        int n = rnd.next(1, 35);
        string pool = noise;
        for (int i = 0; i < 5; ++i) {
            if (i != missing) pool += need[i];
        }
        for (int i = 0; i < n; ++i) s += rnd.any(pool);
    } else if (mode == 3) {
        vector<int> cnt(5);
        int base = rnd.next(0, 6);
        for (int i = 0; i < 5; ++i) cnt[i] = base + rnd.next(0, 5);
        cnt[rnd.next(0, 4)] = rnd.next(0, base);
        for (int i = 0; i < 5; ++i) {
            s += string(cnt[i], need[i]);
        }
        int extra = rnd.next(0, 15);
        for (int i = 0; i < extra; ++i) s += rnd.any(noise);
        if (s.empty()) s = string(1, rnd.any(noise));
        shuffle(s.begin(), s.end());
    } else if (mode == 4) {
        int copies = rnd.next(15, 60);
        for (int i = 0; i < copies; ++i) s += need;
        int extra = rnd.next(0, 100);
        for (int i = 0; i < extra; ++i) s += rnd.any(alphabet);
        shuffle(s.begin(), s.end());
    } else {
        int n = rnd.any(vector<int>{1, 2, 4, 5, 6, 10, 26, 100});
        for (int i = 0; i < n; ++i) {
            s += rnd.next(0, 99) < 75 ? rnd.any(need) : rnd.any(noise);
        }
    }

    println(static_cast<int>(s.size()));
    println(s);
    return 0;
}
