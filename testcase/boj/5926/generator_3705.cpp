#include "testlib.h"
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cows
    int N = rnd.next(1, 10);
    // Number of distinct breeds to include
    int B = rnd.next(1, N);
    // Global cluster radius
    int radius = rnd.next(0, 20);

    // Sample B unique breed IDs in [1,1000]
    set<int> breedSet;
    while ((int)breedSet.size() < B) {
        breedSet.insert(rnd.next(1, 1000));
    }
    vector<int> breedIDs(breedSet.begin(), breedSet.end());

    // Assign a cluster center for each breed in [1,100]
    map<int,int> center;
    for (int b : breedIDs) {
        center[b] = rnd.next(1, 100);
    }

    // Build the list of cow breed assignments: at least one of each breed
    vector<int> cowBreeds;
    for (int b : breedIDs) {
        cowBreeds.push_back(b);
    }
    // Fill remaining cows with random breeds
    for (int i = B; i < N; i++) {
        cowBreeds.push_back(rnd.any(breedIDs));
    }
    // Shuffle breed order
    shuffle(cowBreeds.begin(), cowBreeds.end());

    // Generate positions around their breed's cluster center
    vector<pair<int,int>> cows;
    for (int b : cowBreeds) {
        int c = center[b];
        int lo = max(1, c - radius);
        int hi = c + radius;
        int x = rnd.next(lo, hi);
        cows.emplace_back(x, b);
    }
    // Shuffle final order
    shuffle(cows.begin(), cows.end());

    // Output
    println(N);
    for (auto &pr : cows) {
        println(pr.first, pr.second);
    }

    return 0;
}
