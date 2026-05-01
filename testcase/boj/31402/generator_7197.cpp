#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for tree shape: 0=random tree, 1=chain, 2=star
    int treeType = rnd.next(0, 2);

    // Number of folders
    int N = rnd.next(2, 12);

    // Build parent relationships
    vector<vector<int>> children(N + 1);
    for (int i = 2; i <= N; i++) {
        int p;
        if (treeType == 0) {
            // random parent among [1..i-1]
            p = rnd.next(1, i - 1);
        } else if (treeType == 1) {
            // chain: each node i is child of i-1
            p = i - 1;
        } else {
            // star: all nodes except 1 attach to 1
            p = 1;
        }
        children[p].push_back(i);
    }

    // Shuffle children for extra variability
    for (int i = 1; i <= N; i++) {
        shuffle(children[i].begin(), children[i].end());
    }

    // Number of commands
    int Q = rnd.next(1, 5 * N);

    // Hyper-parameter for command distribution: more moves or more toggles
    int cmdMode = rnd.next(0, 2);
    double moveProb = (cmdMode == 0 ? 0.7 : (cmdMode == 1 ? 0.5 : 0.3));

    // Generate commands, ensure at least one move
    bool hasMove = false;
    vector<pair<bool,int>> commands;
    commands.reserve(Q);
    for (int i = 0; i < Q; i++) {
        bool isMove = rnd.next() < moveProb;
        if (i == Q - 1 && !hasMove) {
            // force at least one move
            isMove = true;
        }
        if (isMove) {
            hasMove = true;
            // move by k, where |k| <= N
            int k = rnd.next(-N, N);
            commands.emplace_back(true, k);
        } else {
            commands.emplace_back(false, 0);
        }
    }

    // Output
    // First line: N Q
    println(N, Q);
    // Next N lines: each folder's number of children and the list
    for (int i = 1; i <= N; i++) {
        println((int)children[i].size(), children[i]);
    }
    // Commands
    for (auto &cmd : commands) {
        if (cmd.first) {
            // move k
            printf("move %d\n", cmd.second);
        } else {
            // toggle
            println("toggle");
        }
    }

    return 0;
}
