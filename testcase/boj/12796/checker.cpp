#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

// Reads an answer from 'stream', validates it, computes the difference
// between the worst-case and best-case multiplication costs, and returns it.
// On invalid output, quits with _wa if stream == ouf, or _fail if stream == ans.
long long readAns(InStream &stream) {
    // Read number of matrices N
    int N = stream.readInt(1, 100, "N");
    // Read dimensions a[0..N]
    vector<long long> a(N + 1);
    for (int i = 0; i <= N; i++) {
        a[i] = stream.readInt(1, (int)1e9, ("a_" + to_string(i)).c_str());
    }
    // We'll do DP over the chain 1..N
    // dpmin[i][j] = minimal cost to multiply M_i..M_j
    // dpmax[i][j] = maximal cost to multiply M_i..M_j
    const __int128 INF = (__int128(1) << 120);
    vector<vector<__int128>> dpmin(N + 2, vector<__int128>(N + 2, INF));
    vector<vector<__int128>> dpmax(N + 2, vector<__int128>(N + 2, -INF));
    for (int i = 1; i <= N; i++) {
        dpmin[i][i] = 0;
        dpmax[i][i] = 0;
    }
    // length = number of matrices in subchain
    for (int len = 2; len <= N; len++) {
        for (int i = 1; i + len - 1 <= N; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                // cost to multiply (i..k) and (k+1..j), then combine
                __int128 mulCost = __int128(a[i-1]) * a[k] * a[j];
                __int128 cmn = dpmin[i][k] + dpmin[k+1][j] + mulCost;
                if (cmn < dpmin[i][j]) dpmin[i][j] = cmn;
                __int128 cmx = dpmax[i][k] + dpmax[k+1][j] + mulCost;
                if (cmx > dpmax[i][j]) dpmax[i][j] = cmx;
            }
        }
    }
    __int128 diff = dpmax[1][N] - dpmin[1][N];
    if (diff < 0)
        stream.quitf(_wa, "computed max < min");
    // Ensure it fits in 64-bit
    long long d = (long long)diff;
    if (__int128(d) != diff)
        stream.quitf(_fail, "difference does not fit in 64-bit");
    // No extra tokens
    stream.readEof();
    return d;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // Read K from input
    long long K = inf.readLong();
    // Read jury's answer and contestant's answer
    long long jans = readAns(ans);
    long long pans = readAns(ouf);
    // Compare
    if (jans != pans) {
        quitf(_wa, "difference is wrong: expected %lld, found %lld", jans, pans);
    }
    quitf(_ok, "difference = %lld", pans);
}
