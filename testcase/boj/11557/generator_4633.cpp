#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int tc = 0; tc < T; ++tc) {
        // Hyper-parameter: choose N small, medium, or large
        double p = rnd.next();
        int N;
        if (p < 0.3) N = rnd.next(1, 3);
        else if (p < 0.7) N = rnd.next(4, 7);
        else N = rnd.next(8, 10);

        // Hyper-parameter: choose max consumption range
        double p2 = rnd.next();
        int maxL;
        if (p2 < 0.3) maxL = 100;
        else if (p2 < 0.6) maxL = 10000;
        else maxL = 10000000;

        // Generate N distinct consumption values
        set<int> s;
        while ((int)s.size() < N) {
            s.insert(rnd.next(0, maxL));
        }
        vector<int> Ls(s.begin(), s.end());
        shuffle(Ls.begin(), Ls.end());

        // Generate N random school names
        vector<string> names;
        for (int i = 0; i < N; ++i) {
            double p3 = rnd.next();
            int len;
            if (p3 < 0.3) len = rnd.next(1, 3);
            else if (p3 < 0.7) len = rnd.next(4, 8);
            else len = rnd.next(9, 20);
            string name;
            for (int j = 0; j < len; ++j) {
                name.push_back(rnd.any(letters));
            }
            names.push_back(name);
        }

        // Pair up names and values and shuffle
        vector<pair<string,int>> v;
        for (int i = 0; i < N; ++i) {
            v.emplace_back(names[i], Ls[i]);
        }
        shuffle(v.begin(), v.end());

        // Output this test case
        println(N);
        for (auto &pr : v) {
            println(pr.first, pr.second);
        }
    }
    return 0;
}
