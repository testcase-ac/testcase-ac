#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of chickens and cows
    int C = rnd.next(1, 20);
    int N = rnd.next(1, 20);

    // Maximum time value for T_i and B_j
    int maxTime = rnd.next(5, 100);

    // Hyper-parameters for weighted sampling
    vector<int> wParams = {-2, -1, 0, 1, 2};
    vector<int> lenWParams = {-1, 0, 1, 2};

    // Generate chicken times T_i
    vector<int> T(C);
    for (int i = 0; i < C; i++) {
        int w = rnd.any(wParams);
        // rnd.wnext(hi, w): in [0..hi-1], so hi = maxTime+1 gives [0..maxTime]
        T[i] = rnd.wnext(maxTime + 1, w);
    }
    shuffle(T.begin(), T.end());

    // Generate cow intervals [A_j, B_j]
    vector<pair<int,int>> intervals;
    for (int j = 0; j < N; j++) {
        // Some intervals cover full range to catch edge cases
        if (rnd.next() < 0.2) {
            intervals.emplace_back(0, maxTime);
        } else {
            int A = rnd.wnext(maxTime + 1, rnd.any(wParams));
            int rem = maxTime - A;
            int lw = rnd.any(lenWParams);
            int len = rnd.wnext(rem + 1, lw);
            int B = A + len;
            intervals.emplace_back(A, B);
        }
    }
    shuffle(intervals.begin(), intervals.end());

    // Output the test case
    println(C, N);
    for (int x : T) println(x);
    for (auto &p : intervals) println(p.first, p.second);

    return 0;
}
