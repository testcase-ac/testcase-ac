#include "testlib.h"
using namespace std;

string revStr(const string &s) {
    string t = s;
    reverse(t.begin(), t.end());
    return t;
}

string randomString(int len, int alpha) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        char c = char('A' + rnd.next(0, alpha - 1));
        s.push_back(c);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide number of test cases with some bias
    int roll = rnd.next(0, 99);
    int T;
    if (roll < 50) T = 1;
    else if (roll < 80) T = 2;
    else T = 3;

    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Choose N with some variety: small, medium, larger (but still hand-checkable)
        int modeN = rnd.next(0, 2);
        int N;
        if (modeN == 0) N = rnd.next(2, 4);
        else if (modeN == 1) N = rnd.next(4, 7);
        else N = rnd.next(7, 9);

        while (true) {
            int Lmax = rnd.next(3, 10); // max length of strings for this test

            // Generate target sorted strings F (final forms after chosen reverses)
            vector<string> F;
            F.reserve(N);
            set<string> usedF;

            while ((int)F.size() < N) {
                int len = rnd.next(2, Lmax);

                // Alphabet size: sometimes full, sometimes small to create overlaps/prefixes
                int alphaMode = rnd.next(0, 2);
                int alpha;
                if (alphaMode == 0) alpha = 26;
                else alpha = rnd.next(2, 6); // small alphabet A..(A+alpha-1)

                string s = randomString(len, alpha);
                if (usedF.count(s)) continue;
                usedF.insert(s);
                F.push_back(s);
            }

            sort(F.begin(), F.end()); // ensure final forms are lexicographically sorted

            // Choose a pattern type for bits
            int patternType = rnd.next(0, 3); // 0,1,2,3

            vector<int> b(N, 0);
            if (patternType == 0) {
                // All zeros (no reverses)
                for (int i = 0; i < N; ++i) b[i] = 0;
            } else if (patternType == 1) {
                // Random bits
                for (int i = 0; i < N; ++i) b[i] = rnd.next(0, 1);
            } else if (patternType == 2) {
                // Alternating bits starting from 0 or 1
                int start = rnd.next(0, 1);
                for (int i = 0; i < N; ++i) b[i] = (start ^ (i & 1));
            } else {
                // Prefix pattern: zeros then ones or ones then zeros
                int k = rnd.next(0, N); // split point
                int variant = rnd.next(0, 1);
                if (variant == 0) {
                    // 0..0 1..1
                    for (int i = 0; i < N; ++i) b[i] = (i >= k);
                } else {
                    // 1..1 0..0
                    for (int i = 0; i < N; ++i) b[i] = (i < k);
                }
            }

            // Build original strings S from F and bits b
            vector<string> S(N);
            set<string> usedOrig;
            bool ok = true;

            for (int i = 0; i < N; ++i) {
                string s = (b[i] == 0 ? F[i] : revStr(F[i]));
                string rs = revStr(s);
                // Enforce: S[i] != S[j] and S[i] != Reverse(S[j]) for all j < i
                if (usedOrig.count(s) || usedOrig.count(rs)) {
                    ok = false;
                    break;
                }
                usedOrig.insert(s);
                S[i] = s;
            }

            if (!ok) continue; // regenerate this test case

            // Successfully generated a valid test case
            println(N);
            for (int i = 0; i < N; ++i) {
                println(S[i]);
            }
            break;
        }
    }

    return 0;
}
