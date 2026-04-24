#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of words
    int N = rnd.next(2, 10);

    // Alphabet size hyper-parameter: at least 2 letters
    int maxK = min(26, N + 3);
    int K = rnd.next(2, maxK);

    // Pick K distinct letters from 'a'..'z'
    vector<char> pool(26);
    iota(pool.begin(), pool.end(), 'a');
    shuffle(pool.begin(), pool.end());
    vector<char> alph(pool.begin(), pool.begin() + K);

    // Hidden permutation defines the alien order
    vector<char> perm = alph;
    shuffle(perm.begin(), perm.end());

    // Rank map for hidden order
    vector<int> rk(256, -1);
    for (int i = 0; i < K; i++) {
        rk[(unsigned char)perm[i]] = i;
    }

    // Hyper-parameters for word lengths
    int maxLen = rnd.next(1, 7);
    int tLenParam = rnd.next(-2, 2);       // bias for longer or shorter words
    double prefixProb = rnd.next(0.0, 1.0);// chance to generate by prefix

    // Generate N distinct words
    set<string> used;
    vector<string> words;
    while ((int)words.size() < N) {
        string s;
        if (!words.empty() && rnd.next() < prefixProb) {
            // Build from an existing word: either a prefix or an extension
            string base = rnd.any(words);
            if (rnd.next(0, 1) == 0 && base.size() > 1) {
                // take a strict prefix
                int nl = rnd.next(1, (int)base.size() - 1);
                s = base.substr(0, nl);
            } else {
                // extend with one more random letter
                s = base + rnd.any(alph);
            }
        } else {
            // Fully random word
            int len = rnd.wnext(maxLen, tLenParam) + 1;
            s.reserve(len);
            for (int i = 0; i < len; i++) {
                s += rnd.any(alph);
            }
        }
        if (used.insert(s).second) {
            words.push_back(s);
        }
    }

    // Sort the words according to the hidden alien order
    auto cmp = [&](const string &a, const string &b) {
        int la = a.size(), lb = b.size();
        for (int i = 0; i < la && i < lb; i++) {
            if (a[i] != b[i])
                return rk[(unsigned char)a[i]] < rk[(unsigned char)b[i]];
        }
        return la < lb;
    };
    sort(words.begin(), words.end(), cmp);

    // Output
    println(N);
    for (auto &w : words) {
        println(w);
    }

    return 0;
}
