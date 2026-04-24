#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    int N = inf.readInt();
    int M = inf.readInt();
    int K = inf.readInt();

    // Read jury's answer to know if a solution exists
    bool juryNoSol = false;
    int ans_first = ans.readInt();
    if (ans_first == -1) {
        juryNoSol = true;
    } else {
        // Jury provides a sequence: validate bounds and consume it
        if (ans_first < 1 || ans_first > N)
            ans.quitf(_fail, "jury's first element = %d is out of range [1, %d]", ans_first, N);
        for (int i = 1; i < N; i++) {
            ans.readInt(1, N, "jury sequence element");
        }
    }

    // Now check participant's output
    if (juryNoSol) {
        // Expect exactly "-1"
        int p = ouf.readInt();
        if (p != -1)
            quitf(_wa, "expected -1 (no solution), found %d", p);
        // No extra tokens
        ouf.skipBlanks();
        if (!ouf.seekEof())
            quitf(_pe, "extra output after -1");
        quitf(_ok, "correctly reported no solution");
    } else {
        // Jury has a solution: participant must output a valid permutation
        int first = ouf.readInt();
        if (first == -1)
            quitf(_wa, "participant output -1 but a solution exists");
        // Read the sequence
        vector<int> seq(N);
        seq[0] = first;
        if (first < 1 || first > N)
            quitf(_wa, "element %d is out of range [1, %d]", first, N);
        for (int i = 1; i < N; i++) {
            seq[i] = ouf.readInt(1, N, "element");
        }
        // No extra tokens
        ouf.skipBlanks();
        if (!ouf.seekEof())
            quitf(_pe, "extra output after sequence");

        // Check that it's a permutation
        vector<bool> seen(N+1, false);
        for (int x : seq) {
            if (seen[x])
                quitf(_wa, "number %d appears more than once", x);
            seen[x] = true;
        }
        for (int i = 1; i <= N; i++) {
            if (!seen[i])
                quitf(_wa, "number %d is missing", i);
        }

        // Compute LIS length
        vector<int> lis_dp;
        for (int x : seq) {
            auto it = lower_bound(lis_dp.begin(), lis_dp.end(), x);
            if (it == lis_dp.end())
                lis_dp.push_back(x);
            else
                *it = x;
        }
        int lis = lis_dp.size();

        // Compute LDS length by computing LIS on -x
        vector<int> lds_dp;
        for (int x : seq) {
            int nx = -x;
            auto it = lower_bound(lds_dp.begin(), lds_dp.end(), nx);
            if (it == lds_dp.end())
                lds_dp.push_back(nx);
            else
                *it = nx;
        }
        int lds = lds_dp.size();

        if (lis != M || lds != K)
            quitf(_wa, "sequence has LIS = %d, LDS = %d; expected LIS = %d, LDS = %d",
                  lis, lds, M, K);
        quitf(_ok, "correct sequence: LIS = %d, LDS = %d", lis, lds);
    }
    return 0;
}
