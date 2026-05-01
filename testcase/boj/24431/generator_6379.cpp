#include "testlib.h"
#include <vector>
#include <set>
#include <string>
using namespace std;

string randStr(int len) {
    string s;
    for (int i = 0; i < len; i++)
        s += char('A' + rnd.next(0, 25));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 7);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int n = rnd.next(2, 12);
        int L = rnd.next(1, 10);
        int F = rnd.next(1, L);

        int mode;
        if (F == L) {
            mode = 0;
        } else {
            mode = rnd.next(0, 2);
        }

        set<string> used;
        vector<string> words;

        if (mode == 1) {
            // partial pairing: guarantee some pairs
            int num_pairs = rnd.next(1, n / 2);
            for (int p = 0; p < num_pairs; p++) {
                string suf;
                string w1, w2;
                // generate a unique suffix and two unique words
                do {
                    suf = randStr(F);
                    // build two candidates
                    string pre1 = randStr(L - F);
                    string pre2 = randStr(L - F);
                    w1 = pre1 + suf;
                    w2 = pre2 + suf;
                } while (w1 == w2 || used.count(w1) || used.count(w2));
                used.insert(w1);
                used.insert(w2);
                words.push_back(w1);
                words.push_back(w2);
            }
            // fill the rest
            while ((int)words.size() < n) {
                string w = randStr(L);
                if (!used.count(w)) {
                    used.insert(w);
                    words.push_back(w);
                }
            }
        } else if (mode == 2) {
            // maximal pairing
            int num_pairs = n / 2;
            for (int p = 0; p < num_pairs; p++) {
                string suf;
                string w1, w2;
                do {
                    suf = randStr(F);
                    string pre1 = randStr(L - F);
                    string pre2 = randStr(L - F);
                    w1 = pre1 + suf;
                    w2 = pre2 + suf;
                } while (w1 == w2 || used.count(w1) || used.count(w2));
                used.insert(w1);
                used.insert(w2);
                words.push_back(w1);
                words.push_back(w2);
            }
            if (n % 2 == 1) {
                while ((int)words.size() < n) {
                    string w = randStr(L);
                    if (!used.count(w)) {
                        used.insert(w);
                        words.push_back(w);
                    }
                }
            }
        } else {
            // mode 0: fully random
            while ((int)words.size() < n) {
                string w = randStr(L);
                if (!used.count(w)) {
                    used.insert(w);
                    words.push_back(w);
                }
            }
        }

        // shuffle the words to avoid ordering bias
        shuffle(words.begin(), words.end());

        // output the test case
        println(n, L, F);
        println(words);
    }

    return 0;
}
