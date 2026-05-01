#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    string letters = "abcdefghijklmnopqrstuvwxyz";
    // Choose N with bias: mostly small, sometimes medium or large
    double p = rnd.next();
    int N;
    if (p < 0.6) {
        N = rnd.next(2, 30);
    } else if (p < 0.85) {
        N = rnd.next(31, 2000);
    } else {
        N = rnd.next(2001, 100000);
    }
    // Choose pattern type
    int t = rnd.next(0, 3);
    vector<string> pairs;
    if (t == 0) {
        // Random distinct pairs
        int maxK = min(676, 100);
        int K = rnd.next(1, maxK);
        vector<string> all;
        all.reserve(676);
        for (char a: letters)
            for (char b: letters)
                all.emplace_back(string()+a+b);
        shuffle(all.begin(), all.end());
        pairs.assign(all.begin(), all.begin() + K);
    }
    else if (t == 1) {
        // Chain + extra random pairs
        int L = rnd.next(2, min(N, 26));
        vector<char> v(letters.begin(), letters.end());
        shuffle(v.begin(), v.end());
        v.resize(L);
        set<string> used;
        for (int i = 0; i + 1 < L; i++) {
            string s; s += v[i]; s += v[i+1];
            pairs.push_back(s);
            used.insert(s);
        }
        int base = (int)pairs.size();
        int maxExtra = min(20, 676 - base);
        int extra = rnd.next(0, maxExtra);
        vector<string> all;
        all.reserve(676);
        for (char a: letters)
            for (char b: letters) {
                string s; s += a; s += b;
                if (!used.count(s)) all.push_back(s);
            }
        shuffle(all.begin(), all.end());
        for (int i = 0; i < extra && i < (int)all.size(); i++) {
            pairs.push_back(all[i]);
        }
    }
    else if (t == 2) {
        // Clique on a small subset (including self-pairs)
        int S = rnd.next(2, min(10, 26));
        vector<char> v(letters.begin(), letters.end());
        shuffle(v.begin(), v.end());
        v.resize(S);
        for (char a: v)
            for (char b: v) {
                string s; s += a; s += b;
                pairs.push_back(s);
            }
    }
    else {
        // Star pattern around a center letter
        char c = rnd.any(letters);
        vector<char> others;
        for (char x: letters) if (x != c) others.push_back(x);
        shuffle(others.begin(), others.end());
        int D = rnd.next(1, (int)others.size());
        others.resize(D);
        for (char x: others) {
            string s1; s1 += c; s1 += x;
            string s2; s2 += x; s2 += c;
            pairs.push_back(s1);
            pairs.push_back(s2);
        }
        if (rnd.next() < 0.5) {
            string s; s += c; s += c;
            pairs.push_back(s);
        }
    }
    // Output
    int K = (int)pairs.size();
    println(K, N);
    shuffle(pairs.begin(), pairs.end());
    for (auto &s: pairs) println(s);
    return 0;
}
