#include "testlib.h"
#include <vector>
#include <cassert>
using namespace std;

int N, M;
vector<vector<long long>> gain;

// Structure to hold an answer: claimed profit and allocation per company.
struct Answer {
    long long profit;
    vector<int> alloc;
};

// Reads an answer from the given stream (ans or ouf), checks its validity,
// and returns the parsed Answer. If the answer is invalid, quits with _wa
// for ouf and _fail for ans.
Answer readAns(InStream &stream) {
    Answer A;
    // Read claimed profit.
    A.profit = stream.readLong(-1ll<<60, (1ll<<60), "profit");
    // Read allocations for each of the M companies.
    A.alloc.resize(M);
    long long sum = 0;
    for (int j = 0; j < M; j++) {
        A.alloc[j] = stream.readInt(0, N, format("allocation[%d]", j+1).c_str());
        sum += A.alloc[j];
    }
    // Check that the sum of allocations is exactly N.
    if (sum != N) {
        stream.quitf(_wa, "sum of allocations is %lld but should be %d", sum, N);
    }
    // Compute the actual profit from the gain table.
    long long actual = 0;
    for (int j = 0; j < M; j++) {
        actual += gain[A.alloc[j]][j];
    }
    // Verify that the claimed profit matches the computed profit.
    if (actual != A.profit) {
        stream.quitf(_wa, "claimed profit = %lld but actual profit = %lld", A.profit, actual);
    }
    return A;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input data.
    N = inf.readInt();
    M = inf.readInt();
    gain.assign(N+1, vector<long long>(M));
    for (int i = 1; i <= N; i++) {
        int x = inf.readInt(1, N, format("investment_amount_line_%d", i).c_str());
        // We don't require x == i, we just skip x.
        for (int j = 0; j < M; j++) {
            gain[i][j] = inf.readLong(0, (1ll<<31), format("gain[%d][%d]", i, j+1).c_str());
        }
    }
    // Read and validate jury and participant answers.
    Answer jans = readAns(ans);
    Answer pans = readAns(ouf);
    // Compare profits.
    if (pans.profit < jans.profit) {
        quitf(_wa, "suboptimal profit: expected %lld, found %lld", jans.profit, pans.profit);
    }
    if (pans.profit > jans.profit) {
        quitf(_fail, "participant's profit %lld exceeds jury's %lld", pans.profit, jans.profit);
    }
    // Equal profits -> OK.
    quitf(_ok, "profit = %lld", pans.profit);
    return 0;
}
