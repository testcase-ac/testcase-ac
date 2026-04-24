#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = rnd.next(2, 10);
    bool wantSolvable = rnd.next(0, 1);
    string s(N, '?');
    s[0] = 'B';

    if (wantSolvable) {
        int maxSteps = min(5, N - 1);
        int L = rnd.next(1, maxSteps);
        vector<int> path(L + 1);
        path[0] = 1;
        path[L] = N;
        if (L > 1) {
            vector<int> cand;
            for (int i = 2; i < N; ++i) cand.push_back(i);
            shuffle(cand.begin(), cand.end());
            for (int i = 1; i < L; ++i) path[i] = cand[i - 1];
        }
        sort(path.begin(), path.end());
        for (int i = 1; i <= L; ++i) {
            char prev = s[path[i-1]-1];
            char nextc = (prev == 'B' ? 'O' : (prev == 'O' ? 'J' : 'B'));
            s[path[i]-1] = nextc;
        }
        for (int i = 1; i < N; ++i) {
            if (s[i] == '?') {
                s[i] = rnd.any(string("BOJ"));
            }
        }
    } else {
        // fill randomly
        for (int i = 1; i < N; ++i) {
            s[i] = rnd.any(string("BOJ"));
        }
        // enforce unsolvable pattern
        if (rnd.next(0,1) == 0) {
            // remove all O's
            for (int i = 1; i < N; ++i) {
                if (s[i] == 'O') s[i] = rnd.any(string("BJ"));
            }
        } else {
            // break final step by equalizing last two
            if (N >= 2) s[N-1] = s[N-2];
        }
    }

    println(N);
    printf("%s\n", s.c_str());
    return 0;
}
