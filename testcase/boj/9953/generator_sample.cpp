#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> shops;
    int mode = rnd.next(0, 5);
    int count = rnd.next(1, 24);

    if (mode == 0) {
        vector<int> anchors = {1, 2, 49, 50, 51, 52, 99, 100};
        shuffle(anchors.begin(), anchors.end());
        shops.insert(shops.end(), anchors.begin(), anchors.begin() + rnd.next(3, (int)anchors.size()));
    } else if (mode == 1) {
        int parity = rnd.next(0, 1);
        for (int i = 0; i < count; ++i) {
            shops.push_back(1 + parity + 2 * rnd.next(0, 49));
        }
    } else if (mode == 2) {
        int lo = rnd.next(1, 80);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < count; ++i) {
            shops.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        int center = rnd.next(1, 100);
        int radius = rnd.next(0, 10);
        for (int i = 0; i < count; ++i) {
            int lo = max(1, center - radius);
            int hi = min(100, center + radius);
            shops.push_back(rnd.next(lo, hi));
        }
    } else {
        for (int i = 0; i < count; ++i) {
            shops.push_back(rnd.next(1, 100));
        }
    }

    for (int shop : shops) {
        println(shop);
    }
    println(0);

    return 0;
}
