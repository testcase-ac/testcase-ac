#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Seg { int x1, y1, x2, y2; };

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of roads and query time
    int N = rnd.next(2, 10);
    int T = rnd.next(0, 20);

    // Split into some horizontals and verticals
    int H = rnd.next(1, N - 1);
    int V = N - H;

    // Random grid size, ensuring enough room
    int X_MAX = rnd.next(V + 3, V + 10);
    int Y_MAX = rnd.next(H + 3, H + 10);

    // Choose distinct y-levels for horizontals in [1, Y_MAX-1]
    vector<int> ys;
    for (int y = 1; y < Y_MAX; y++) ys.push_back(y);
    shuffle(ys.begin(), ys.end());
    ys.resize(H);

    // Choose distinct x-levels for verticals in [1, X_MAX-1]
    vector<int> xs;
    for (int x = 1; x < X_MAX; x++) xs.push_back(x);
    shuffle(xs.begin(), xs.end());
    xs.resize(V);

    // Build segments: horizontals span full [0, X_MAX], verticals span full [0, Y_MAX]
    vector<Seg> segs;
    for (int i = 0; i < H; i++) {
        int y = ys[i];
        segs.push_back({0, y, X_MAX, y});
    }
    for (int j = 0; j < V; j++) {
        int x = xs[j];
        segs.push_back({x, 0, x, Y_MAX});
    }

    // Shuffle and pick a random starting segment and endpoint
    shuffle(segs.begin(), segs.end());
    int start_idx = rnd.next(0, N - 1);
    swap(segs[0], segs[start_idx]);
    if (rnd.next(0, 1)) {
        swap(segs[0].x1, segs[0].x2);
        swap(segs[0].y1, segs[0].y2);
    }

    // Output
    println(N, T);
    for (auto &s : segs) {
        println(s.x1, s.y1, s.x2, s.y2);
    }
    return 0;
}
