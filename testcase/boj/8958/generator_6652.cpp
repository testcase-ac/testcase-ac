#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases: keep total input under ~500 chars
    int T = rnd.next(1, 3);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        int L = rnd.next(1, 50);
        // Choose generation pattern based on length
        vector<string> patterns = {"random", "random", "allO", "allX", "alternating"};
        if (L >= 2) patterns.push_back("blocks");
        string pat = rnd.any(patterns);
        string s;
        if (pat == "random") {
            // Random O/X with random density
            double p = rnd.next(0.0, 1.0);
            for (int i = 0; i < L; i++) {
                s.push_back(rnd.next() < p ? 'O' : 'X');
            }
        } else if (pat == "allO") {
            s = string(L, 'O');
        } else if (pat == "allX") {
            s = string(L, 'X');
        } else if (pat == "alternating") {
            char c = rnd.any(string("OX"));
            for (int i = 0; i < L; i++) {
                s.push_back(c);
                c = (c == 'O' ? 'X' : 'O');
            }
        } else if (pat == "blocks") {
            // Create a few blocks of consecutive same chars
            int B = rnd.next(2, min(10, L));
            // pick B-1 cut points in [1, L-1]
            set<int> cuts;
            while ((int)cuts.size() < B - 1) {
                cuts.insert(rnd.next(1, L - 1));
            }
            vector<int> pts(cuts.begin(), cuts.end());
            pts.push_back(0);
            pts.push_back(L);
            sort(pts.begin(), pts.end());
            vector<int> sizes;
            for (int i = 1; i < (int)pts.size(); i++) {
                sizes.push_back(pts[i] - pts[i - 1]);
            }
            char c = rnd.any(string("OX"));
            for (int sz : sizes) {
                s.append(sz, c);
                c = (c == 'O' ? 'X' : 'O');
            }
        }
        println(s);
    }
    return 0;
}
