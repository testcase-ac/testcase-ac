#include "testlib.h"
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Pond radius and net length (both at least 1)
    int R = rnd.next(5, 50);
    int L = rnd.next(1, 2 * R);

    // Number of lotus petals and ducks
    int N = rnd.next(0, 8);
    int M = rnd.next(0, 8);

    println(R, L);
    println(N, M);

    // Generate lotus petals
    vector<tuple<int,int,int>> pads;
    int k_touch = rnd.next(0, N);  // how many touch the boundary
    // First generate some petals that touch pond boundary
    for (int i = 0; i < k_touch; i++) {
        int pr = rnd.next(1, max(1, R / 2));
        bool horiz = rnd.next(0, 1);
        int sign = rnd.next(0, 1) ? 1 : -1;
        int x = horiz ? sign * (R - pr) : 0;
        int y = horiz ? 0 : sign * (R - pr);
        pads.emplace_back(x, y, pr);
    }
    // Then generate the rest fully inside
    for (int i = k_touch; i < N; i++) {
        int pr = rnd.next(1, max(1, R / 3));
        int maxc = R - pr;
        if (maxc < 0) maxc = 0;
        int x, y;
        do {
            x = rnd.next(-maxc, maxc);
            y = rnd.next(-maxc, maxc);
        } while (1LL * x * x + 1LL * y * y > 1LL * (R - pr) * (R - pr));
        pads.emplace_back(x, y, pr);
    }
    shuffle(pads.begin(), pads.end());
    for (auto &t : pads) {
        int x, y, pr;
        tie(x, y, pr) = t;
        println(x, y, pr);
    }

    // Generate ducks
    vector<pair<int,int>> ducks;
    double p_near = rnd.next(0.0, 1.0);
    for (int i = 0; i < M; i++) {
        int x, y;
        if (!pads.empty() && rnd.next() < p_near) {
            // Place near a random pad
            int idx = rnd.next(0, (int)pads.size() - 1);
            int px, py, pr;
            tie(px, py, pr) = pads[idx];
            int dir = rnd.next(0, 3);
            int delta = rnd.next(0, L);
            if (dir == 0)      { x = px + pr + delta; y = py; }
            else if (dir == 1) { x = px - pr - delta; y = py; }
            else if (dir == 2) { x = px; y = py + pr + delta; }
            else               { x = px; y = py - pr - delta; }
            // If outside pond, fallback to random
            if (1LL * x * x + 1LL * y * y > 1LL * R * R) {
                do {
                    x = rnd.next(-R, R);
                    y = rnd.next(-R, R);
                } while (1LL * x * x + 1LL * y * y > 1LL * R * R);
            }
        } else {
            // Completely random inside pond
            do {
                x = rnd.next(-R, R);
                y = rnd.next(-R, R);
            } while (1LL * x * x + 1LL * y * y > 1LL * R * R);
        }
        ducks.emplace_back(x, y);
    }
    shuffle(ducks.begin(), ducks.end());
    for (auto &d : ducks) println(d.first, d.second);

    return 0;
}
