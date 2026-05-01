#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

bool isLeapJulian(int y) {
    return y % 4 == 0;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 10);
    vector<string> specials = {
        "1582-10-04",
        "1752-09-02",
        "1900-02-25",
        "1923-02-15",
        "9999-10-18"
    };
    int use = min(T, (int)specials.size());
    vector<string> dates;
    for (int i = 0; i < use; i++) {
        dates.push_back(specials[i]);
    }
    int totalYears = 9999 - 1582 + 1; // 8418
    vector<int> t_params = {-5, -3, -1, 0, 1, 3, 5};
    for (int i = use; i < T; i++) {
        int t = rnd.any(t_params.begin(), t_params.end());
        int yidx = rnd.wnext(totalYears, t); // [0, totalYears-1]
        int y = 1582 + yidx;
        int m;
        if (y == 1582) {
            m = rnd.next(10, 12);
        } else if (y == 9999) {
            m = rnd.next(1, 10);
        } else {
            m = rnd.next(1, 12);
        }
        int maxd;
        if (m == 2) {
            maxd = isLeapJulian(y) ? 29 : 28;
        } else if (m == 4 || m == 6 || m == 9 || m == 11) {
            maxd = 30;
        } else {
            maxd = 31;
        }
        int mind = 1, maxd2 = maxd;
        if (y == 1582 && m == 10) mind = 4;
        if (y == 9999 && m == 10) maxd2 = 18;
        int d = rnd.next(mind, maxd2);
        char buf[12];
        sprintf(buf, "%04d-%02d-%02d", y, m, d);
        dates.push_back(string(buf));
    }
    shuffle(dates.begin(), dates.end());
    for (auto &s : dates) {
        println(s);
    }
    return 0;
}
