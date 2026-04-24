#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        // Number of islands (small for hand-checkable)
        int n = rnd.next(1, 10);
        println(n);

        // Choose coordinate range: small or large
        bool use_large = rnd.next() < 0.3;
        int cr = use_large
                 ? rnd.next(1000, 1000000)
                 : rnd.next(5, 20);

        // Occasionally force all x or all y equal
        bool same_x = rnd.next() < 0.2;
        bool same_y = rnd.next() < 0.2;
        // Prevent infinite loop if both true and n>1
        if (same_x && same_y && n > 1) {
            if (rnd.next() < 0.5) same_x = false;
            else                   same_y = false;
        }

        int x0 = same_x ? rnd.next(-cr, cr) : 0;
        int y0 = same_y ? rnd.next(-cr, cr) : 0;

        vector<pair<int,int>> pts;
        pts.reserve(n);

        // Hyper-parameter: cluster some points or spread uniformly
        bool do_cluster = rnd.next() < 0.3;
        int cluster_cx = 0, cluster_cy = 0;
        if (do_cluster) {
            cluster_cx = rnd.next(-cr, cr);
            cluster_cy = rnd.next(-cr, cr);
        }

        // Generate unique points
        while ((int)pts.size() < n) {
            int x, y;
            if (same_x) {
                x = x0;
            } else if (do_cluster && rnd.next() < 0.5) {
                // cluster around cluster_cx
                int d = rnd.next(-5, 5);
                x = cluster_cx + d;
            } else {
                x = rnd.next(-cr, cr);
            }

            if (same_y) {
                y = y0;
            } else if (do_cluster && rnd.next() < 0.5) {
                // cluster around cluster_cy
                int d = rnd.next(-5, 5);
                y = cluster_cy + d;
            } else {
                y = rnd.next(-cr, cr);
            }

            bool dup = false;
            for (auto &p : pts) {
                if (p.first == x && p.second == y) {
                    dup = true;
                    break;
                }
            }
            if (!dup) {
                pts.emplace_back(x, y);
            }
        }

        // Shuffle order
        shuffle(pts.begin(), pts.end());

        // Output points
        for (auto &p : pts) {
            println(p.first, p.second);
        }
    }

    return 0;
}
