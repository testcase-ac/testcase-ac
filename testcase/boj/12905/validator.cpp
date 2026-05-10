#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Simulate whether there exists an assignment of honest/liar types
// consistent with answers, and if so return minimum number of liars.
// Honest = 1, Liar = 0 in vectors.
int computeMinLiars(const string &s) {
    int n = (int)s.size();
    const int INF = 1000000000;
    int best = INF;

    // Try all 4 combinations for person 0 type and person n-1 type,
    // but due to circular consistency, only consistent ones will survive.
    // However, it's easier to treat this as assigning all persons.
    // N is <= 50, so we can brute force all 2^N assignments.
    // 2^50 is too large, so we must reason more cleverly.

    // Better approach: For each possible type of person 0 (0 = liar, 1 = honest),
    // deduce all others deterministically and then check circular consistency.
    for (int firstType = 0; firstType <= 1; ++firstType) {
        // we will create two possibilities for second person (type 0 or 1)
        for (int secondType = 0; secondType <= 1; ++secondType) {
            vector<int> type(n, -1);
            type[0] = firstType;
            type[1 % n] = secondType;

            bool ok = true;
            // propagate types from person 0 to n-2 using answers.
            for (int i = 0; i < n; ++i) {
                int next = (i + 1) % n;
                if (i == n - 1) break; // we'll check last consistency later
                char ans = s[i];
                // If type[i] or type[next] is unknown, may derive.
                if (ans == '?') {
                    // No constraint from this person.
                    // Only possible relation: they refuse, nothing implied.
                    // So do nothing.
                    continue;
                }
                // Let t[i] in {0,1}, t[next] in {0,1}
                // Honest says:
                //   'L' -> right neighbor is liar -> t[next] = 0
                //   'H' -> right neighbor is honest -> t[next] = 1
                // Liar says opposite:
                //   'L' -> right neighbor is honest -> t[next] = 1
                //   'H' -> right neighbor is liar -> t[next] = 0

                // So target type for next:
                int mustNext;
                if (ans == 'L') {
                    mustNext = (type[i] == 1 ? 0 : 1);
                } else if (ans == 'H') {
                    mustNext = (type[i] == 1 ? 1 : 0);
                } else {
                    ok = false;
                    break;
                }

                if (type[i] == -1) {
                    // If speaker type unknown, we cannot know mustNext because
                    // formula depends on type[i]. But we purposely fixed type[0] and [1],
                    // and then propagate sequentially, so here type[i] should never be -1
                    // for i < n-1 if propagation is consistent.
                    ok = false;
                    break;
                }

                if (type[next] == -1) {
                    type[next] = mustNext;
                } else if (type[next] != mustNext) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;

            // Now check all constraints including circular for i = n-1
            for (int i = 0; i < n && ok; ++i) {
                char ans = s[i];
                if (ans == '?') continue;
                int cur = type[i];
                int nxt = type[(i + 1) % n];
                // Ensure they are fully assigned
                if (cur == -1 || nxt == -1) {
                    ok = false;
                    break;
                }
                bool statement; // statement meaning: "right neighbor is liar" for 'L', "honest" for 'H'
                if (ans == 'L') {
                    statement = (nxt == 0);
                } else if (ans == 'H') {
                    statement = (nxt == 1);
                } else {
                    ok = false;
                    break;
                }
                // Honest: statement must be true. Liar: statement must be false.
                if (cur == 1 && !statement) ok = false;
                if (cur == 0 && statement) ok = false;
            }
            if (!ok) continue;

            int liars = 0;
            for (int i = 0; i < n; ++i)
                if (type[i] == 0) ++liars;
            best = min(best, liars);
        }
    }

    if (best == INF) return -1;
    return best;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 50, "N");
    inf.readEoln();

    string s = inf.readToken("[A-Z\\?]{1,50}", "answers");
    inf.readEoln();

    ensuref((int)s.size() == N, "Length of answers string (%d) must equal N (%d)", (int)s.size(), N);

    for (int i = 0; i < N; ++i) {
        ensuref(s[i] == 'L' || s[i] == 'H' || s[i] == '?',
                "answers[%d] must be one of 'L','H','?', got '%c'", i, s[i]);
    }

    // Problem guarantees: output is either minimum possible liars or -1.
    // That implies that the model must be well-defined; we check that
    // our computation always finishes and result is within [0,N] or -1.
    int res = computeMinLiars(s);
    ensuref(res == -1 || (0 <= res && res <= N),
            "Computed minimum liars %d is invalid", res);

    inf.readEof();
}
