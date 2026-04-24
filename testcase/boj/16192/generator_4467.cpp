#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for small but diverse test
    int n = rnd.next(3, 10);
    int q = rnd.next(1, 5);
    bool narrow = rnd.next(0, 1);
    int coord_range = narrow ? 5 : 10;

    // Generate n distinct points
    set<pair<int,int>> seen;
    vector<pair<int,int>> pts;
    while ((int)pts.size() < n) {
        int x = rnd.next(-coord_range, coord_range);
        int y = rnd.next(-coord_range, coord_range);
        if (seen.emplace(x, y).second) {
            pts.emplace_back(x, y);
        }
    }

    // Output number of sites and queries
    println(n, q);
    // Output sites
    for (auto &p : pts) {
        println(p.first, p.second);
    }

    // Generate queries: some exactly on sites, others random
    for (int i = 0; i < q; i++) {
        if (!pts.empty() && rnd.next(0, 2) == 0) {
            // Query exactly at a site
            auto p = rnd.any(pts);
            println(p.first, p.second);
        } else {
            // Random query in a larger area
            int lim = coord_range * 2;
            int x = rnd.next(-lim, lim);
            int y = rnd.next(-lim, lim);
            println(x, y);
        }
    }

    return 0;
}
