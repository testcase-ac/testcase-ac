#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: bias small or large or uniform
    int bias = rnd.next(-1, 1);
    int N = rnd.wnext(12, bias) + 1; // N in [1..12]
    // Total possible seats in rows 1 and 3
    int totalSeats = 2 * N;
    int M = rnd.next(1, totalSeats);

    // Build all possible seats (row, col)
    vector<pair<int,int>> seats;
    seats.reserve(totalSeats);
    for (int y = 1; y <= N; y++) {
        seats.emplace_back(1, y);
        seats.emplace_back(3, y);
    }
    // Randomly pick M distinct seats
    shuffle(seats.begin(), seats.end());
    seats.resize(M);

    // Hyper-parameter for probability a person disables AC
    double zeroProb = rnd.next(0.0, 1.0);

    // Prepare operations (x, y, t)
    vector<tuple<int,int,int>> ops;
    ops.reserve(M);
    for (auto &s : seats) {
        int x = s.first, y = s.second;
        int t = (rnd.next() < zeroProb ? 0 : 1);
        ops.emplace_back(x, y, t);
    }
    shuffle(ops.begin(), ops.end());

    // Output
    println(N, M);
    for (auto &tp : ops) {
        int x, y, t;
        tie(x, y, t) = tp;
        println(x, y, t);
    }
    return 0;
}
