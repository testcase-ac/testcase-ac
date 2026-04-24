#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // hyper-parameter for number of runners: 4..20, weighted small/medium/large
    vector<int> w = {-1, 0, 1};
    int tn = rnd.any(w);
    int n = rnd.wnext(17, tn) + 4;  // 0..16 + 4 => 4..20

    // generate unique names
    set<string> used;
    vector<string> names;
    while ((int)names.size() < n) {
        int L = rnd.next(2, 10);
        string s;
        for (int i = 0; i < L; i++) s += char('A' + rnd.next(0, 25));
        if (used.insert(s).second) names.push_back(s);
    }

    println(n);
    for (auto &s : names) {
        // flying-start time b_i: 8.00..19.99
        int tb = rnd.any(w);
        int boff = rnd.wnext(1200, tb);      // 0..1199
        int b_int = 800 + boff;              // 800..1999
        // first-leg slower time a_i: b_int..1999
        int maxd = 1999 - b_int;
        int delta = 0;
        if (maxd > 0) {
            double r = rnd.next();
            if (r < 0.3) delta = rnd.wnext(maxd+1, -1);  // small delta
            else if (r < 0.6) delta = rnd.next(0, maxd);  // uniform
            else delta = rnd.wnext(maxd+1, 1);           // large delta
        }
        int a_int = b_int + delta;
        double a = a_int / 100.0;
        double b = b_int / 100.0;
        printf("%s %.2f %.2f\n", s.c_str(), a, b);
    }
    return 0;
}
