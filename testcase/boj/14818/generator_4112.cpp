#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        // Hyper-parameters for sizes
        int N = rnd.next(2, 10);                     // number of seats
        int C = rnd.next(2, max(2, N) * 2);          // number of customers
        int mult = rnd.next(1, 3);
        int maxM = min(20, N * mult);
        int M = rnd.next(1, maxM);                   // number of tickets

        // Skew parameters to get diverse distributions
        int posSkew = rnd.next(-1, 1);
        int buyerSkew = rnd.next(-1, 1);

        vector<pair<int,int>> tickets;
        tickets.reserve(M);
        for (int i = 0; i < M; ++i) {
            int p, b;
            if (posSkew == 0) {
                p = rnd.next(1, N);
            } else {
                // rnd.wnext(N, t) gives [0..N-1]
                p = rnd.wnext(N, posSkew) + 1;
            }
            if (buyerSkew == 0) {
                b = rnd.next(1, C);
            } else {
                b = rnd.wnext(C, buyerSkew) + 1;
            }
            tickets.emplace_back(p, b);
        }

        // Shuffle so that tickets are in random order
        shuffle(tickets.begin(), tickets.end());

        // Output this test case
        println(N, C, M);
        for (auto &t : tickets) {
            println(t.first, t.second);
        }
    }

    return 0;
}
