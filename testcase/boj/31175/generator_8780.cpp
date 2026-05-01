#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    // Choose n with some bias: very small, small, medium, large, max
    int tp = rnd.next(1, 6);
    if (tp == 1) {
        n = 2; // smallest
    } else if (tp == 2) {
        n = rnd.next(3, 10); // small
    } else if (tp == 3) {
        n = rnd.next(10, 30); // medium-small
    } else if (tp == 4) {
        n = rnd.next(30, 100); // medium
    } else if (tp == 5) {
        n = rnd.next(100, 500); // large
    } else {
        // pick from some special values including maximum
        vector<int> special = {2, 3, 4, 5, 7, 9, 10, 20, 30, 50, 100, 200, 499, 500};
        n = rnd.any(special);
    }

    int a = 1, b = 1;

    // Choose target cell pattern
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        // Completely random
        a = rnd.next(1, n);
        b = rnd.next(1, n);
    } else if (mode == 1) {
        // Corners
        vector<pair<int,int>> corners = {
            {1,1}, {1,n}, {n,1}, {n,n}
        };
        auto p = rnd.any(corners);
        a = p.first; b = p.second;
    } else if (mode == 2) {
        // Center-ish
        if (n % 2 == 1) {
            int mid = (n + 1) / 2;
            a = mid; b = mid;
        } else {
            int m1 = n / 2;
            int m2 = m1 + 1;
            vector<pair<int,int>> centers = {
                {m1, m1}, {m1, m2}, {m2, m1}, {m2, m2}
            };
            auto p = rnd.any(centers);
            a = p.first; b = p.second;
        }
    } else if (mode == 3) {
        // Edge but not corner
        vector<pair<int,int>> edges;
        int mid = (n + 1) / 2;
        if (n > 2) {
            edges.push_back({1, mid});
            edges.push_back({n, mid});
            edges.push_back({mid, 1});
            edges.push_back({mid, n});
        } else {
            // n == 2, edges are all cells; just random
            a = rnd.next(1, n);
            b = rnd.next(1, n);
        }
        if (!edges.empty()) {
            auto p = rnd.any(edges);
            a = p.first; b = p.second;
        }
    } else {
        // Near border but not corner (if possible)
        if (n >= 3) {
            vector<pair<int,int>> near = {
                {2, 2}, {2, n - 1}, {n - 1, 2}, {n - 1, n - 1}
            };
            auto p = rnd.any(near);
            a = p.first; b = p.second;
        } else {
            // fallback for n = 2
            a = 1; b = 2;
        }
    }

    println(n, a, b);
    return 0;
}
