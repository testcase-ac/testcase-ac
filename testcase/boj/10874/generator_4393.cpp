#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of students
    int N = rnd.next(1, 10);
    // Hyper-parameter to bias number of cheaters
    int tC = rnd.next(-1, 1);
    int C = rnd.wnext(N + 1, tC);
    if (C > N) C = N;

    // Choose which students are cheaters
    vector<int> idx(N);
    iota(idx.begin(), idx.end(), 1);
    shuffle(idx.begin(), idx.end());
    vector<bool> isCheater(N + 1, false);
    for (int i = 0; i < C; i++) {
        isCheater[idx[i]] = true;
    }

    // The correct answer pattern
    vector<int> pattern(10);
    for (int j = 0; j < 10; j++) {
        pattern[j] = (j % 5) + 1;
    }

    // Output
    println(N);
    for (int i = 1; i <= N; i++) {
        if (isCheater[i]) {
            // Perfect pattern for cheaters
            println(pattern);
        } else {
            // Generate a near-pattern but with at least one mismatch
            int tNC = rnd.next(-2, 2);
            int K = rnd.wnext(10, tNC);
            if (K > 9) K = 9;
            vector<int> pos(10);
            iota(pos.begin(), pos.end(), 0);
            shuffle(pos.begin(), pos.end());
            vector<bool> useMatch(10, false);
            for (int j = 0; j < K; j++) {
                useMatch[pos[j]] = true;
            }
            vector<int> ans(10);
            for (int j = 0; j < 10; j++) {
                if (useMatch[j]) {
                    ans[j] = pattern[j];
                } else {
                    int v;
                    do {
                        v = rnd.next(1, 5);
                    } while (v == pattern[j]);
                    ans[j] = v;
                }
            }
            println(ans);
        }
    }

    return 0;
}
