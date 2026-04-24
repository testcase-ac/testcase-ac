#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases, ensure at least some special cases
    int T = rnd.next(6, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        // seats
        int N = rnd.next(2, 10);
        int C = 2;
        // number of tickets
        int M;
        if (i == 0) {
            // trivial single ticket
            M = 1;
        } else if (i == 1) {
            // maximal tickets for diversity
            M = min(N * 2, 20);
        } else {
            M = rnd.next(1, min(N * 2, 20));
        }
        // biases for position and buyer
        int posBias, buyerBias;
        if (i == 2) posBias = 2;
        else if (i == 3) posBias = -2;
        else posBias = rnd.next(-2, 2);
        if (i == 4) buyerBias = 2;
        else if (i == 5) buyerBias = -2;
        else buyerBias = rnd.next(-2, 2);

        vector<pair<int,int>> tickets;
        tickets.reserve(M);
        for (int j = 0; j < M; j++) {
            // P in [1..N] with bias: positive bias favors back seats (higher numbers)
            int P = rnd.wnext(N, posBias) + 1;
            // B in {1,2} with bias
            int B = rnd.wnext(C, buyerBias) + 1;
            tickets.emplace_back(P, B);
        }
        // shuffle ticket order
        shuffle(tickets.begin(), tickets.end());

        // output this test case
        println(N, C, M);
        for (auto &t : tickets) {
            println(t.first, t.second);
        }
    }
    return 0;
}
