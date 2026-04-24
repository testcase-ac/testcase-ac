#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: vary N and M sizes (small or medium)
    int N = (rnd.next(0,1) == 0 ? rnd.next(1, 5) : rnd.next(6, 15));
    int M = (rnd.next(0,1) == 0 ? rnd.next(1, 5) : rnd.next(6, 15));

    // Decide intersection size k (0, full, or partial)
    int mx = min(N, M);
    int k;
    if (mx == 0) {
        k = 0;
    } else {
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            k = 0;
        } else if (mode == 1) {
            k = mx;
        } else {
            k = (mx > 1 ? rnd.next(1, mx - 1) : 0);
        }
    }

    // Alphabet size hyper-parameter
    int a_size = (rnd.next(0,1) == 0 ? rnd.next(2, 5) : rnd.next(6, 26));
    char max_char = char('a' + a_size - 1);

    // Name length hyper-parameter (short vs longer)
    bool shortNames = rnd.next(0,1) == 0;
    int len_lo = shortNames ? 1 : 3;
    int len_hi = shortNames ? 5 : 10;

    // Helper to generate a random name
    auto genName = [&]() {
        int len = rnd.next(len_lo, len_hi);
        string s;
        s.reserve(len);
        for (int i = 0; i < len; i++) {
            s.push_back(char(rnd.next('a', max_char)));
        }
        return s;
    };

    // Build the sets ensuring uniqueness
    set<string> heard, unseen;
    // Common names
    for (int i = 0; i < k; i++) {
        string s;
        do { s = genName(); } while (heard.count(s));
        heard.insert(s);
        unseen.insert(s);
    }
    // Heard-only names
    for (int i = 0; i < N - k; i++) {
        string s;
        do { s = genName(); } while (heard.count(s) || unseen.count(s));
        heard.insert(s);
    }
    // Unseen-only names
    for (int i = 0; i < M - k; i++) {
        string s;
        do { s = genName(); } while (heard.count(s) || unseen.count(s));
        unseen.insert(s);
    }

    // Shuffle to randomize order
    vector<string> heardVec(heard.begin(), heard.end());
    vector<string> unseenVec(unseen.begin(), unseen.end());
    shuffle(heardVec.begin(), heardVec.end());
    shuffle(unseenVec.begin(), unseenVec.end());

    // Output
    println(N, M);
    for (auto &s : heardVec) println(s);
    for (auto &s : unseenVec) println(s);

    return 0;
}
