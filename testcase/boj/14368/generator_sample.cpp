#include "testlib.h"
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<array<int, 4>> cases;
    vector<array<int, 4>> anchors = {
        {1, 1, 1, 1},
        {1, 1, 1, 10},
        {1, 1, 10, 1},
        {1, 1, 10, 10},
        {1, 10, 10, 1},
        {1, 10, 10, 10},
        {10, 10, 10, 1},
        {10, 10, 10, 10},
    };

    shuffle(anchors.begin(), anchors.end());
    int anchorCount = rnd.next(2, 5);
    for (int i = 0; i < anchorCount; ++i) {
        cases.push_back(anchors[i]);
    }

    int randomCount = rnd.next(8, 24);
    for (int i = 0; i < randomCount; ++i) {
        int mode = rnd.next(0, 5);
        int j;
        int p;
        int s;

        if (mode == 0) {
            j = 1;
            p = rnd.next(j, 3);
            s = rnd.next(p, 5);
        } else if (mode == 1) {
            j = rnd.next(1, 4);
            p = rnd.next(j, 6);
            s = rnd.next(p, 10);
        } else if (mode == 2) {
            j = rnd.next(7, 10);
            p = rnd.next(j, 10);
            s = rnd.next(p, 10);
        } else if (mode == 3) {
            j = rnd.next(1, 10);
            p = j;
            s = rnd.next(p, 10);
        } else if (mode == 4) {
            j = rnd.next(1, 8);
            p = rnd.next(j, 10);
            s = p;
        } else {
            j = rnd.next(1, 10);
            p = rnd.next(j, 10);
            s = rnd.next(p, 10);
        }

        int kMode = rnd.next(0, 4);
        int k;
        if (kMode == 0) {
            k = 1;
        } else if (kMode == 1) {
            k = 10;
        } else if (kMode == 2) {
            k = rnd.next(1, min(10, s));
        } else {
            k = rnd.next(1, 10);
        }

        cases.push_back({j, p, s, k});
    }

    println(static_cast<int>(cases.size()));
    for (const auto& testCase : cases) {
        println(testCase[0], testCase[1], testCase[2], testCase[3]);
    }

    return 0;
}
