#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for r and s
    int tR = rnd.next(-1, 1);
    int tS = rnd.next(-1, 1);
    int maxR = 10;
    int maxS = 5;
    int r = rnd.wnext(maxR, tR) + 1;  // rows: 1..maxR
    int s = rnd.wnext(maxS, tS) + 1;  // seats per side: 1..maxS

    // Maximum number of passengers
    int pmax = 2 * r * s;

    // Hyper-parameter for passenger count density
    int tP = rnd.next(-1, 1);
    int p = rnd.wnext(pmax, tP) + 1;  // at least 1 passenger

    // Generate all possible seat positions
    vector<pair<int,int>> seats;
    seats.reserve(pmax);
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= 2*s; j++) {
            seats.emplace_back(i, j);
        }
    }

    // Shuffle and pick p distinct seats
    shuffle(seats.begin(), seats.end());
    seats.resize(p);

    // Output
    println(r, s, p);
    for (auto &pr : seats) {
        println(pr.first, pr.second);
    }

    return 0;
}
