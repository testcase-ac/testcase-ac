#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for sizes: weighted to favor small but allow up to 10
    int N = rnd.wnext(10, -1) + 1; // [1..10], skewed small
    int M = rnd.wnext(10, -1) + 1; // [1..10], skewed small

    // Hyper-parameters for distributions
    int pdist = rnd.next(0, 2);
    int qdist = rnd.next(0, 2);

    // Generate P points
    vector<pair<int,int>> P;
    P.reserve(N);
    for (int i = 0; i < N; i++) {
        int x, y;
        if (pdist == 0) {
            // small cluster
            x = rnd.next(-10, 10);
            y = rnd.next(-10, 10);
        } else if (pdist == 1) {
            // wide spread
            x = rnd.next(-1000000, 1000000);
            y = rnd.next(-1000000, 1000000);
        } else {
            // medium spread
            x = rnd.next(-100, 100);
            y = rnd.next(-100, 100);
        }
        P.emplace_back(x, y);
    }

    // Generate Q points
    vector<pair<int,int>> Q(M);
    if (qdist == 0) {
        // Some centers exactly at P, others near origin
        int eq = rnd.next(1, M);
        // first eq will be exact copies
        for (int i = 0; i < eq; i++) {
            auto pr = rnd.any(P);
            Q[i] = pr;
        }
        for (int i = eq; i < M; i++) {
            Q[i].first = rnd.next(-100, 100);
            Q[i].second = rnd.next(-100, 100);
        }
        shuffle(Q.begin(), Q.end());
    } else if (qdist == 1) {
        // All centers widely spread
        for (int i = 0; i < M; i++) {
            Q[i].first = rnd.next(-1000000, 1000000);
            Q[i].second = rnd.next(-1000000, 1000000);
        }
    } else {
        // Clustered around a random P
        auto center = rnd.any(P);
        for (int i = 0; i < M; i++) {
            Q[i].first = center.first + rnd.next(-100, 100);
            Q[i].second = center.second + rnd.next(-100, 100);
        }
    }

    // Output
    println(N, M);
    for (auto &pr : P) println(pr.first, pr.second);
    for (auto &qr : Q) println(qr.first, qr.second);

    return 0;
}
