#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int W = rnd.next(5, 20);
    int H = rnd.next(5, 20);
    int N = rnd.next(1, 8);
    bool preferLongSide = rnd.next() < 0.5;

    // Weighting parameters for distances
    int tShop = rnd.next(-1, 1);
    int tGuard = rnd.next(-1, 1);

    // Prepare side sets
    vector<int> allSides = {1, 2, 3, 4};
    vector<int> longSides = (W >= H ? vector<int>{1, 2} : vector<int>{3, 4});

    // Generate shops
    vector<pair<int,int>> shops;
    shops.reserve(N);
    for (int i = 0; i < N; i++) {
        int side;
        if (preferLongSide && rnd.next() < 0.7) {
            side = rnd.any(longSides);
        } else {
            side = rnd.next(1, 4);
        }
        int dist;
        if (side == 1 || side == 2) {
            // north/south: width direction
            dist = rnd.wnext(W - 1, tShop) + 1;
        } else {
            // west/east: height direction
            dist = rnd.wnext(H - 1, tShop) + 1;
        }
        shops.emplace_back(side, dist);
    }

    // Generate guard position
    int gSide = rnd.any(allSides);
    int gDist;
    if (gSide == 1 || gSide == 2) {
        gDist = rnd.wnext(W - 1, tGuard) + 1;
    } else {
        gDist = rnd.wnext(H - 1, tGuard) + 1;
    }

    // Output
    println(W, H);
    println(N);
    for (auto &p : shops) {
        println(p.first, p.second);
    }
    println(gSide, gDist);

    return 0;
}
