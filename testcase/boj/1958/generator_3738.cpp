#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small lengths for hand-checkable inputs
    int L1 = rnd.next(1, 10);
    int L2 = rnd.next(1, 10);
    int L3 = rnd.next(1, 10);

    // Choose a small alphabet size for diversity
    int pAlpha = rnd.next(1, 7);
    vector<char> alpha;
    for (char c = 'a'; c <= 'z'; ++c) alpha.push_back(c);
    shuffle(alpha.begin(), alpha.end());
    alpha.resize(pAlpha);

    // Decide a common subsequence length with bias
    int Smax = min({L1, L2, L3, 5});
    vector<int> ts = {-1, 0, 1};
    int t = rnd.any(ts);                      // bias parameter: -1, 0, or 1
    int Slen = rnd.wnext(Smax + 1, t);        // length in [0..Smax] with bias

    // Generate the common subsequence S
    string S;
    for (int i = 0; i < Slen; ++i)
        S.push_back(rnd.any(alpha));

    // Function to embed S into a random string of length L
    auto genStr = [&](int L) {
        string s(L, 'a');
        vector<int> pos(L);
        iota(pos.begin(), pos.end(), 0);
        vector<int> pick;
        if (Slen > 0) {
            shuffle(pos.begin(), pos.end());
            pick.assign(pos.begin(), pos.begin() + Slen);
            sort(pick.begin(), pick.end());
        }
        int idxS = 0;
        for (int i = 0; i < L; ++i) {
            if (idxS < Slen && i == pick[idxS]) {
                s[i] = S[idxS++];
            } else {
                s[i] = rnd.any(alpha);
            }
        }
        return s;
    };

    string s1 = genStr(L1);
    string s2 = genStr(L2);
    string s3 = genStr(L3);

    // Output the three strings
    println(s1);
    println(s2);
    println(s3);

    return 0;
}
