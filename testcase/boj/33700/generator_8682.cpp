#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 7);
    int N;

    if (scenario == 0) {
        N = 2;
    } else if (scenario == 1) {
        N = rnd.next(2, 16);
        if (N % 2 == 1) N++;
    } else {
        N = rnd.next(6, 40);
        if (N % 2 == 1) N++;
    }

    string S;

    switch (scenario) {
        case 0: {
            // Very small edge cases
            vector<string> cand = {"CC", "UU", "CU", "UC"};
            S = cand[rnd.next(0, (int)cand.size() - 1)];
            break;
        }
        case 1: {
            // Random small/medium
            S.resize(N);
            for (int i = 0; i < N; i++)
                S[i] = rnd.next(0, 1) ? 'C' : 'U';
            break;
        }
        case 2: {
            // All C
            S.assign(N, 'C');
            break;
        }
        case 3: {
            // All U
            S.assign(N, 'U');
            break;
        }
        case 4: {
            // Alternating pattern
            char start = rnd.any(string("CU"));
            char other = (start == 'C' ? 'U' : 'C');
            S.resize(N);
            for (int i = 0; i < N; i++)
                S[i] = (i % 2 == 0 ? start : other);
            break;
        }
        case 5: {
            // Half and half
            bool firstC = rnd.next(0, 1);
            S.resize(N);
            for (int i = 0; i < N; i++) {
                if (i < N / 2)
                    S[i] = firstC ? 'C' : 'U';
                else
                    S[i] = firstC ? 'U' : 'C';
            }
            break;
        }
        case 6: {
            // Biased random: more Cs or more Us
            int biasType = rnd.next(0, 1); // 0: more C, 1: more U
            S.resize(N);
            for (int i = 0; i < N; i++) {
                int r = rnd.next(0, 99);
                if (biasType == 0) {
                    // ~80% C
                    S[i] = (r < 80 ? 'C' : 'U');
                } else {
                    // ~80% U
                    S[i] = (r < 80 ? 'U' : 'C');
                }
            }
            break;
        }
        case 7: {
            // Mostly C with scattered U's
            S.assign(N, 'C');
            int changes = rnd.next(1, max(1, N / 3));
            for (int i = 0; i < changes; i++) {
                int pos = rnd.next(0, N - 1);
                S[pos] = 'U';
            }
            break;
        }
    }

    int maxQ;
    if (N <= 10) maxQ = 40;
    else if (N <= 20) maxQ = 60;
    else maxQ = 80;

    int Q = rnd.next(1, maxQ);
    vector<int> queries(Q);

    switch (scenario) {
        case 0: {
            // Random between 1 and 2
            for (int i = 0; i < Q; i++)
                queries[i] = rnd.next(1, 2);
            break;
        }
        case 1: {
            // Pure random indices
            for (int i = 0; i < Q; i++)
                queries[i] = rnd.next(1, N);
            break;
        }
        case 2: {
            // Many toggles at ends
            for (int i = 0; i < Q; i++) {
                int t = rnd.next(0, 3);
                if (t == 0) queries[i] = 1;
                else if (t == 1) queries[i] = N;
                else queries[i] = rnd.next(1, N);
            }
            break;
        }
        case 3: {
            // Many toggles near the middle
            int mid = (N + 1) / 2;
            for (int i = 0; i < Q; i++) {
                int t = rnd.next(0, 3);
                if (t <= 1) queries[i] = mid;
                else queries[i] = rnd.next(1, N);
            }
            break;
        }
        case 4: {
            // Walk along the string with wrap-around
            int cur = rnd.next(1, N);
            int dir = rnd.next(0, 1) ? 1 : -1;
            for (int i = 0; i < Q; i++) {
                queries[i] = cur;
                cur += dir;
                if (cur < 1) cur = N;
                if (cur > N) cur = 1;
            }
            break;
        }
        case 5: {
            // More queries on one half
            bool leftHeavy = rnd.next(0, 1);
            for (int i = 0; i < Q; i++) {
                int t = rnd.next(0, 3);
                if (t <= 2) {
                    if (leftHeavy)
                        queries[i] = rnd.next(1, N / 2);
                    else
                        queries[i] = rnd.next(N / 2 + 1, N);
                } else {
                    queries[i] = rnd.next(1, N);
                }
            }
            break;
        }
        case 6: {
            // One hot index toggled very often
            int hot = rnd.next(1, N);
            for (int i = 0; i < Q; i++) {
                int t = rnd.next(0, 3);
                if (t <= 2) queries[i] = hot;
                else queries[i] = rnd.next(1, N);
            }
            break;
        }
        case 7: {
            // Repeated pattern 1..N..1..N...
            for (int i = 0; i < Q; i++)
                queries[i] = (i % N) + 1;
            break;
        }
    }

    println(N, Q);
    println(S);
    for (int i = 0; i < Q; i++)
        println(queries[i]);

    return 0;
}
