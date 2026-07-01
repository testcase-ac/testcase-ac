#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    constexpr int maxN = 100000;

    int t = rnd.next(1, 12);
    vector<int> values;
    values.reserve(t);

    vector<int> anchors = {1, 2, 3, 4, 5, maxN - 2, maxN - 1, maxN};
    shuffle(anchors.begin(), anchors.end());

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 5);
        int n;
        if (mode == 0 && !anchors.empty()) {
            n = anchors.back();
            anchors.pop_back();
        } else if (mode <= 2) {
            n = rnd.next(1, 30);
        } else if (mode == 3) {
            n = rnd.next(31, 1000);
        } else {
            n = rnd.next(maxN - 2000, maxN);
        }
        values.push_back(n);
    }

    println(t);
    for (int n : values) {
        println("");
        println(n);
    }

    return 0;
}
