#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int K = rnd.next(1, 5);
    println(K);
    for (int tc = 0; tc < K; ++tc) {
        double branch = rnd.next();
        int M, P;
        if (branch < 0.5) {
            M = rnd.next(1, 10);
            P = rnd.next(1, M);
        } else {
            M = rnd.next(1, 9);
            P = rnd.next(M + 1, min(10, M + 5));
        }
        double hotProb = rnd.next();
        int H = rnd.next(1, min(M, 3));

        vector<int> allSeats(M);
        iota(allSeats.begin(), allSeats.end(), 1);
        shuffle(allSeats.begin(), allSeats.end());
        vector<int> hotSeats(allSeats.begin(), allSeats.begin() + H);

        vector<int> req;
        for (int i = 0; i < P; ++i) {
            int seat;
            if (rnd.next() < hotProb) {
                seat = rnd.any(hotSeats);
            } else {
                seat = rnd.next(1, M);
            }
            req.push_back(seat);
        }

        println(P, M);
        for (int x : req) println(x);
    }

    return 0;
}
