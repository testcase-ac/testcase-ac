#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 200;
    const vector<char> alphabet = {'A', 'P', 'p'};

    auto addRandomNoPattern = [&](string &s, int len) {
        for (int it = 0; it < len; ++it) {
            char c;
            while (true) {
                c = rnd.any(alphabet);
                int L = (int)s.size();
                if (L >= 3 && s[L - 3] == 'p' && s[L - 2] == 'P' && s[L - 1] == 'A' && c == 'p') {
                    continue; // would create "pPAp"
                }
                break;
            }
            s.push_back(c);
        }
    };

    string s;
    int scenario = rnd.next(1, 7);

    switch (scenario) {
        case 1: { // tiny random
            int n = rnd.next(1, 7);
            s.reserve(n);
            for (int i = 0; i < n; ++i)
                s.push_back(rnd.any(alphabet));
            break;
        }
        case 2: { // mid-size, guaranteed no "pPAp"
            int n = rnd.next(5, 40);
            addRandomNoPattern(s, n);
            break;
        }
        case 3: { // several "pPAp" patterns with noise
            int prefix = rnd.next(0, 5);
            addRandomNoPattern(s, prefix);

            while (true) {
                if ((int)s.size() + 4 > MAX_N) break;
                s += "pPAp"; // insert a pattern

                int maxGap = min(3, MAX_N - (int)s.size());
                if (maxGap > 0) {
                    int gap = rnd.next(0, maxGap);
                    addRandomNoPattern(s, gap); // noise that does not create new pattern internally
                }

                if ((int)s.size() + 4 > MAX_N) break;
                if (rnd.next(0, 1) == 0) break; // stop sometimes
            }

            // optional trailing noise
            if (rnd.next(0, 1) && (int)s.size() < MAX_N) {
                int tail = rnd.next(0, MAX_N - (int)s.size());
                addRandomNoPattern(s, tail);
            }
            break;
        }
        case 4: { // has "pPAp" as subsequence but no substring "pPAp"
            vector<string> bases = {
                "pPAAp",
                "pPAPAp",
                "ApPAApA"
            };
            string base = rnd.any(bases);

            int preLen = rnd.next(0, 3);
            int sufLen = rnd.next(0, 3);

            // prefix & suffix only from 'A' and 'P' to avoid introducing 'pPAp'
            string two = "AP";
            for (int i = 0; i < preLen; ++i)
                s.push_back(rnd.any(two));
            s += base;
            for (int i = 0; i < sufLen; ++i)
                s.push_back(rnd.any(two));
            break;
        }
        case 5: { // all same character
            int n = rnd.next(1, MAX_N);
            char c = rnd.any(alphabet);
            s.assign(n, c);
            break;
        }
        case 6: { // target length, mix of patterns and safe random chars
            int n = rnd.next(10, MAX_N);
            s.reserve(n);
            for (int i = 0; i < n; ++i) {
                if (i + 4 <= n && rnd.next(0, 4) == 0) { // sometimes start a pattern
                    s += "pPAp";
                    i += 3; // loop will add +1 -> total advance 4
                } else {
                    char c;
                    while (true) {
                        c = rnd.any(alphabet);
                        int L = (int)s.size();
                        if (L >= 3 && s[L - 3] == 'p' && s[L - 2] == 'P' && s[L - 1] == 'A' && c == 'p') {
                            continue;
                        }
                        break;
                    }
                    s.push_back(c);
                }
            }
            break;
        }
        case 7:
        default: { // completely random
            int n = rnd.next(1, MAX_N);
            s.reserve(n);
            for (int i = 0; i < n; ++i)
                s.push_back(rnd.any(alphabet));
            break;
        }
    }

    int n = (int)s.size();
    println(n);
    println(s);

    return 0;
}
