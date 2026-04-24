#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small number of cows
    int N = rnd.next(2, 10);

    // Build all possible pairs (A < B)
    vector<pair<int,int>> pairs;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            pairs.emplace_back(i, j);
        }
    }
    int total = (int)pairs.size();

    // Ensure at least one constraint of each type
    shuffle(pairs.begin(), pairs.end());
    int ML = rnd.next(1, total);
    shuffle(pairs.begin(), pairs.end());
    int MD = rnd.next(1, total);

    // Select constraints
    vector<pair<int,int>> ml_pairs(pairs.begin(), pairs.begin() + ML);
    shuffle(pairs.begin(), pairs.end());
    vector<pair<int,int>> md_pairs(pairs.begin(), pairs.begin() + MD);

    // Distance options hyper-parameter
    vector<int> D_opts = {10, 100, 1000, 1000000};
    int ml_max_d = rnd.any(D_opts);
    int md_max_d = rnd.any(D_opts);

    // Output header
    println(N, ML, MD);

    // Output ML "like" constraints: distance <= D
    for (auto &pr : ml_pairs) {
        int bias = rnd.next(-2, 2);
        int d = rnd.wnext(ml_max_d, bias) + 1;
        println(pr.first, pr.second, d);
    }
    // Output MD "dislike" constraints: distance >= D
    for (auto &pr : md_pairs) {
        int bias = rnd.next(-2, 2);
        int d = rnd.wnext(md_max_d, bias) + 1;
        println(pr.first, pr.second, d);
    }

    return 0;
}
