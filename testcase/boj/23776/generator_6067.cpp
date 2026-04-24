#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Decide whether to generate a circumnavigation (yes-case) or not (no-case)
    bool circ = rnd.next(0, 1) == 1;
    if (circ) {
        // Choose k dividing 360, k>=3, so that step=360/k is integer and <180
        vector<int> divs = {3,4,5,6,8,9,10,12};
        int k = rnd.any(divs);
        int step = 360 / k;
        // Prepare waypoints on the equator at evenly spaced longitudes
        vector<pair<int,int>> pts;
        for (int i = 0; i < k; i++) {
            int lam = (i * step) % 360;
            if (lam >= 180) lam -= 360;
            pts.emplace_back(0, lam);
        }
        // Output
        println(k);
        for (auto &p : pts) println(p.first, p.second);
    } else {
        // Generate a cluster on equator within a longitude window <=178,
        // so that no meridian outside window is visited -> non-circ
        int n = rnd.next(2, 10);
        // minimal half-window t so that 2*t+1 >= n
        int t_low = max(1, (n + 1) / 2);
        int t = rnd.next(t_low, 89);
        int w = 2 * t; // window width
        int c_low = -179 + t;
        int c_high =  179 - t;
        int c = rnd.next(c_low, c_high);
        int left = c - t;
        int right = c + t;
        // build available integer longitudes in [left, right]
        vector<int> L;
        for (int x = left; x <= right; x++) L.push_back(x);
        shuffle(L.begin(), L.end());
        L.resize(n);
        shuffle(L.begin(), L.end());
        // Output
        println(n);
        for (int lam : L) {
            println(0, lam);
        }
    }
    return 0;
}
