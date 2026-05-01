#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 8);
    int N;
    string ans;

    switch (scenario) {
        // 0: small random, fully random answers
        case 0: {
            N = rnd.next(2, 8);
            ans.resize(N);
            string choices = "L H?"; // can't have spaces; use manual
            for (int i = 0; i < N; ++i) {
                int t = rnd.next(0, 2);
                ans[i] = (t == 0 ? 'L' : (t == 1 ? 'H' : '?'));
            }
            break;
        }

        // 1: all '?'
        case 1: {
            N = rnd.next(2, 50);
            ans.assign(N, '?');
            break;
        }

        // 2: all 'L' with odd N (guaranteed unsatisfiable)
        case 2: {
            do {
                N = rnd.next(2, 50);
            } while (N % 2 == 0);
            ans.assign(N, 'L');
            break;
        }

        // 3: all 'H' (always satisfiable, minimum liars = 0)
        case 3: {
            N = rnd.next(2, 50);
            ans.assign(N, 'H');
            break;
        }

        // 4: alternating pattern LHLH..., mixed satisfiable/unsatisfiable
        case 4: {
            N = rnd.next(2, 15);
            ans.resize(N);
            for (int i = 0; i < N; ++i) {
                ans[i] = (i % 2 == 0 ? 'L' : 'H');
            }
            break;
        }

        // 5: consistent via hidden types, small N with '?'
        case 5: {
            N = rnd.next(2, 15);
            vector<int> type(N); // 0 = honest, 1 = liar
            for (int i = 0; i < N; ++i)
                type[i] = rnd.next(0, 1);

            ans.resize(N);
            double pRefuse = 0.3 + 0.4 * rnd.next(); // between 0.3 and 0.7
            for (int i = 0; i < N; ++i) {
                if (rnd.next() < pRefuse) {
                    ans[i] = '?';
                } else {
                    int j = (i + 1) % N;
                    if (type[i] == 0) { // honest
                        ans[i] = (type[j] == 1 ? 'L' : 'H');
                    } else { // liar
                        ans[i] = (type[j] == 1 ? 'H' : 'L');
                    }
                }
            }
            break;
        }

        // 6: consistent via hidden types, larger N with fewer '?'
        case 6: {
            N = rnd.next(16, 50);
            vector<int> type(N); // 0 = honest, 1 = liar
            for (int i = 0; i < N; ++i)
                type[i] = rnd.next(0, 1);

            ans.resize(N);
            double pRefuse = 0.1 + 0.2 * rnd.next(); // between 0.1 and 0.3
            for (int i = 0; i < N; ++i) {
                if (rnd.next() < pRefuse) {
                    ans[i] = '?';
                } else {
                    int j = (i + 1) % N;
                    if (type[i] == 0) { // honest
                        ans[i] = (type[j] == 1 ? 'L' : 'H');
                    } else { // liar
                        ans[i] = (type[j] == 1 ? 'H' : 'L');
                    }
                }
            }
            break;
        }

        // 7: N = 2, hand-picked small tricky patterns
        case 7: {
            N = 2;
            vector<string> patterns = {
                "LL", "LH", "HL", "HH",
                "L?", "?L", "H?", "?H",
                "??"
            };
            ans = rnd.any(patterns);
            break;
        }

        // 8: fully constrained (no '?'), parity-controlled L-count for sat/unsat
        case 8: {
            N = rnd.next(3, 15);
            bool wantSatisfiable = rnd.next(0, 1); // 0: unsat, 1: sat
            int cntL;
            ans.resize(N);
            do {
                cntL = 0;
                for (int i = 0; i < N; ++i) {
                    char c = (rnd.next(0, 1) == 0 ? 'L' : 'H');
                    ans[i] = c;
                    if (c == 'L') cntL++;
                }
            } while (((cntL % 2 == 0) ? 1 : 0) != (wantSatisfiable ? 1 : 0));
            break;
        }
    }

    println(N);
    println(ans);

    return 0;
}
