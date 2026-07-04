#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> edgeCases = {
        {1, 1}, {1, 15}, {15, 1}, {15, 15}, {2, 2}, {3, 2}
    };

    int n;
    int k;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        pair<int, int> chosen = rnd.any(edgeCases);
        n = chosen.first;
        k = chosen.second;
    } else if (mode == 1) {
        n = rnd.next(1, 4);
        k = rnd.next(1, 4);
    } else if (mode == 2) {
        n = rnd.next(12, 15);
        k = rnd.next(12, 15);
    } else if (mode == 3) {
        n = rnd.next(1, 15);
        k = rnd.next(1, 3);
    } else if (mode == 4) {
        n = rnd.next(1, 3);
        k = rnd.next(1, 15);
    } else {
        int center = rnd.next(1, 15);
        n = max(1, min(15, center + rnd.next(-2, 2)));
        k = max(1, min(15, center + rnd.next(-2, 2)));
    }

    println(n, k);
    return 0;
}
