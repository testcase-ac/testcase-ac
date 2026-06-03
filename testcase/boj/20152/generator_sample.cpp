#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int H = 0;
    int N = 0;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        H = N = rnd.next(0, 30);
    } else if (mode == 1) {
        vector<pair<int, int>> corners = {{0, 0}, {0, 30}, {30, 0}, {30, 30}};
        auto picked = rnd.any(corners);
        H = picked.first;
        N = picked.second;
    } else if (mode == 2) {
        H = rnd.next(0, 29);
        N = rnd.next(H + 1, 30);
    } else if (mode == 3) {
        H = rnd.next(1, 30);
        N = rnd.next(0, H - 1);
    } else if (mode == 4) {
        int base = rnd.next(0, 30);
        int delta = rnd.next(0, 3);
        H = base;
        N = rnd.next(0, 1) == 0 ? max(0, base - delta) : min(30, base + delta);
    } else {
        H = rnd.next(0, 30);
        N = rnd.next(0, 30);
    }

    println(H, N);
    return 0;
}
