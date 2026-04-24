#include "testlib.h"
#include <vector>
#include <set>
#include <array>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Three categories: unique solution, uncertain, impossible
    int category = rnd.next(0, 2);
    if (category == 0) {
        // Unique solution: at least 3 beacons around a chosen receiver
        int N = rnd.next(3, 7);
        int XR = rnd.next(-5, 5);
        int YR = rnd.next(-5, 5);
        set<pair<int,int>> used;
        vector<array<int,3>> beacons;
        while ((int)beacons.size() < N) {
            int dx = rnd.next(-5, 5);
            int dy = rnd.next(-5, 5);
            if (dx == 0 && dy == 0) continue;
            int xi = XR + dx;
            int yi = YR + dy;
            if (used.insert({xi, yi}).second) {
                int di = abs(dx) + abs(dy);
                beacons.push_back({xi, yi, di});
            }
        }
        shuffle(beacons.begin(), beacons.end());
        println(N);
        for (auto &b : beacons)
            println(b[0], b[1], b[2]);
    }
    else if (category == 1) {
        // Uncertain: single beacon with positive distance => infinite solutions
        int xi = rnd.next(-10, 10);
        int yi = rnd.next(-10, 10);
        int di = rnd.next(1, 10);
        println(1);
        println(xi, yi, di);
    }
    else {
        // Impossible: two beacons both claim distance zero but at different spots
        println(2);
        println(0, 0, 0);
        println(0, 1, 0);
    }
    return 0;
}
