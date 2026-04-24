#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid dimensions hyper-parameters
    int H = rnd.next(1, 4);
    int W = rnd.next(1, 4);
    int total = H * W;
    int K = rnd.next(1, total);

    // Grow a connected set of K cells in the HxW grid
    vector<vector<bool>> used(H, vector<bool>(W, false));
    vector<vector<bool>> inFront(H, vector<bool>(W, false));
    vector<pair<int,int>> cells, front;

    int si = rnd.next(0, H - 1), sj = rnd.next(0, W - 1);
    used[si][sj] = true;
    cells.emplace_back(si, sj);
    auto addNei = [&](int i, int j) {
        if (i >= 0 && i < H && j >= 0 && j < W && !used[i][j] && !inFront[i][j]) {
            inFront[i][j] = true;
            front.emplace_back(i, j);
        }
    };
    addNei(si - 1, sj); addNei(si + 1, sj);
    addNei(si, sj - 1); addNei(si, sj + 1);

    while ((int)cells.size() < K && !front.empty()) {
        int idx = rnd.next((int)front.size());
        auto [ci, cj] = front[idx];
        // remove from frontier
        front[idx] = front.back();
        front.pop_back();
        inFront[ci][cj] = false;
        // use it
        used[ci][cj] = true;
        cells.emplace_back(ci, cj);
        // add its neighbors
        addNei(ci - 1, cj); addNei(ci + 1, cj);
        addNei(ci, cj - 1); addNei(ci, cj + 1);
    }

    // Collect fence segments, deduplicated
    set<tuple<int,int,int,int>> segs;
    double subdivProb = rnd.next(0.0, 1.0);
    for (auto &c : cells) {
        int i = c.first, j = c.second;
        pair<int,int> cr[4] = {
            {i, j}, {i+1, j}, {i+1, j+1}, {i, j+1}
        };
        // add the four border edges
        for (int t = 0; t < 4; t++) {
            auto p = cr[t], q = cr[(t+1)%4];
            int x1 = p.first, y1 = p.second, x2 = q.first, y2 = q.second;
            if (make_pair(x1,y1) > make_pair(x2,y2))
                swap(x1, x2), swap(y1, y2);
            segs.emplace(x1, y1, x2, y2);
        }
        // randomly subdivide into two triangles
        if (rnd.next() < subdivProb) {
            pair<int,int> d1 = cr[0], d2 = cr[2];
            if (rnd.next(0, 1) == 1) {
                d1 = cr[1];
                d2 = cr[3];
            }
            int x1 = d1.first, y1 = d1.second, x2 = d2.first, y2 = d2.second;
            if (make_pair(x1,y1) > make_pair(x2,y2))
                swap(x1, x2), swap(y1, y2);
            segs.emplace(x1, y1, x2, y2);
        }
    }

    // Turn segments into a vector and shuffle for variability
    vector<tuple<int,int,int,int>> out(segs.begin(), segs.end());
    shuffle(out.begin(), out.end());

    // Output
    println((int)out.size());
    for (auto &t : out) {
        int x1,y1,x2,y2;
        tie(x1,y1,x2,y2) = t;
        println(x1, y1, x2, y2);
    }
    return 0;
}
