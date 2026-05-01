#include "testlib.h"
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

bool canMerge(const string &a, const string &b) {
    int v = 0;
    for (char c : a) {
        v = v * 10 + (c - '0');
        if (v > 641) return false;
    }
    for (char c : b) {
        v = v * 10 + (c - '0');
        if (v > 641) return false;
    }
    return v <= 641;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    vector<int> maxChoices = {5, 10, 20, 30};
    while (true) {
        int maxL = rnd.any(maxChoices);
        int K = rnd.next(1, min(8, maxL));
        vector<string> pieces;
        int sumlen = 0;
        bool good = true;
        for (int i = 0; i < K; i++) {
            bool placed = false;
            for (int t = 0; t < 1000; t++) {
                int x = rnd.next(1, 641);
                string s = to_string(x);
                if (sumlen + (int)s.size() > maxL) continue;
                if (i > 0 && canMerge(pieces.back(), s)) continue;
                pieces.push_back(s);
                sumlen += s.size();
                placed = true;
                break;
            }
            if (!placed) {
                good = false;
                break;
            }
        }
        if (!good || pieces.empty()) continue;
        // built successfully
        string S;
        S.reserve(sumlen);
        for (auto &s : pieces) S += s;
        printf("%d\n%s\n", sumlen, S.c_str());
        return 0;
    }
    return 0;
}
