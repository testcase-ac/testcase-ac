#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters for small size and diversity
    int min_N = 2, max_N = 10;
    int min_K = 1, max_K = 10;
    int min_coord = 0, max_coord_range = 20;

    // Decide bias or uniform for directions
    int bias_type = rnd.next(0, 1);
    string dirs = "ABCD";
    char biased_dir = 'A';
    double bias_strength = 0.0;
    if (bias_type == 1) {
        biased_dir = rnd.any(dirs);
        bias_strength = rnd.next(50, 90) / 100.0; // between 0.50 and 0.90
    }

    int N = rnd.next(min_N, max_N);
    int K = rnd.next(min_K, max_K);
    int max_coord = rnd.next(5, max_coord_range);

    // Generate directions
    string jump_dirs;
    jump_dirs.reserve(K);
    for (int i = 0; i < K; i++) {
        if (bias_type == 1 && rnd.next() < bias_strength) {
            jump_dirs.push_back(biased_dir);
        } else {
            // uniform among all 4
            jump_dirs.push_back(dirs[rnd.next(0, 3)]);
        }
    }

    // Generate N distinct plant coordinates
    set<pair<int,int>> plant_set;
    while ((int)plant_set.size() < N) {
        int x = rnd.next(min_coord, max_coord);
        int y = rnd.next(min_coord, max_coord);
        plant_set.insert({x, y});
    }

    // Move to vector and shuffle order
    vector<pair<int,int>> plants(plant_set.begin(), plant_set.end());
    shuffle(plants.begin(), plants.end());

    // Ensure the first plant is the starting plant
    int start_idx = rnd.next(0, N-1);
    swap(plants[0], plants[start_idx]);

    // Output
    println(N, K);
    // Directions as a single string
    printf("%s\n", jump_dirs.c_str());
    for (auto &p : plants) {
        println(p.first, p.second);
    }

    return 0;
}
