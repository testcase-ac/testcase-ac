#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int L, W;
    vector<pair<int,int>> soldiers;

    int pattern = rnd.next(0, 4); // choose one of 5 patterns

    if (pattern == 0) {
        // Random scatter: medium size, no particular structure
        L = rnd.next(150, 400);
        W = rnd.next(150, 400);
        int N = rnd.next(5, 20);
        for (int i = 0; i < N; ++i) {
            int x = rnd.next(0, L);
            int y = rnd.next(0, W);
            soldiers.push_back({x, y});
        }
    } else if (pattern == 1) {
        // Strong vertical blocking chain from bottom to top, plus some noise
        L = rnd.next(200, 400);
        W = rnd.next(260, 400); // tall enough to host a chain

        int xCenter = rnd.next(L / 3, 2 * L / 3);

        // Build y-coordinates forming a chain with gaps <= 180 and touching both boundaries
        vector<int> ys;
        int y0 = rnd.next(0, 80); // within 100 of bottom
        ys.push_back(y0);

        while (true) {
            int cur = ys.back();
            if (W - cur <= 80) break; // last is already within 100 of top
            int minNext = cur + 50;  // ensure progress but keep gap not too small
            int maxNext = min(cur + 180, W); // gap <= 180 (so centers <= 180 apart)
            int nextY = rnd.next(minNext, maxNext);
            ys.push_back(nextY);
        }

        for (int y : ys) {
            int x = xCenter + rnd.next(-20, 20);
            if (x < 0) x = 0;
            if (x > L) x = L;
            soldiers.push_back({x, y});
        }

        // Add a few random extra soldiers
        int extras = rnd.next(0, 7);
        for (int i = 0; i < extras; ++i) {
            int x = rnd.next(0, L);
            int y = rnd.next(0, W);
            soldiers.push_back({x, y});
        }
    } else if (pattern == 2) {
        // Borderline distances: touches boundaries at exactly 100, and soldiers exactly 200 apart
        L = rnd.next(200, 400);
        W = rnd.next(350, 400); // ensure space for y = 100, 300, and W-100

        int xMid = L / 2;

        // S0: exactly 100 from bottom
        soldiers.push_back({xMid, 100});
        // S1: exactly 200 above S0 (distance 200 between centers)
        soldiers.push_back({xMid, 300});
        // S2: exactly 100 from top
        soldiers.push_back({xMid, W - 100});

        // Some additional random soldiers
        int extras = rnd.next(2, 10);
        for (int i = 0; i < extras; ++i) {
            int x = rnd.next(0, L);
            int y = rnd.next(0, W);
            soldiers.push_back({x, y});
        }
    } else if (pattern == 3) {
        // Two separated clusters near bottom and top, leaving a safe horizontal corridor
        L = rnd.next(200, 400);
        W = rnd.next(320, 400);
        int mid = W / 2;

        int bottomCnt = rnd.next(2, 5);
        int topCnt = rnd.next(2, 5);

        // Bottom cluster: well below the middle
        for (int i = 0; i < bottomCnt; ++i) {
            int x = rnd.next(0, L);
            int maxY = mid - 150;
            if (maxY < 0) maxY = 0;
            int y = rnd.next(0, maxY);
            soldiers.push_back({x, y});
        }

        // Top cluster: well above the middle
        for (int i = 0; i < topCnt; ++i) {
            int x = rnd.next(0, L);
            int minY = mid + 150;
            if (minY > W) minY = W;
            int y = rnd.next(minY, W);
            soldiers.push_back({x, y});
        }

        // Optional few random extras that still shouldn't close the gap too easily
        int extras = rnd.next(0, 4);
        for (int i = 0; i < extras; ++i) {
            int x = rnd.next(0, L);
            int y;
            if (rnd.next(0, 1) == 0) {
                int maxY = mid - 170;
                if (maxY < 0) maxY = 0;
                y = rnd.next(0, maxY);
            } else {
                int minY = mid + 170;
                if (minY > W) minY = W;
                y = rnd.next(minY, W);
            }
            soldiers.push_back({x, y});
        }
    } else {
        // Small or edge-focused cases: few soldiers, often on or near corners
        L = rnd.next(50, 200);
        W = rnd.next(50, 200);

        int kind = rnd.next(0, 2);
        if (kind == 0) {
            // Single soldier in the center
            soldiers.push_back({L / 2, W / 2});
        } else if (kind == 1) {
            // Soldiers at corners
            soldiers.push_back({0, 0});
            soldiers.push_back({L, 0});
            soldiers.push_back({0, W});
            soldiers.push_back({L, W});
        } else {
            // One near each side
            soldiers.push_back({0, W / 2});
            soldiers.push_back({L, W / 2});
            soldiers.push_back({L / 2, 0});
            soldiers.push_back({L / 2, W});
        }
    }

    // Ensure total count within small, readable bounds (trim randomly if needed)
    if ((int)soldiers.size() > 30) {
        shuffle(soldiers.begin(), soldiers.end());
        soldiers.resize(30);
    }

    // Shuffle soldiers for unpredictability
    shuffle(soldiers.begin(), soldiers.end());

    int N = (int)soldiers.size();

    println(L, W, N);
    for (int i = 0; i < N; ++i) {
        println(soldiers[i].first, soldiers[i].second);
    }

    return 0;
}
