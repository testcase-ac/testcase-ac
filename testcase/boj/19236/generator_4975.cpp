#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Prepare fish numbers 1..16 and shuffle positions
    vector<int> fish(16);
    iota(fish.begin(), fish.end(), 1);
    shuffle(fish.begin(), fish.end());
    // Hyper-parameter: bias for directions
    // t > 0 biases to larger directions, t < 0 to smaller ones
    int t = rnd.next(-3, 3);
    // Generate directions 1..8 with weighted sampling
    vector<int> dir(16);
    for (int i = 0; i < 16; i++) {
        dir[i] = rnd.wnext(8, t) + 1;
    }
    // Output in 4 rows, each with 4 pairs (fish number, direction)
    for (int r = 0; r < 4; r++) {
        vector<int> row;
        for (int c = 0; c < 4; c++) {
            int idx = r * 4 + c;
            row.push_back(fish[idx]);
            row.push_back(dir[idx]);
        }
        println(row);
    }
    return 0;
}
