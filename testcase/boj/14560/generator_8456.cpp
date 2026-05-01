#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 8);
    int N = 1;
    vector<long long> A;
    long long D = 0;

    auto computeSum = [&](const vector<long long>& v) {
        long long s = 0;
        for (long long x : v) s += x;
        return s;
    };

    switch (type) {
        case 0: { // tiny random
            N = rnd.next(1, 5);
            long long maxA = rnd.next(3, 20);
            A.resize(N);
            for (int i = 0; i < N; ++i)
                A[i] = rnd.next(1LL, maxA);
            long long sum = computeSum(A);
            long long hiD = sum * 2 + 10;
            if (hiD > (long long)1e18) hiD = (long long)1e18;
            D = rnd.next(0LL, hiD);
            break;
        }
        case 1: { // all equal
            N = rnd.next(1, 18);
            vector<long long> cand = {1, 2, 3, 5, 10};
            long long val = rnd.any(cand);
            A.assign(N, val);
            long long sum = computeSum(A);
            int pat = rnd.next(0, 2);
            if (pat == 0) {
                D = 0;
            } else if (pat == 1) {
                D = sum;
            } else {
                long long hiD = sum * 2 + 5;
                if (hiD > (long long)1e18) hiD = (long long)1e18;
                D = rnd.next(0LL, hiD);
            }
            break;
        }
        case 2: { // increasing sequence
            N = rnd.next(3, 18);
            long long first = rnd.next(1LL, 5LL);
            long long diff = rnd.next(1LL, 5LL);
            A.resize(N);
            for (int i = 0; i < N; ++i)
                A[i] = first + diff * i;
            long long sum = computeSum(A);
            int pat = rnd.next(0, 1);
            if (pat == 0) {
                long long hiD = sum;
                if (hiD > 10) hiD = 10;
                D = rnd.next(0LL, hiD);
            } else {
                long long hiD = sum * 2;
                if (hiD > (long long)1e18) hiD = (long long)1e18;
                D = rnd.next(0LL, hiD);
            }
            break;
        }
        case 3: { // huge values near 1e16
            N = rnd.next(2, 10);
            A.resize(N);
            for (int i = 0; i < N; ++i) {
                long long v;
                if (rnd.next(0, 1) == 0) {
                    int k = rnd.next(45, 53); // 2^45..2^53 <= 1e16
                    v = (1LL << k);
                } else {
                    v = rnd.next((long long)1e15, (long long)1e16);
                }
                A[i] = v;
            }
            long long sum = computeSum(A);
            int pat = rnd.next(0, 2);
            if (pat == 0) {
                D = 0;
            } else if (pat == 1) {
                long long hiD = sum;
                if (hiD > (long long)1e18) hiD = (long long)1e18;
                D = rnd.next(0LL, hiD);
            } else {
                long long loD = sum;
                if (loD > (long long)1e18) loD = (long long)1e18;
                long long hiD = sum * 2;
                if (hiD > (long long)1e18) hiD = (long long)1e18;
                if (loD > hiD) loD = hiD;
                D = rnd.next(loD, hiD);
            }
            break;
        }
        case 4: { // D >= total sum -> all assignments valid
            N = rnd.next(1, 18);
            A.resize(N);
            for (int i = 0; i < N; ++i)
                A[i] = rnd.next(1LL, 100LL);
            long long sum = computeSum(A);
            long long baseD = sum + rnd.next(0LL, sum + 5);
            if (baseD > (long long)1e18) baseD = (long long)1e18;
            D = baseD;
            break;
        }
        case 5: { // D = 0
            N = rnd.next(1, 18);
            A.resize(N);
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 2) <= 1)
                    A[i] = rnd.next(1LL, 20LL);
                else
                    A[i] = rnd.next(1LL, (long long)1e9);
            }
            D = 0;
            break;
        }
        case 6: { // N maxish, mixed sizes
            N = 18;
            A.resize(N);
            for (int i = 0; i < N; ++i) {
                if (i < 9)
                    A[i] = rnd.next(1LL, 10LL);
                else
                    A[i] = rnd.next(10LL, 1000LL);
            }
            long long sum = computeSum(A);
            int pat = rnd.next(0, 3);
            if (pat == 0) {
                D = 0;
            } else if (pat == 1) {
                long long hiD = sum;
                if (hiD > 20) hiD = 20;
                D = rnd.next(0LL, hiD);
            } else if (pat == 2) {
                long long loD = sum / 2;
                long long hiD = sum;
                if (hiD > (long long)1e18) hiD = (long long)1e18;
                D = rnd.next(loD, hiD);
            } else {
                long long loD = sum;
                long long hiD = sum * 2;
                if (hiD > (long long)1e18) hiD = (long long)1e18;
                if (loD > hiD) loD = hiD;
                D = rnd.next(loD, hiD);
            }
            break;
        }
        case 7: { // one huge, others small
            N = rnd.next(2, 18);
            A.resize(N);
            int bigIdx = rnd.next(0, N - 1);
            for (int i = 0; i < N; ++i) {
                if (i == bigIdx)
                    A[i] = rnd.next((long long)5e15, (long long)1e16);
                else
                    A[i] = rnd.next(1LL, 20LL);
            }
            long long sum = computeSum(A);
            if (rnd.next(0, 1) == 0) {
                long long hiD = 20;
                D = rnd.next(0LL, hiD);
            } else {
                long long hiD = sum;
                if (hiD > (long long)1e18) hiD = (long long)1e18;
                D = rnd.next(0LL, hiD);
            }
            break;
        }
        case 8: { // D tied to a random assignment's difference
            N = rnd.next(4, 12);
            A.resize(N);
            for (int i = 0; i < N; ++i)
                A[i] = rnd.next(1LL, 50LL);
            long long sumA = 0, sumR = 0;
            for (int i = 0; i < N; ++i) {
                int who = rnd.next(0, 2); // 0=L,1=A,2=R
                if (who == 1) sumA += A[i];
                else if (who == 2) sumR += A[i];
            }
            long long diff = sumA - sumR;
            long long absd = diff >= 0 ? diff : -diff;
            if (rnd.next(0, 1) == 0) {
                D = absd; // that assignment just valid
            } else {
                if (absd == 0) {
                    D = 0;
                } else {
                    D = rnd.next(0LL, absd - 1); // that assignment invalid
                }
            }
            break;
        }
    }

    println(N);
    println(A);
    println(D);

    return 0;
}
