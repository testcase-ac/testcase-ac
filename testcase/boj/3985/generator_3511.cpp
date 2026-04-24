#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Cake length L and number of audience N
    int L = rnd.next(1, 20);
    int N = rnd.next(1, 10);

    // Hyper-parameters for interval sizes
    double smallProb = rnd.next(0.0, 1.0);   // probability of small requests
    double wholeProb = rnd.next(0.0, 0.3);   // probability of requesting the whole cake

    vector<pair<int,int>> req;
    req.reserve(N);
    for (int i = 0; i < N; i++) {
        double r = rnd.next();
        int P, K;
        if (r < wholeProb) {
            // Request the whole cake
            P = 1;
            K = L;
        } else if (r < wholeProb + smallProb) {
            // Small interval of length up to 3
            int maxLen = min(3, L);
            int len = rnd.next(1, maxLen);
            P = rnd.next(1, L - len + 1);
            K = P + len - 1;
        } else {
            // Random interval
            P = rnd.next(1, L);
            K = rnd.next(P, L);
        }
        req.emplace_back(P, K);
    }

    // Output the generated test case
    println(L);
    println(N);
    for (auto &pr : req)
        println(pr.first, pr.second);

    return 0;
}
