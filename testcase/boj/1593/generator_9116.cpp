#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    auto randomString = [&](int len, const string& alphabet) -> string {
        string s;
        s.reserve(len);
        for (int i = 0; i < len; i++)
            s += rnd.any(alphabet);
        return s;
    };

    int g;
    string W, S;

    int type = rnd.next(1, 8);

    // Small alphabets for variability
    vector<string> alphabets = {
        "abc",
        "ABC",
        "aAbB",
        "abcdefghijklmnopqrstuvwxyz",
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    };

    switch (type) {
        case 1: { // Completely random small case
            string alphabet = rnd.any(alphabets);
            int Slen = rnd.next(1, 40);
            g = rnd.next(1, Slen);
            W = randomString(g, alphabet);
            S = randomString(Slen, alphabet);
            break;
        }
        case 2: { // Many disjoint exact-permutation matches (non-overlapping)
            string alphabet = "abcdAB";
            g = rnd.next(2, 6);
            int k = rnd.next(2, 6); // number of permutation blocks
            W = randomString(g, alphabet);
            S.clear();
            for (int i = 0; i < k; i++) {
                string perm = W;
                shuffle(perm.begin(), perm.end());
                S += perm;
            }
            break;
        }
        case 3: { // All same character, all windows match (maximal overlaps)
            int extra = rnd.next(0, 10);
            g = rnd.next(2, 15);
            int Slen = g + extra;
            char c = rnd.any(string("abcABC"));
            W.assign(g, c);
            S.assign(Slen, c);
            break;
        }
        case 4: { // Guaranteed no matches, disjoint alphabets (case sensitivity)
            int Slen = rnd.next(1, 40);
            g = rnd.next(1, Slen);
            string lower = "abcdefghijklmnopqrstuvwxyz";
            string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            W = randomString(g, lower);
            S = randomString(Slen, upper);
            break;
        }
        case 5: { // g == |S| edge case, sometimes anagram sometimes not
            int len = rnd.next(1, 40);
            g = len;
            string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            W = randomString(g, alphabet);
            bool makeAnagram = rnd.next(0, 1);
            if (makeAnagram) {
                S = W;
                shuffle(S.begin(), S.end());
            } else {
                S = W;
                int pos = rnd.next(0, g - 1);
                char oldc = S[pos];
                char newc;
                do {
                    newc = rnd.any(alphabet);
                } while (newc == oldc);
                S[pos] = newc; // now S is not an anagram of W
            }
            break;
        }
        case 6: { // Medium-sized random with at least one guaranteed match
            int Slen = rnd.next(60, 120);
            g = rnd.next(10, min(40, Slen));
            string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            W = randomString(g, alphabet);
            S = randomString(Slen, alphabet);
            int pos = rnd.next(0, Slen - g);
            string perm = W;
            shuffle(perm.begin(), perm.end());
            for (int i = 0; i < g; i++)
                S[pos + i] = perm[i];
            break;
        }
        case 7: { // g = 1 special case
            int Slen = rnd.next(1, 50);
            g = 1;
            string alphabet = "abcABC";
            W = string(1, rnd.any(alphabet));
            S = randomString(Slen, alphabet);
            if (rnd.next(0, 1) == 1) {
                int pos = rnd.next(0, Slen - 1);
                S[pos] = W[0]; // ensure at least one occurrence
            }
            break;
        }
        case 8: { // Many repeated characters with some embedded matches
            g = rnd.next(3, 8);
            char ca = 'a';
            char cb = 'b';
            W.assign(g - 1, ca);
            W.push_back(cb);
            shuffle(W.begin(), W.end());

            int Slen = rnd.next(g, 40);
            string alphabet = "ab";
            S = randomString(Slen, alphabet);

            int maxStarts = max(1, Slen - g + 1);
            int embedCount = rnd.next(1, min(3, maxStarts));
            for (int t = 0; t < embedCount; t++) {
                int pos = rnd.next(0, Slen - g);
                string perm = W;
                shuffle(perm.begin(), perm.end());
                for (int i = 0; i < g; i++)
                    S[pos + i] = perm[i];
            }
            break;
        }
    }

    println(g, (int)S.size());
    println(W);
    println(S);

    return 0;
}
