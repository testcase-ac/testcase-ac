#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

const string TARGET = "MOBIS";
const int DR[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DC[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

char randomLetter(bool biased) {
    if (biased && rnd.next(100) < 70) {
        return TARGET[rnd.next(static_cast<int>(TARGET.size()))];
    }
    return static_cast<char>('A' + rnd.next(26));
}

bool canPlace(int n, int r, int c, int dir) {
    int er = r + 4 * DR[dir];
    int ec = c + 4 * DC[dir];
    return 0 <= er && er < n && 0 <= ec && ec < n;
}

void placeWord(vector<string>& grid, int r, int c, int dir) {
    for (int i = 0; i < 5; ++i) {
        grid[r + i * DR[dir]][c + i * DC[dir]] = TARGET[i];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(5, 9);
    } else if (mode == 2) {
        n = rnd.next(8, 16);
    } else {
        n = rnd.next(20, 30);
    }

    bool biased = mode != 0 && rnd.next(100) < 65;
    vector<string> grid(n, string(n, 'X'));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            grid[r][c] = randomLetter(biased);
        }
    }

    if (n >= 5 && mode != 1) {
        int placements = rnd.next(1, mode == 2 ? 6 : 12);
        for (int attempt = 0; attempt < placements * 20 && placements > 0; ++attempt) {
            int r = rnd.next(n);
            int c = rnd.next(n);
            int dir = rnd.next(8);
            if (!canPlace(n, r, c, dir)) {
                continue;
            }
            placeWord(grid, r, c, dir);
            --placements;
        }
    }

    println(n);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
