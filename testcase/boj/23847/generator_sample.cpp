#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> loops = {"II", "NN", "UU"};
    const vector<string> bridges = {"IN", "IU", "NU"};
    vector<string> types;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        types = loops;
    } else if (mode == 1) {
        types = loops;
        types.push_back(rnd.any(bridges));
    } else if (mode == 2) {
        types = loops;
        vector<string> chosen = bridges;
        shuffle(chosen.begin(), chosen.end());
        types.push_back(chosen[0]);
        types.push_back(chosen[1]);
    } else {
        types = loops;
        types.insert(types.end(), bridges.begin(), bridges.end());
    }

    int n;
    if (mode == 5) {
        n = rnd.next(12, 30);
    } else if (rnd.next(0, 9) == 0) {
        n = 1;
    } else {
        n = rnd.next(2, 14);
    }

    vector<pair<string, int>> rods;
    rods.reserve(n);
    for (int i = 0; i < n; ++i) {
        string ends = rnd.any(types);
        if (ends[0] != ends[1] && rnd.next(0, 1)) {
            swap(ends[0], ends[1]);
        }

        int len;
        int lengthMode = rnd.next(0, 3);
        if (lengthMode == 0) {
            len = rnd.next(1, 9);
        } else if (lengthMode == 1) {
            len = rnd.next(990, 1000);
        } else if (lengthMode == 2) {
            len = rnd.next(1, 1000);
        } else {
            len = (i % 3 == 0) ? 1000 : rnd.next(1, 25);
        }

        rods.push_back({ends, len});
    }

    shuffle(rods.begin(), rods.end());

    println(n);
    for (const auto& rod : rods) {
        println(rod.first, rod.second);
    }

    return 0;
}
