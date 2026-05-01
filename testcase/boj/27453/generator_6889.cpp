#include "testlib.h"
#include <vector>
#include <string>
#include <deque>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // grid size small for manual verification
    int N = rnd.next(4, 9);
    int M = rnd.next(4, 9);
    // choose path length D (Manhattan distance)
    int D = rnd.next(2, min(N - 2, M - 2));
    int rx = rnd.next(0, D);
    int ry = D - rx;
    bool solvable = rnd.next(0, 1);
    int K;
    vector<int> digits; // digits for intermediate cells
    if (solvable) {
        // pick K and generate digits so sum of any recent up to 3 <= K
        K = rnd.next(0, 27);
        deque<int> last;
        for (int i = 0; i < D - 1; i++) {
            int sum_prev = 0;
            for (int v : last) sum_prev += v;
            int mx = K - sum_prev;
            if (mx < 0) mx = 0;
            if (mx > 9) mx = 9;
            int d = rnd.next(0, mx);
            digits.push_back(d);
            last.push_back(d);
            if ((int)last.size() > 2) last.pop_front();
        }
    } else {
        // unsolvable: K small, digits too large so even first cell fails
        K = rnd.next(0, 5);
        for (int i = 0; i < D - 1; i++) {
            int lo = max(K + 1, 1);
            int d = rnd.next(lo, 9);
            digits.push_back(d);
        }
    }
    // build grid full of walls
    vector<string> grid(N, string(M, 'X'));
    // trace path: start at (0,0)
    int r = 0, c = 0;
    grid[r][c] = 'S';
    // move right rx steps
    for (int i = 0; i < rx; i++) {
        c++;
        // position index = i+1; intermediate if <= D-1
        if (i < D - 1) {
            char ch = char('0' + digits[i]);
            grid[r][c] = ch;
        }
    }
    // move down ry steps
    for (int j = 0; j < ry; j++) {
        r++;
        // overall index of this cell: rx + j + 1; intermediate if <= D-1
        if (rx + j < D - 1) {
            int idx = rx + j;
            char ch = char('0' + digits[idx]);
            grid[r][c] = ch;
        }
    }
    // mark goal
    grid[r][c] = 'H';
    // output
    println(N, M, K);
    for (auto &row : grid) println(row);
    return 0;
}
