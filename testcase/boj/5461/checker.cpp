#include "testlib.h"
#include <vector>
#include <cstdint>
using namespace std;

int N;
long long W;
vector<int> S, Q;

// Structure to hold answer info: number of workers H,
// sum of Q's, numerator and denominator of the required k = max(S_i/Q_i).
struct Answer {
    int H;
    long long sumQ;
    long long num; // numerator of max ratio S_i/Q_i
    long long den; // denominator of that ratio
};

// Read an answer from stream (either jury ans or contestant ouf),
// validate it, and compute H, sumQ, num, den. On invalid:
//  - if stream == ouf: quitf(_wa,...)
//  - if stream == ans: quitf(_fail,...)
Answer readAns(InStream &stream) {
    Answer res;
    res.H = stream.readInt(0, N, "number of workers");
    vector<bool> used(N+1, false);
    res.sumQ = 0;
    res.num = 0;
    res.den = 1;
    for (int i = 0; i < res.H; i++) {
        int v = stream.readInt(1, N, format("worker[%d]", i+1).c_str());
        if (used[v])
            stream.quitf(_wa, "worker %d is chosen more than once", v);
        used[v] = true;
        // update sumQ
        res.sumQ += Q[v];
        // update max ratio num/den vs S[v]/Q[v]
        // compare: num/den < S[v]/Q[v] <=> num*Q[v] < S[v]*den
        if (res.num * (long long)Q[v] < (long long)S[v] * res.den) {
            res.num = S[v];
            res.den = Q[v];
        }
    }
    // Now check budget: cost = res.sumQ * (res.num/res.den) <= W
    // i.e. res.sumQ * res.num <= W * res.den
    __int128 lhs = (__int128)res.sumQ * res.num;
    __int128 rhs = (__int128)W * res.den;
    if (lhs > rhs) {
        stream.quitf(_wa, "total cost = sumQ*k = %lld*%lld/%lld = %.10f exceeds budget %lld",
                     res.sumQ, res.num, res.den,
                     double(res.sumQ) * double(res.num) / double(res.den),
                     W);
    }
    return res;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // read input
    N = inf.readInt();
    W = inf.readLong();
    S.resize(N+1);
    Q.resize(N+1);
    for (int i = 1; i <= N; i++) {
        S[i] = inf.readInt();
        Q[i] = inf.readInt();
    }

    // read jury and participant answers
    Answer jans = readAns(ans);
    Answer pans = readAns(ouf);

    // Compare number of workers
    if (pans.H != jans.H) {
        quitf(_wa, "wrong number of workers: expected %d, found %d",
              jans.H, pans.H);
    }
    // Compare cost: pans.sumQ * pans.num / pans.den <= jans.sumQ * jans.num / jans.den
    __int128 lhs = (__int128)pans.sumQ * pans.num * jans.den;
    __int128 rhs = (__int128)jans.sumQ * jans.num * pans.den;
    if (lhs > rhs) {
        // participant cost strictly greater than jury's
        long double pcost = (long double)pans.sumQ * pans.num / pans.den;
        long double jcost = (long double)jans.sumQ * jans.num / jans.den;
        quitf(_wa, "suboptimal cost: expected <= %.10Lf, found %.10Lf", jcost, pcost);
    }

    quitf(_ok, "%d workers hired, cost = %.10Lf",
          pans.H,
          (long double)pans.sumQ * pans.num / pans.den);

    return 0;
}
