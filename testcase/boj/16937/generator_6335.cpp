#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for grid size with bias
    int hBias = rnd.next(-2, 2);
    int wBias = rnd.next(-2, 2);
    int H = rnd.wnext(100, hBias) + 1;
    int W = rnd.wnext(100, wBias) + 1;
    // Number of stickers
    int N = rnd.next(2, 15);
    vector<pair<int,int>> stickers;
    stickers.reserve(N);
    int minS = min(H, W);
    for (int i = 0; i < N; i++) {
        int type = rnd.next(0, 2);
        int R, C;
        if (type == 0) {
            // fits normally
            R = rnd.next(1, H);
            C = rnd.next(1, W);
        } else if (type == 1) {
            // fits when rotated
            R = rnd.next(1, W);
            C = rnd.next(1, H);
        } else {
            // too big to fit in either orientation, if possible
            if (minS < 100) {
                R = rnd.next(minS + 1, 100);
                C = rnd.next(minS + 1, 100);
            } else {
                // fallback to normal if grid is full 100x100
                R = rnd.next(1, H);
                C = rnd.next(1, W);
            }
        }
        stickers.emplace_back(R, C);
    }
    // Output
    println(H, W);
    println(N);
    for (auto &p : stickers) {
        println(p.first, p.second);
    }
    return 0;
}
