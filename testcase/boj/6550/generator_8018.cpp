#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

string randStr(int len, const string &alpha) {
    string s;
    for (int i = 0; i < len; i++)
        s.push_back(rnd.any(alpha));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    int T = rnd.next(5, 10);
    for (int tc = 0; tc < T; tc++) {
        int tp = rnd.next(0, 7);
        string s, t;
        switch (tp) {
            case 0: {
                // trivial 1-char equal
                char c = rnd.any(alpha);
                s = string(1, c);
                t = s;
                break;
            }
            case 1: {
                // 1-char present in t
                char c = rnd.any(alpha);
                int Lt = rnd.next(2, 20);
                t = randStr(Lt, alpha);
                int pos = rnd.next(0, Lt - 1);
                t[pos] = c;
                s = string(1, c);
                break;
            }
            case 2: {
                // 1-char not present in t
                char c = rnd.any(alpha);
                int Lt = rnd.next(2, 20);
                string alpha2;
                for (char x : alpha) if (x != c) alpha2.push_back(x);
                t = randStr(Lt, alpha2);
                s = string(1, c);
                break;
            }
            case 3: {
                // s == t, length >=2
                int L = rnd.next(2, 20);
                s = randStr(L, alpha);
                t = s;
                break;
            }
            case 4: {
                // s longer than t
                int Lt = rnd.next(1, 15);
                int extra = rnd.next(1, 5);
                t = randStr(Lt, alpha);
                s = randStr(Lt + extra, alpha);
                break;
            }
            case 5: {
                // subsequence true, non-trivial
                int Lt = rnd.next(2, 20);
                t = randStr(Lt, alpha);
                int K = rnd.next(2, min(16, Lt));
                vector<int> idx(Lt);
                iota(idx.begin(), idx.end(), 0);
                shuffle(idx.begin(), idx.end());
                idx.resize(K);
                sort(idx.begin(), idx.end());
                s.clear();
                for (int i : idx) s.push_back(t[i]);
                break;
            }
            case 6: {
                // subsequence false via reversed pair
                int Lt = rnd.next(2, 20);
                t = randStr(Lt, alpha);
                int p = rnd.next(0, Lt - 2);
                int q = rnd.next(p + 1, Lt - 1);
                s = "";
                s.push_back(t[q]);
                s.push_back(t[p]);
                break;
            }
            case 7: {
                // fully random
                int Lt = rnd.next(1, 20);
                int Ls = rnd.next(1, 20);
                t = randStr(Lt, alpha);
                s = randStr(Ls, alpha);
                break;
            }
        }
        println(s, t);
    }
    return 0;
}
