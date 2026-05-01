#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool is_leap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

int days_in_month(int y, int m) {
    static int dm[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && is_leap(y)) return 29;
    return dm[m];
}

bool is_nice(int D, int M, int Y) {
    // digit frequency
    vector<int> cnt(10,0);
    string s = to_string(D) + to_string(M) + to_string(Y);
    for(char c: s) cnt[c-'0']++;
    int target = -1;
    for(int d = 0; d < 10; d++) {
        if (cnt[d] == 0) continue;
        if (target == -1) target = cnt[d];
        else if (cnt[d] != target) return false;
    }
    // split sums
    int a = D, b = M, c = Y/100, d = Y%100;
    int vals[4] = {a,b,c,d};
    int tot = a+b+c+d;
    for(int mask = 1; mask < (1<<4)-1; mask++) {
        int s = 0;
        for(int i = 0; i < 4; i++)
            if (mask & (1<<i)) s += vals[i];
        if (s * 2 == tot) return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // randomize a year window for diversity
    int ylo = rnd.next(1000, 9000);
    int span = rnd.next(100, 500);
    int yhi = min(9999, ylo + span);
    vector<tuple<int,int,int>> niceDates;
    for(int y = ylo; y <= yhi; y++) {
        for(int m = 1; m <= 12; m++) {
            int dm = days_in_month(y, m);
            for(int d = 1; d <= dm; d++) {
                if (is_nice(d, m, y))
                    niceDates.emplace_back(d, m, y);
            }
        }
    }
    // if too few nice, expand search
    if ((int)niceDates.size() < 10) {
        niceDates.clear();
        for(int y = 1000; y <= 9999; y++) {
            for(int m = 1; m <= 12; m++) {
                int dm = days_in_month(y, m);
                for(int d = 1; d <= dm; d++) {
                    if (is_nice(d, m, y))
                        niceDates.emplace_back(d, m, y);
                }
            }
        }
    }
    shuffle(niceDates.begin(), niceDates.end());
    int T = rnd.next(5, 15);
    println(T);
    for(int i = 0; i < T; i++) {
        bool wantNice = (rnd.next(0,1) == 0) && !niceDates.empty();
        if (wantNice) {
            auto [d,m,y] = rnd.any(niceDates);
            println(d, m, y);
        } else {
            // generate a non-nice random valid date
            int d,m,y;
            do {
                y = rnd.next(1000, 9999);
                m = rnd.next(1, 12);
                d = rnd.next(1, days_in_month(y, m));
            } while (is_nice(d, m, y));
            println(d, m, y);
        }
    }
    return 0;
}
