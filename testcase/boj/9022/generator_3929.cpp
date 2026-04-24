#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 3);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        int n = rnd.next(1, 10);
        println(n);
        int distribution = rnd.next(0, 1);
        vector<int> rx = {10, 100, 1000};
        vector<int> ry = {10, 100, 1000};
        int range_x = rnd.any(rx);
        int range_y = rnd.any(ry);

        vector<pair<int,int>> pts;
        if (distribution == 1) {
            int k = rnd.next(1, min(n, 3));
            set<pair<int,int>> cst;
            while ((int)cst.size() < k) {
                int cx = rnd.next(-range_x, range_x);
                int cy = rnd.next(-range_y, range_y);
                if (cy == 0) cy = rnd.next(0, 1) ? 1 : -1;
                cst.insert({cx, cy});
            }
            vector<pair<int,int>> centers(cst.begin(), cst.end());
            int rdx = max(1, range_x / 4);
            int rdy = max(1, range_y / 4);
            set<pair<int,int>> st;
            int attempts = 0, maxAttempts = n * 20 + 100;
            while ((int)st.size() < n && attempts < maxAttempts) {
                attempts++;
                int ci = rnd.next(0, k - 1);
                int dx = rnd.next(-rdx, rdx);
                int dy = rnd.next(-rdy, rdy);
                int x = centers[ci].first + dx;
                x = x < -range_x ? -range_x : x > range_x ? range_x : x;
                int y = centers[ci].second + dy;
                y = y < -range_y ? -range_y : y > range_y ? range_y : y;
                if (y == 0) y += (centers[ci].second >= 0 ? 1 : -1);
                st.insert({x, y});
            }
            if ((int)st.size() == n) {
                pts.assign(st.begin(), st.end());
            }
        }
        if (pts.empty()) {
            set<pair<int,int>> st;
            while ((int)st.size() < n) {
                int x = rnd.next(-range_x, range_x);
                int y = rnd.next(-range_y, range_y);
                if (y == 0) continue;
                st.insert({x, y});
            }
            pts.assign(st.begin(), st.end());
        }
        shuffle(pts.begin(), pts.end());
        for (auto &p : pts) println(p.first, p.second);
    }
    return 0;
}
