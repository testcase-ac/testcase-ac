#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of Holsteins and Guernseys
    int H = rnd.next(1, 10);
    int G = rnd.next(1, 10);

    // Choose pattern: 0 = Holstein cluster, 1 = Guernsey cluster, 2 = uniform
    int mode = rnd.next(0, 2);

    int bound = 10;
    // Cluster centers
    int cxH = rnd.next(0, bound), cyH = rnd.next(0, bound);
    int cxG = rnd.next(0, bound), cyG = rnd.next(0, bound);
    int radius = rnd.next(1, 4);

    vector<pair<int,int>> Hs, Gs;

    if (mode == 0) {
        // Cluster Holsteins around (cxH, cyH)
        for (int i = 0; i < H; i++) {
            int dx = rnd.next(-radius, radius);
            int dy = rnd.next(-radius, radius);
            int x = min(max(0, cxH + dx), bound);
            int y = min(max(0, cyH + dy), bound);
            Hs.emplace_back(x, y);
        }
        // Uniform Guernseys
        for (int i = 0; i < G; i++) {
            int x = rnd.next(0, bound);
            int y = rnd.next(0, bound);
            Gs.emplace_back(x, y);
        }
    } else if (mode == 1) {
        // Uniform Holsteins
        for (int i = 0; i < H; i++) {
            int x = rnd.next(0, bound);
            int y = rnd.next(0, bound);
            Hs.emplace_back(x, y);
        }
        // Cluster Guernseys around (cxG, cyG)
        for (int i = 0; i < G; i++) {
            int dx = rnd.next(-radius, radius);
            int dy = rnd.next(-radius, radius);
            int x = min(max(0, cxG + dx), bound);
            int y = min(max(0, cyG + dy), bound);
            Gs.emplace_back(x, y);
        }
    } else {
        // Both uniform
        for (int i = 0; i < H; i++) {
            int x = rnd.next(0, bound);
            int y = rnd.next(0, bound);
            Hs.emplace_back(x, y);
        }
        for (int i = 0; i < G; i++) {
            int x = rnd.next(0, bound);
            int y = rnd.next(0, bound);
            Gs.emplace_back(x, y);
        }
    }

    // Output
    println(H, G);
    for (auto &p : Hs) println(p.first, p.second);
    for (auto &p : Gs) println(p.first, p.second);

    return 0;
}
