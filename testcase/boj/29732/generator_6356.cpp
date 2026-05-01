#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of people
    int N = rnd.next(1, 30);
    // Infection spread range
    int K = rnd.next(0, N / 2);

    // Generate initial infection string
    string S(N, '.');
    int C = rnd.next(0, N); // number of initially infected
    vector<int> idx(N);
    iota(idx.begin(), idx.end(), 0);
    shuffle(idx.begin(), idx.end());
    vector<int> infected(idx.begin(), idx.begin() + C);
    sort(infected.begin(), infected.end());
    for (int x : infected) {
        S[x] = 'R';
    }

    // Compute infected count after one day
    vector<pair<int,int>> intervals;
    for (int x : infected) {
        int l = max(0, x - K);
        int r = min(N - 1, x + K);
        intervals.emplace_back(l, r);
    }
    sort(intervals.begin(), intervals.end());
    int F = 0;
    int cur_l = -1, cur_r = -1;
    for (auto &p : intervals) {
        int l = p.first, r = p.second;
        if (cur_l == -1) {
            cur_l = l; cur_r = r;
        } else if (l <= cur_r + 1) {
            cur_r = max(cur_r, r);
        } else {
            F += cur_r - cur_l + 1;
            cur_l = l;
            cur_r = r;
        }
    }
    if (cur_l != -1) {
        F += cur_r - cur_l + 1;
    }

    // Choose M to sometimes yield Yes, sometimes No
    int M;
    if (F <= 1) {
        // trivial or single infection -> always Yes
        M = rnd.next(1, N);
    } else {
        bool wantNo = rnd.next(0, 1) == 1;
        if (wantNo) {
            // not enough medicine
            M = rnd.next(1, F - 1);
        } else {
            // enough or just enough
            M = rnd.next(F, N);
        }
    }

    // Output
    println(N, M, K);
    println(S);

    return 0;
}
