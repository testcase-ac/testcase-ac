#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Board size hyper-parameter
    int N = rnd.next(1, 10);

    // Generate all positions
    vector<pair<int,int>> all;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            all.emplace_back(i, j);
        }
    }

    // Type of obstacle pattern
    int type = rnd.next(0, 2);
    vector<pair<int,int>> obs;

    if (type == 0) {
        // Pure random obstacles
        double dens = rnd.next(0.0, 1.0);
        int maxOb = (int)(dens * all.size());
        shuffle(all.begin(), all.end());
        for (int i = 0; i < maxOb; i++) {
            obs.push_back(all[i]);
        }
    } else if (type == 1) {
        // Main diagonal obstacles plus random extras
        for (int i = 1; i <= N; i++) {
            obs.emplace_back(i, i);
        }
        vector<pair<int,int>> rem;
        for (auto &p : all) {
            if (p.first != p.second) rem.push_back(p);
        }
        double dens = rnd.next(0.0, 1.0);
        int extra = rnd.next(0, (int)(dens * all.size()));
        shuffle(rem.begin(), rem.end());
        for (int i = 0; i < extra && i < (int)rem.size(); i++) {
            obs.push_back(rem[i]);
        }
    } else {
        // Anti-diagonal obstacles plus random extras
        for (int i = 1; i <= N; i++) {
            obs.emplace_back(i, N + 1 - i);
        }
        vector<pair<int,int>> rem;
        for (auto &p : all) {
            if (p.first + p.second != N + 1) rem.push_back(p);
        }
        double dens = rnd.next(0.0, 1.0);
        int extra = rnd.next(0, (int)(dens * all.size()));
        shuffle(rem.begin(), rem.end());
        for (int i = 0; i < extra && i < (int)rem.size(); i++) {
            obs.push_back(rem[i]);
        }
    }

    // Output the test case
    println(N);
    println((int)obs.size());
    for (auto &p : obs) {
        println(p.first, p.second);
    }

    return 0;
}
