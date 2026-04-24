#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for grid size
    int A = rnd.next(1, 10);
    int B = rnd.next(1, 10);

    // Number of robots: at least 1, at most min(5, A*B)
    int maxRobots = min(A * B, 5);
    int N = rnd.next(1, maxRobots);

    // Number of commands: between 1 and 10
    int M = rnd.next(1, 10);

    // Generate all possible cells and pick N distinct ones
    vector<pair<int,int>> cells;
    for (int x = 1; x <= A; x++) {
        for (int y = 1; y <= B; y++) {
            cells.emplace_back(x, y);
        }
    }
    shuffle(cells.begin(), cells.end());
    vector<pair<int,int>> pos(cells.begin(), cells.begin() + N);

    // Assign initial directions randomly from N, W, E, S
    string dirs = "NWES";
    vector<char> dir(N);
    for (int i = 0; i < N; i++) {
        dir[i] = rnd.any(dirs);
    }

    // Generate M commands
    string acts = "LRF";
    vector<tuple<int,char,int>> cmds;
    for (int i = 0; i < M; i++) {
        int rid = rnd.next(1, N);
        char c = rnd.any(acts);
        int rep = rnd.next(1, 5);
        cmds.emplace_back(rid, c, rep);
    }

    // Output in the required format
    println(A, B);
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(pos[i].first, pos[i].second, dir[i]);
    }
    for (auto &t : cmds) {
        int rid, rep;
        char c;
        tie(rid, c, rep) = t;
        println(rid, c, rep);
    }

    return 0;
}
