#include "testlib.h"
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes
    int N = rnd.next(2, 15);
    // Number of files at least 1, at most N-1
    int F = rnd.next(1, N - 1);
    int D = N - F; // directories count

    // Prepare node IDs 2..N
    vector<int> nodes(N - 1);
    iota(nodes.begin(), nodes.end(), 2);
    shuffle(nodes.begin(), nodes.end());

    // Assign directories
    vector<bool> isDir(N + 1, false);
    isDir[1] = true;
    for (int i = 0; i < D - 1; i++) {
        isDir[nodes[i]] = true;
    }

    // Hyper-parameter for depth bias: -2..2
    int wDepth = rnd.next(-2, 2);

    // Build the tree: parent pointers, children lists
    vector<vector<int>> children(N + 1);
    vector<int> availDirs = {1};
    for (int v : nodes) {
        // choose parent among available directories, biased by wDepth
        int pidx = rnd.wnext((int)availDirs.size(), wDepth);
        int p = availDirs[pidx];
        children[p].push_back(v);
        if (isDir[v]) availDirs.push_back(v);
    }

    // Hyper-parameter for name generation
    double alphaProb = rnd.next();

    auto genName = [&]() {
        int maxLen = rnd.next(1, 16);
        string s;
        for (int i = 0; i < maxLen; i++) {
            if (rnd.next() < alphaProb) {
                s += char('a' + rnd.next(0, 25));
            } else {
                s += char('0' + rnd.next(0, 9));
            }
        }
        return s;
    };

    // Generate names
    vector<string> names(N + 1);
    for (int i = 1; i <= N; i++) {
        names[i] = genName();
    }

    // Output
    println(N);
    for (int i = 1; i <= N; i++) {
        printf("%s ", names[i].c_str());
        if (!isDir[i]) {
            // file
            printf("0\n");
        } else {
            // directory
            int m = (int)children[i].size();
            printf("%d", m);
            for (int c : children[i]) {
                printf(" %d", c);
            }
            printf("\n");
        }
    }

    return 0;
}
