#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Scenario selection for diversity
    int scenario = rnd.next(0, 3);
    int N, O;
    if (scenario == 0) {
        N = rnd.next(3, 5);
        O = rnd.next(1, 5);
    } else if (scenario == 1) {
        N = rnd.next(5, 15);
        O = rnd.next(1, 20);
    } else if (scenario == 2) {
        N = rnd.next(10, 20);
        O = rnd.next(10, 50);
    } else {
        N = rnd.next(15, 25);
        O = rnd.next(20, 100);
    }
    // Generate command string
    string cmd;
    cmd.reserve(O);
    const string moves = "UDLRS";
    for (int i = 0; i < O; i++) {
        cmd.push_back(rnd.any(moves));
    }
    // Starting position
    int py = rnd.next(1, N);
    int px = rnd.next(1, N);
    // Prepare all other cells
    vector<pair<int,int>> cells;
    cells.reserve(N*N);
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= N; x++) {
            if (y == py && x == px) continue;
            cells.emplace_back(y, x);
        }
    }
    // Shuffle for random selection of walls and zombies
    shuffle(cells.begin(), cells.end());
    int maxCells = N * N - 1;
    int maxEntities = min(maxCells, 50);
    int W = 0, Z = 0;
    if (scenario == 0) {
        W = 0; Z = 0;
    } else if (scenario == 1) {
        W = rnd.next(1, maxEntities);
        Z = 0;
    } else if (scenario == 2) {
        W = rnd.next(0, maxEntities/2);
        Z = rnd.next(1, maxEntities - W);
    } else {
        int lbW = maxEntities/2;
        W = rnd.next(lbW, maxEntities);
        int maxZ = min(maxCells - W, maxEntities);
        int lbZ = maxEntities/2;
        if (lbZ > maxZ) lbZ = maxZ;
        Z = rnd.next(lbZ, maxZ);
    }
    // Select walls and zombies
    vector<pair<int,int>> walls(cells.begin(), cells.begin() + W);
    vector<pair<int,int>> zombies(cells.begin() + W, cells.begin() + W + Z);
    // Choose day D to query
    int D = rnd.next(1, O);
    // Output
    println(N);
    printf("%s\n", cmd.c_str());
    println(py, px);
    println(W);
    for (auto &w : walls) {
        println(w.first, w.second);
    }
    println(Z);
    for (auto &z : zombies) {
        int zy = z.first, zx = z.second;
        int type = rnd.next(0, 1);
        char dir = rnd.any(string("UDLR"));
        int speed;
        if (type == 0) {
            speed = rnd.next(0, N);
        } else {
            speed = rnd.next(0, 100000000);
        }
        println(zy, zx, type, dir, speed);
    }
    println(D);
    return 0;
}
