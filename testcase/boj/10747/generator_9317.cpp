#include "testlib.h"
using namespace std;

string censorSim(string S, const string& T) {
    if (T.empty()) return S;
    size_t pos;
    while ((pos = S.find(T)) != string::npos) {
        S.erase(pos, T.size());
    }
    return S;
}

string randomString(int len, const string& alpha) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s += alpha[rnd.next(0, (int)alpha.size() - 1)];
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string S, T;

    for (int attempt = 0; ; ++attempt) {
        int type = rnd.next(0, 6);
        if (attempt > 50) type = 4; // safe fallback: T never occurs

        switch (type) {
            case 0: {
                // Small random with guaranteed occurrence
                int n = rnd.next(1, 10);
                int m = rnd.next(1, n);
                S = randomString(n, "abc");
                T = randomString(m, "abc");
                int pos = rnd.next(0, n - m);
                for (int i = 0; i < m; ++i) {
                    S[pos + i] = T[i];
                }
                break;
            }
            case 1: {
                // T of length 1, many deletions, but S not all that char
                int n = rnd.next(2, 40);
                char c1 = (char)rnd.next('a', 'z');
                char c2;
                do {
                    c2 = (char)rnd.next('a', 'z');
                } while (c2 == c1);

                S.assign(n, c1);
                int idxDiff = rnd.next(0, n - 1);
                S[idxDiff] = c2;
                // Optionally sprinkle more c2
                for (int i = 0; i < n; ++i) {
                    if (rnd.next(0, 4) == 0) S[i] = c2;
                }
                T = string(1, c1);
                break;
            }
            case 2: {
                // Many overlapping occurrences like "aaa..."; T = "aaa.."
                int n = rnd.next(3, 60);
                int k = rnd.next(2, 5);
                T = string(k, 'a');
                S.clear();
                while ((int)S.size() < n) {
                    bool aBlock = (rnd.next(0, 4) != 0); // mostly 'a' blocks
                    int len = aBlock ? rnd.next(1, 6) : rnd.next(1, 3);
                    char ch = aBlock ? 'a' : 'b';
                    for (int i = 0; i < len && (int)S.size() < n; ++i)
                        S.push_back(ch);
                }
                break;
            }
            case 3: {
                // T at prefix/suffix/both edges
                int n = rnd.next(3, 50);
                int m = rnd.next(1, min(10, n));
                T = randomString(m, "abcdefghijklmnopqrstuvwxyz");

                int patternType = rnd.next(0, 2);
                if (patternType == 0) {
                    // prefix only
                    int tailLen = n - m;
                    string tail = randomString(tailLen, "abcdef");
                    S = T + tail;
                } else if (patternType == 1) {
                    // suffix only
                    int headLen = n - m;
                    string head = randomString(headLen, "abcdef");
                    S = head + T;
                } else {
                    // both, if possible; else fallback to prefix
                    if (2 * m <= n) {
                        int midLen = n - 2 * m;
                        string mid = randomString(midLen, "abcdef");
                        S = T + mid + T;
                    } else {
                        int tailLen = n - m;
                        string tail = randomString(tailLen, "abcdef");
                        S = T + tail;
                    }
                }
                break;
            }
            case 4: {
                // T never occurs (uses a character not in S)
                int n = rnd.next(1, 60);
                int m = rnd.next(1, min(10, n));
                S = randomString(n, "abc");
                T = string(m, 'd'); // 'd' not in S
                break;
            }
            case 5: {
                // Overlapping creation after deletion: T = "aba" inside many "ab"a patterns
                string base;
                int rep = rnd.next(2, 5); // number of "ab" repeats
                for (int i = 0; i < rep; ++i) {
                    base += "ab";
                }
                base += 'a'; // makes sequences like "ababa", "abababa", ...
                int preLen = rnd.next(0, 3);
                int postLen = rnd.next(0, 3);
                S = string(preLen, 'c') + base + string(postLen, 'c');
                T = "aba";
                break;
            }
            case 6: {
                // Medium-sized random with several embedded T
                int n = rnd.next(30, 120);
                int m = rnd.next(2, min(10, n));
                T = randomString(m, "abcdef");
                S = randomString(n, "abcdef");
                int kOcc = rnd.next(1, 3);
                for (int it = 0; it < kOcc; ++it) {
                    int pos = rnd.next(0, n - m);
                    for (int i = 0; i < m; ++i)
                        S[pos + i] = T[i];
                }
                break;
            }
        }

        if (T.empty() || T.size() > S.size()) continue;

        string res = censorSim(S, T);
        if (!res.empty()) break;
    }

    println(S);
    println(T);

    return 0;
}
