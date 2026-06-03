#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    vector<int> a;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        a.assign(n, 0);
    } else if (mode == 1) {
        int n = rnd.next(2, 14);
        vector<int> pool = {0, 1, 10, 100, 1000, 1000000000};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 2) {
        int n = rnd.next(3, 14);
        vector<int> pool = {12, 121, 1212, 120, 9, 91, 90, 909};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 3) {
        int n = rnd.next(3, 15);
        int prefix = rnd.next(1, 9);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, 5);
            string s(len, char('0' + prefix));
            if (rnd.next(0, 2) == 0) {
                s += char('0' + rnd.next(0, 9));
            }
            a.push_back(stoi(s));
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 13);
        int lo = rnd.next(0, 999);
        int hi = rnd.next(lo, min(1000000000, lo + rnd.next(0, 10000)));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    } else if (mode == 5) {
        int n = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            int digits = rnd.next(1, 10);
            string s;
            s += char('1' + rnd.next(0, 8));
            for (int j = 1; j < digits; ++j) s += char('0' + rnd.next(0, 9));
            long long value = stoll(s);
            if (value > 1000000000LL) value = rnd.next(100000000, 1000000000);
            a.push_back((int)value);
        }
    } else if (mode == 6) {
        int n = rnd.next(4, 16);
        vector<int> pool = {3, 30, 34, 5, 9, 95, 959, 1000000000, 0};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else {
        int n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, 1000000000));
    }

    shuffle(a.begin(), a.end());
    println((int)a.size());
    println(a);

    return 0;
}
