#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Ensure at least 6 to include all predefined edge cases
    int M = rnd.next(6, 20);
    vector<pair<int,int>> q;
    // Small edge cases with very small N
    int Ns = rnd.next(1, 5);
    q.emplace_back(Ns, 0);
    q.emplace_back(Ns, Ns);
    // Small-to-medium N cases
    int N2 = rnd.next(1, 100);
    q.emplace_back(N2, 1);
    if (N2 > 1) q.emplace_back(N2, N2 - 1);
    else q.emplace_back(N2, 0);
    // Large N with random K
    int Nlarge1 = rnd.wnext(4000000, 10);
    q.emplace_back(Nlarge1, rnd.next(0, Nlarge1));
    // Large N with special K choices
    int Nlarge2 = rnd.next(2000000, 4000000);
    vector<int> choices = {0, 1, Nlarge2/2, Nlarge2 - 1, Nlarge2};
    int K2 = rnd.any(choices);
    if (K2 < 0) K2 = 0;
    if (K2 > Nlarge2) K2 = Nlarge2;
    q.emplace_back(Nlarge2, K2);
    // Fill up to M with random queries
    while ((int)q.size() < M) {
        int N = rnd.next(1, 4000000);
        int K = rnd.next(0, N);
        q.emplace_back(N, K);
    }
    shuffle(q.begin(), q.end());
    // Output
    println(M);
    for (auto &p : q) {
        println(p.first, p.second);
    }
    return 0;
}
