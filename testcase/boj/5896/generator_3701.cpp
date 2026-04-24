#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small number of cows
    int N = rnd.next(1, 10);
    int K = rnd.next(1, N);

    vector<pair<int,int>> cows;
    double discountProb = rnd.next(0.0, 1.0);
    long long sumP = 0, sumC = 0;
    for (int i = 0; i < N; i++) {
        int P = rnd.next(1, 50);
        int C;
        if (P >= 2 && rnd.next() < discountProb) {
            // strong discount
            C = rnd.next(1, P / 2);
        } else {
            // weak or no discount
            int lo = max(1, P / 2 + 1);
            C = rnd.next(lo, P);
        }
        cows.emplace_back(P, C);
        sumP += P;
        sumC += C;
    }

    // Budget hyper-parameter: sometimes tight, sometimes loose
    int sumPint = (int)sumP;
    int sumCint = (int)sumC;
    long long M;
    if (rnd.next() < 0.5) {
        // tight budget up to sum of coupon prices
        M = rnd.next(1, sumCint);
    } else {
        // looser budget from sum of coupon prices up to full prices
        M = rnd.next(sumCint, sumPint);
    }

    // Output
    println(N, K, M);
    for (auto &pr : cows) {
        println(pr.first, pr.second);
    }
    return 0;
}
