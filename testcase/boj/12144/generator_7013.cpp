#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // number of unknown sentences U, total N = 2 + U
        int U = rnd.next(0, 6);
        int N = 2 + U;
        // vocabulary sizes
        int en = rnd.next(1, 6);
        int fr = rnd.next(1, 6);
        int ov = rnd.next(0, min(en, fr));
        // word generator
        int wc = 0;
        auto newWord = [&]() {
            int idx = wc++;
            char c1 = 'a' + (idx / 26) % 26;
            char c2 = 'a' + (idx % 26);
            return string{c1, c2};
        };
        // build overlap, unique English, unique French
        vector<string> overlap, uniqueE, uniqueF;
        for (int i = 0; i < ov; i++) overlap.push_back(newWord());
        for (int i = 0; i < en - ov; i++) uniqueE.push_back(newWord());
        for (int i = 0; i < fr - ov; i++) uniqueF.push_back(newWord());
        vector<string> E_set = overlap, F_set = overlap;
        E_set.insert(E_set.end(), uniqueE.begin(), uniqueE.end());
        F_set.insert(F_set.end(), uniqueF.begin(), uniqueF.end());
        shuffle(E_set.begin(), E_set.end());
        shuffle(F_set.begin(), F_set.end());
        // weights for random unknowns
        int wE = rnd.next(1, 5), wF = rnd.next(1, 5), wN = rnd.next(1, 5);
        // output
        println(N);
        println(E_set);
        println(F_set);
        // unknown sentences
        for (int i = 0; i < U; i++) {
            vector<string> sen;
            if (i == 0) {
                // only English words
                int L = rnd.next(1, max(1, (int)E_set.size()));
                for (int j = 0; j < L; j++) sen.push_back(rnd.any(E_set));
            } else if (i == 1) {
                // only French words
                int L = rnd.next(1, max(1, (int)F_set.size()));
                for (int j = 0; j < L; j++) sen.push_back(rnd.any(F_set));
            } else if (i == 2) {
                // mix English and French
                int maxL = min((int)E_set.size() + (int)F_set.size(), 8);
                int L = rnd.next(2, max(2, maxL));
                for (int j = 0; j < L; j++) {
                    if (rnd.next(0, 1) == 0) sen.push_back(rnd.any(E_set));
                    else sen.push_back(rnd.any(F_set));
                }
            } else if (i == 3) {
                // only new words
                int L = rnd.next(1, 5);
                for (int j = 0; j < L; j++) sen.push_back(newWord());
            } else {
                // weighted random pick among E, F, new
                int L = rnd.next(1, 8);
                int tot = wE + wF + wN;
                for (int j = 0; j < L; j++) {
                    int p = rnd.next(1, tot);
                    if (p <= wE && !E_set.empty()) {
                        sen.push_back(rnd.any(E_set));
                    } else if (p <= wE + wF && !F_set.empty()) {
                        sen.push_back(rnd.any(F_set));
                    } else {
                        sen.push_back(newWord());
                    }
                }
            }
            println(sen);
        }
    }
    return 0;
}
