#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Base solved puzzle
    vector<char> tiles = {
        'A','B','C','D',
        'E','F','G','H',
        'I','J','K','L',
        'M','N','O','.'
    };

    // Hyper-parameters for diversity
    // Maximum number of random swaps
    int maxSwaps = rnd.next(1, 10);
    // Bias parameter for weighted sampling of swap count
    // Negative t => bias towards few swaps, positive => towards many swaps
    vector<int> biasChoices = { -3, -1, 0, 1, 3 };
    int t = rnd.any(biasChoices);
    // Determine number of swaps
    int swaps = rnd.wnext(maxSwaps + 1, t);

    // Apply random swaps
    for (int i = 0; i < swaps; i++) {
        int a = rnd.next(0, 15);
        int b = rnd.next(0, 15);
        if (a == b) {
            // ensure distinct
            b = (a + 1) % 16;
        }
        swap(tiles[a], tiles[b]);
    }

    // Occasionally reverse one row or one column for more structure
    if (rnd.next() < 0.3) {
        int row = rnd.next(0, 3);
        reverse(tiles.begin() + row*4, tiles.begin() + row*4 + 4);
    }
    if (rnd.next() < 0.3) {
        int col = rnd.next(0, 3);
        for (int i = 0; i < 2; i++) {
            swap(tiles[col + i*4], tiles[col + (3-i)*4]);
        }
    }

    // Output 4x4 puzzle
    for (int r = 0; r < 4; r++) {
        string line;
        for (int c = 0; c < 4; c++) {
            line += tiles[r*4 + c];
        }
        println(line);
    }
    return 0;
}
