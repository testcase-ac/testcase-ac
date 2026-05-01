#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int M = 0, S = 0;
    int sx = 1, sy = 1;
    vector<tuple<int,int,int>> fish; // (fx, fy, d)

    int type = rnd.next(0, 6);

    switch (type) {
        case 0: { // small random
            M = rnd.next(1, 3);
            S = rnd.next(1, 5); // S small
            for (int i = 0; i < M; i++) {
                int fx = rnd.next(1, 4);
                int fy = rnd.next(1, 4);
                int d  = rnd.next(1, 8);
                fish.emplace_back(fx, fy, d);
            }
            sx = rnd.next(1, 4);
            sy = rnd.next(1, 4);
            break;
        }
        case 1: { // clustered fish
            M = rnd.next(4, 10);
            S = rnd.next(5, 12); // S <= 12
            int bx = rnd.next(1, 4);
            int by = rnd.next(1, 4);
            for (int i = 0; i < M; i++) {
                int d = rnd.next(1, 8);
                fish.emplace_back(bx, by, d);
            }
            bool sameCell = rnd.next(0, 1);
            if (sameCell) {
                sx = bx; sy = by;
            } else {
                do {
                    sx = rnd.next(1, 4);
                    sy = rnd.next(1, 4);
                } while (sx == bx && sy == by);
            }
            break;
        }
        case 2: { // edge-heavy positions
            M = rnd.next(4, 10);
            S = rnd.next(8, 16); // S <= 16
            vector<pair<int,int>> cells;
            for (int c = 1; c <= 4; c++) {
                cells.emplace_back(1, c);
                cells.emplace_back(4, c);
                cells.emplace_back(c, 1);
                cells.emplace_back(c, 4);
            }
            for (int i = 0; i < M; i++) {
                auto p = rnd.any(cells);
                int fx = p.first;
                int fy = p.second;
                int d  = rnd.next(1, 8);
                fish.emplace_back(fx, fy, d);
            }
            sx = rnd.next(1, 4);
            sy = rnd.next(1, 4);
            break;
        }
        case 3: { // one fish per direction in one cell
            M = rnd.next(8, 10);
            S = rnd.next(3, 10); // S <= 10
            int bx = rnd.next(1, 4);
            int by = rnd.next(1, 4);
            for (int d = 1; d <= 8; d++) {
                fish.emplace_back(bx, by, d);
            }
            for (int i = 8; i < M; i++) {
                int fx = bx;
                int fy = by;
                int d  = rnd.next(1, 8);
                fish.emplace_back(fx, fy, d);
            }
            if (rnd.next(0, 1)) {
                sx = bx; sy = by;
            } else {
                sx = rnd.next(1, 4);
                sy = rnd.next(1, 4);
            }
            break;
        }
        case 4: { // central shark, scattered fish
            M = rnd.next(6, 10);
            S = rnd.next(10, 16); // S <= 16
            vector<pair<int,int>> centers = {{2,2}, {2,3}, {3,2}, {3,3}};
            auto p = rnd.any(centers);
            sx = p.first;
            sy = p.second;
            for (int i = 0; i < M; i++) {
                int fx = rnd.next(1, 4);
                int fy = rnd.next(1, 4);
                int d  = rnd.next(1, 8);
                fish.emplace_back(fx, fy, d);
            }
            break;
        }
        case 5: { // Exactly Example 7 from statement
            M = 8;
            S = 100;
            for (int d = 1; d <= 8; d++) {
                fish.emplace_back(1, 1, d);
            }
            sx = 1; sy = 1;
            break;
        }
        case 6: { // Exactly Example 8 from statement
            M = 10;
            S = 25;
            fish.emplace_back(1, 1, 1);
            fish.emplace_back(1, 1, 2);
            fish.emplace_back(1, 1, 3);
            fish.emplace_back(1, 1, 4);
            fish.emplace_back(1, 1, 5);
            fish.emplace_back(1, 1, 6);
            fish.emplace_back(1, 1, 7);
            fish.emplace_back(1, 1, 8);
            fish.emplace_back(2, 1, 1);
            fish.emplace_back(2, 1, 1);
            sx = 2; sy = 1;
            break;
        }
    }

    // Output input
    println(M, S);
    for (auto &t : fish) {
        int fx, fy, d;
        tie(fx, fy, d) = t;
        println(fx, fy, d);
    }
    println(sx, sy);

    return 0;
}
