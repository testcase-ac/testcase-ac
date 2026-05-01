#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of friends
    int maxN = 30;
    int N = rnd.next(1, maxN);
    vector<long long> P(N), S(N);
    // Generate diverse prices and shippings
    for (int i = 0; i < N; i++) {
        int pt = rnd.next(0, 2);
        if (pt == 0) {
            // small price, skewed to very small
            int t = -rnd.next(0, 2);
            P[i] = rnd.wnext(100LL, t);
        } else if (pt == 1) {
            // medium price
            P[i] = rnd.next(100LL, 1000LL);
        } else {
            // large price, skewed to very large
            int t = rnd.next(0, 2);
            P[i] = rnd.wnext(1000000000LL, t);
        }
        int st = rnd.next(0, 2);
        if (st == 0) {
            // small shipping
            S[i] = rnd.next(0LL, 10LL);
        } else if (st == 1) {
            // medium shipping
            S[i] = rnd.next(10LL, 1000LL);
        } else {
            // occasional large shipping
            int t = rnd.next(0, 1);
            S[i] = rnd.wnext(1000000000LL, t);
        }
    }
    // Compute sum of normal costs
    long long sum0 = 0;
    for (int i = 0; i < N; i++) sum0 += P[i] + S[i];
    // Cap budget to allowed maximum
    long long cap = sum0;
    if (cap < 1) cap = 1;
    if (cap > 1000000000LL) cap = 1000000000LL;
    // Budget skew hyper-parameter
    int tB = rnd.any(vector<int>{-1, 0, 1});
    long long B = rnd.wnext(cap, tB) + 1;
    // Output
    println(N, B);
    for (int i = 0; i < N; i++) {
        println(P[i], S[i]);
    }
    return 0;
}
