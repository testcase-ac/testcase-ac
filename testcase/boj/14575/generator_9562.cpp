#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 5); // 6 scenarios: 0..5

    int N;
    long long T;
    vector<int> L, R;

    if (scenario == 0) {
        // General random feasible case
        N = rnd.next(1, 10);
        L.resize(N);
        R.resize(N);
        long long sumL = 0, sumR = 0;
        for (int i = 0; i < N; ++i) {
            L[i] = rnd.next(1, 15);
            R[i] = rnd.next(L[i], 30);
            sumL += L[i];
            sumR += R[i];
        }
        T = rnd.next(sumL, sumR); // ensure global feasibility
    } else if (scenario == 1) {
        // Minimal S = max L_i
        N = rnd.next(2, 10);
        L.resize(N);
        R.resize(N);

        int Lmax = rnd.next(2, 20);
        int id = rnd.next(0, N - 1);
        for (int i = 0; i < N; ++i) {
            if (i == id) {
                L[i] = Lmax;
            } else {
                L[i] = rnd.next(1, Lmax - 1);
            }
            int extra = rnd.next(0, 10);
            R[i] = rnd.next(L[i], L[i] + extra);
        }

        long long sumL = 0;
        long long U_at_S = 0;
        for (int i = 0; i < N; ++i) {
            sumL += L[i];
            U_at_S += min(R[i], Lmax);
        }
        // U_at_S >= sumL always holds
        T = rnd.next(sumL, U_at_S); // globally feasible; minimal S will be Lmax
    } else if (scenario == 2) {
        // Minimal S determined by average (ceil(T / N))
        N = rnd.next(2, 8);
        L.assign(N, 1);
        int Rcommon = rnd.next(5, 30);
        int S_ans = rnd.next(2, Rcommon);
        R.assign(N, Rcommon);

        long long sumL = N;
        long long sumR = 1LL * N * Rcommon;
        long long low = 1LL * N * (S_ans - 1) + 1;
        long long high = 1LL * N * S_ans;
        // low >= sumL, high <= sumR
        T = rnd.next(low, high); // ensures minimal S = S_ans
    } else if (scenario == 3) {
        // N = 1 edge case (always globally feasible here)
        N = 1;
        L.resize(1);
        R.resize(1);
        L[0] = rnd.next(1, 20);
        R[0] = rnd.next(L[0], 40);
        T = rnd.next((long long)L[0], (long long)R[0]); // sumL <= T <= sumR
    } else if (scenario == 4) {
        // T = sum R_i -> minimal S = max R_i
        N = rnd.next(2, 10);
        L.resize(N);
        R.resize(N);
        long long sumR = 0;
        for (int i = 0; i < N; ++i) {
            L[i] = rnd.next(1, 20);
            R[i] = rnd.next(L[i], 40);
            sumR += R[i];
        }
        T = sumR; // sumL <= T <= sumR holds automatically
    } else { // scenario == 5
        // Many participants with small slack (R_i close to L_i)
        N = rnd.next(5, 12);
        L.resize(N);
        R.resize(N);
        long long sumL = 0, sumR = 0;
        for (int i = 0; i < N; ++i) {
            L[i] = rnd.next(1, 20);
            int delta = rnd.next(0, 3);
            R[i] = L[i] + delta;
            sumL += L[i];
            sumR += R[i];
        }
        // Choose T as either sumL, sumR, or somewhere in between
        int type = rnd.next(0, 2);
        if (type == 0) {
            T = sumL;
        } else if (type == 1) {
            T = sumR;
        } else {
            T = rnd.next(sumL, sumR);
        }
    }

    println(N, T);
    for (int i = 0; i < N; ++i) {
        println(L[i], R[i]);
    }

    return 0;
}
