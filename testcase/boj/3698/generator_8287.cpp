#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> types = {0, 1, 2};
    shuffle(types.begin(), types.end());
    int T = 3;
    println(T);

    for (int t : types) {
        if (t == 0) {
            // Unique reconstruction case
            int W = rnd.next(2, 4);  // number of words
            vector<string> orig(W);
            for (int i = 0; i < W; i++) {
                int L = rnd.next(3, 6);
                string w;
                w += char('a' + rnd.next(0, 25));
                for (int j = 0; j < L - 2; j++)
                    w += char('a' + rnd.next(0, 25));
                w += char('a' + rnd.next(0, 25));
                orig[i] = w;
            }
            // Build the scrambled, space-free sentence
            string s;
            for (auto &w : orig) {
                if (w.size() > 2) {
                    string mid = w.substr(1, w.size() - 2);
                    shuffle(mid.begin(), mid.end());
                    s += w[0];
                    s += mid;
                    s += w.back();
                } else {
                    s += w;
                }
            }
            // Dictionary: include exactly the original words + unique distractors
            set<string> used(orig.begin(), orig.end());
            vector<string> dict = orig;
            int extras = rnd.next(1, 3);
            for (int i = 0; i < extras; i++) {
                string d;
                int Ld = rnd.next(1, 3);
                do {
                    d.clear();
                    for (int j = 0; j < Ld; j++)
                        d += char('a' + rnd.next(0, 25));
                } while (used.count(d));
                used.insert(d);
                dict.push_back(d);
            }
            // Output
            println(s);
            println((int)dict.size());
            for (auto &w : dict) println(w);
        }
        else if (t == 1) {
            // Ambiguous case: single scrambled word matching two different variants
            int L = rnd.next(4, 7);
            char f = char('a' + rnd.next(0, 25));
            char l = char('a' + rnd.next(0, 25));
            string midStr;
            for (int i = 0; i < L - 2; i++)
                midStr += char('a' + i);
            string midRev = midStr;
            reverse(midRev.begin(), midRev.end());
            string w1 = string(1, f) + midStr + l;
            string w2 = string(1, f) + midRev + l;
            string midSh = midStr;
            shuffle(midSh.begin(), midSh.end());
            string s2;
            s2 += f;
            s2 += midSh;
            s2 += l;
            println(s2);
            println(2);
            println(w1);
            println(w2);
        }
        else {
            // Impossible case: no match
            int L = rnd.next(5, 10);
            string s3(L, 'x');
            int n = 1;
            int La = rnd.next(1, 3);
            string w(La, 'a');
            println(s3);
            println(n);
            println(w);
        }
    }
    return 0;
}
