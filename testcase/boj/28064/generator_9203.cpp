#include "testlib.h"
using namespace std;

string randomString(int len, char lo = 'a', char hi = 'z') {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; i++) {
        s.push_back((char)rnd.next((int)lo, (int)hi));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> names;

    int type = rnd.next(0, 7);

    switch (type) {
        case 0: {
            // Very small, mostly handcrafted
            int sub = rnd.next(0, 2);
            if (sub == 0) {
                // From statement example 2 (answer = 2)
                names = {"leeminhee", "minheejin", "jinmichae"};
            } else if (sub == 1) {
                // From statement example 3 (answer = 3)
                names = {"mini", "minhee", "minimini", "minigimbob"};
            } else {
                // Simple no-overlap
                names = {"a", "b"};
            }
            break;
        }
        case 1: {
            // 1-letter names, guaranteed some duplicates
            int N = rnd.next(3, 12);
            for (int i = 0; i < N; i++) {
                char c = char('a' + rnd.next(0, 3)); // a..d
                names.push_back(string(1, c));
            }
            // Ensure at least one duplicate exists
            bool dup = false;
            for (int i = 0; i < N; i++)
                for (int j = 0; j < i; j++)
                    if (names[i] == names[j])
                        dup = true;
            if (!dup && N >= 2) {
                names[1] = names[0];
            }
            break;
        }
        case 2: {
            // Several base names, many duplicates
            int nUnique = rnd.next(1, 4);
            vector<string> base;
            for (int i = 0; i < nUnique; i++) {
                int len = rnd.next(2, 6); // always <= 20
                base.push_back(randomString(len, 'a', 'c'));
            }
            int N = rnd.next(max(3, nUnique + 1), 15);
            int dupIdx = rnd.next(0, nUnique - 1);

            // Ensure at least two copies of one base name
            names.push_back(base[dupIdx]);
            names.push_back(base[dupIdx]);
            while ((int)names.size() < N) {
                names.push_back(rnd.any(base));
            }
            break;
        }
        case 3: {
            // Guaranteed zero connections: all distinct 1-letter names
            int N = rnd.next(2, 10);
            for (int i = 0; i < N; i++) {
                char c = char('a' + i); // all distinct
                names.push_back(string(1, c));
            }
            break;
        }
        case 4: {
            // Star-shaped overlaps around a center name
            int L = rnd.next(4, 8);
            string center = randomString(L, 'a', 'c');
            names.push_back(center);

            int Nothers = rnd.next(3, 9); // total <= 11
            for (int i = 0; i < Nothers; i++) {
                bool usePrefix = (rnd.next(0, 1) == 0);
                int k = rnd.next(1, L - 1);
                int extraLen = rnd.next(1, 4);
                string extra = randomString(extraLen, 'a', 'c');
                string s;
                if (usePrefix) {
                    // center prefix matches suffix of s
                    s = center.substr(0, k) + extra;
                } else {
                    // center suffix matches prefix of s
                    s = extra + center.substr(L - k, k);
                }
                // s length <= (L-1)+4 <= 11 <= 20
                names.push_back(s);
            }

            // Optionally add one noise name that likely doesn't overlap
            if (rnd.next(0, 1) == 0 && (int)names.size() < 15) {
                int len = rnd.next(2, 4);
                string noise(len, 'x'); // unlikely to overlap center built from 'a'..'c'
                names.push_back(noise);
            }
            break;
        }
        case 5: {
            // Random moderate case, mixed overlaps
            int N = rnd.next(5, 15);
            for (int i = 0; i < N; i++) {
                int len = rnd.next(1, 10); // <= 10
                names.push_back(randomString(len, 'a', 'z'));
            }
            break;
        }
        case 6: {
            // Tricky handcrafted directional & multi-k overlaps
            names = {
                "abc",  // with "cde" only suffix/prefix (condition 2)
                "cde",  // with "dea" suffix/prefix, etc.
                "dea",  // with "abc" only prefix/suffix (condition 1)
                "aa",   // many k work with others
                "aaa",
                "baa",
                "aab"
            };
            break;
        }
        case 7: {
            // Long names near max length, full-length overlaps
            int baseLen = rnd.next(15, 19); // ensure baseLen + 1 <= 20
            string base = randomString(baseLen, 'a', 'd');
            names.push_back(base);                            // full base (<= 19)
            names.push_back(base.substr(0, baseLen - 1));     // prefix of base (<= 18)
            names.push_back(string(1, base[0]) + base);       // base as suffix (<= 20)
            names.push_back(base + string(1, base.back()));   // base as prefix (<= 20)

            int extra = rnd.next(0, 4);
            for (int i = 0; i < extra; i++) {
                int len = rnd.next(15, 20);                   // <= 20
                names.push_back(randomString(len, 'a', 'z'));
            }
            break;
        }
    }

    // Fallback safety (should not happen)
    if (names.empty()) {
        names.push_back("a");
    }

    // Shuffle order to avoid positional assumptions
    shuffle(names.begin(), names.end());

    int N = (int)names.size();
    println(N);
    for (const string &s : names) {
        println(s);
    }

    return 0;
}
