#include "testlib.h"
using namespace std;

void randomTransform(vector<pair<int,int>>& pts) {
    if (pts.empty()) return;

    // Optional swap x and y
    if (rnd.next(0, 1) == 1) {
        for (auto &p : pts) {
            swap(p.first, p.second);
        }
    }

    // Optional mirror on x-axis
    if (rnd.next(0, 1) == 1) {
        for (auto &p : pts) {
            p.first = -p.first;
        }
    }

    // Optional mirror on y-axis
    if (rnd.next(0, 1) == 1) {
        for (auto &p : pts) {
            p.second = -p.second;
        }
    }

    // Optional small translation, staying inside bounds
    if (rnd.next(0, 1) == 1) {
        int dx = rnd.next(-20, 20);
        int dy = rnd.next(-20, 20);

        int minX = 1000000000, maxX = -1000000000;
        int minY = 1000000000, maxY = -1000000000;
        for (auto &p : pts) {
            minX = min(minX, p.first);
            maxX = max(maxX, p.first);
            minY = min(minY, p.second);
            maxY = max(maxY, p.second);
        }

        if (minX + dx >= -30000 && maxX + dx <= 30000 &&
            minY + dy >= -30000 && maxY + dy <= 30000) {
            for (auto &p : pts) {
                p.first += dx;
                p.second += dy;
            }
        }
    }

    // Shuffle point order
    shuffle(pts.begin(), pts.end());
}

void genCase(int type, vector<pair<int,int>>& pts) {
    pts.clear();

    switch (type) {
        case 0: { // Degenerate & duplicates: all same / same x / same y
            int baseX = rnd.next(-5, 5);
            int baseY = rnd.next(-5, 5);
            int mode = rnd.next(0, 2); // 0: all same, 1: same x, 2: same y
            int N = rnd.next(1, 5);
            for (int i = 0; i < N; ++i) {
                if (mode == 0) {
                    pts.emplace_back(baseX, baseY);
                } else if (mode == 1) {
                    int dy = rnd.next(-2, 2);
                    pts.emplace_back(baseX, baseY + dy);
                } else {
                    int dx = rnd.next(-2, 2);
                    pts.emplace_back(baseX + dx, baseY);
                }
            }
            // Ensure at least one exact duplicate
            if (rnd.next(0, 1) == 1) {
                pts.emplace_back(baseX, baseY);
            }
            break;
        }

        case 1: { // Two horizontal clusters (separated in x)
            int n1 = rnd.next(1, 4);
            int n2 = rnd.next(1, 4);
            int gap = rnd.next(5, 15);
            int cx1 = rnd.next(-10, 10 - gap - 1);
            int cx2 = cx1 + gap;
            int cy1 = rnd.next(-5, 5);
            int cy2 = rnd.next(-5, 5);
            for (int i = 0; i < n1; ++i) {
                int x = cx1 + rnd.next(-1, 1);
                int y = cy1 + rnd.next(-2, 2);
                pts.emplace_back(x, y);
            }
            for (int i = 0; i < n2; ++i) {
                int x = cx2 + rnd.next(-1, 1);
                int y = cy2 + rnd.next(-2, 2);
                pts.emplace_back(x, y);
            }
            break;
        }

        case 2: { // Two vertical clusters (separated in y)
            int n1 = rnd.next(1, 4);
            int n2 = rnd.next(1, 4);
            int gap = rnd.next(5, 15);
            int cy1 = rnd.next(-10, 10 - gap - 1);
            int cy2 = cy1 + gap;
            int cx1 = rnd.next(-5, 5);
            int cx2 = rnd.next(-5, 5);
            for (int i = 0; i < n1; ++i) {
                int x = cx1 + rnd.next(-2, 2);
                int y = cy1 + rnd.next(-1, 1);
                pts.emplace_back(x, y);
            }
            for (int i = 0; i < n2; ++i) {
                int x = cx2 + rnd.next(-2, 2);
                int y = cy2 + rnd.next(-1, 1);
                pts.emplace_back(x, y);
            }
            break;
        }

        case 3: { // Diagonal clusters (top-left vs bottom-right)
            int n1 = rnd.next(2, 4);
            int n2 = rnd.next(2, 4);
            int cx1 = -10, cy1 = 10;
            int cx2 = 10, cy2 = -10;
            for (int i = 0; i < n1; ++i) {
                int x = cx1 + rnd.next(-2, 2);
                int y = cy1 + rnd.next(-2, 2);
                pts.emplace_back(x, y);
            }
            for (int i = 0; i < n2; ++i) {
                int x = cx2 + rnd.next(-2, 2);
                int y = cy2 + rnd.next(-2, 2);
                pts.emplace_back(x, y);
            }
            break;
        }

        case 4: { // Points forming / filling a small rectangle
            int w = rnd.next(1, 6);
            int h = rnd.next(1, 6);
            int x0 = rnd.next(-5, 5);
            int y0 = rnd.next(-5, 5);

            // Four corners
            pts.emplace_back(x0, y0);
            pts.emplace_back(x0 + w, y0);
            pts.emplace_back(x0, y0 + h);
            pts.emplace_back(x0 + w, y0 + h);

            int extra = rnd.next(0, 4);
            for (int i = 0; i < extra; ++i) {
                int kind = rnd.next(0, 2); // 0: interior, 1: edge
                if (kind == 0) {
                    int x = x0 + rnd.next(0, w);
                    int y = y0 + rnd.next(0, h);
                    pts.emplace_back(x, y);
                } else {
                    int side = rnd.next(0, 3);
                    int x = x0 + rnd.next(0, w);
                    int y = y0 + rnd.next(0, h);
                    if (side == 0) x = x0;
                    else if (side == 1) x = x0 + w;
                    else if (side == 2) y = y0;
                    else y = y0 + h;
                    pts.emplace_back(x, y);
                }
            }
            break;
        }

        case 5: { // Points on a diagonal line
            int N = rnd.next(3, 10);
            int x0 = rnd.next(-5, 5);
            int y0 = rnd.next(-5, 5);
            int dx = rnd.next(1, 3);
            int dy = rnd.next(1, 3);
            for (int i = 0; i < N; ++i) {
                pts.emplace_back(x0 + i * dx, y0 + i * dy);
            }
            // Optional duplicate
            if (rnd.next(0, 1) == 1) {
                pts.push_back(pts[rnd.next((int)pts.size())]);
            }
            break;
        }

        case 6: { // Cluster plus far outlier(s)
            int nBulk = rnd.next(2, 7);
            int cx = rnd.next(-5, 5);
            int cy = rnd.next(-5, 5);
            for (int i = 0; i < nBulk; ++i) {
                int x = cx + rnd.next(-2, 2);
                int y = cy + rnd.next(-2, 2);
                pts.emplace_back(x, y);
            }
            int outType = rnd.next(0, 3);
            int ox[4] = {30000, -30000, -30000, 30000};
            int oy[4] = {30000, -30000, 30000, -30000};
            pts.emplace_back(ox[outType], oy[outType]);
            if ((int)pts.size() < 10 && rnd.next(0, 1) == 1) {
                int outType2 = rnd.next(0, 3);
                pts.emplace_back(ox[outType2], oy[outType2]);
            }
            break;
        }

        case 7: { // Random moderate cluster
            int N = rnd.next(5, 12);
            for (int i = 0; i < N; ++i) {
                int x = rnd.next(-10, 10);
                int y = rnd.next(-10, 10);
                pts.emplace_back(x, y);
            }
            break;
        }

        case 8: { // Extreme large rectangle with huge area
            int minX = rnd.any(vector<int>{-30000, -25000, -20000});
            int maxX = rnd.any(vector<int>{20000, 25000, 30000});
            if (minX > maxX) swap(minX, maxX);
            int minY = rnd.any(vector<int>{-30000, -25000, -20000});
            int maxY = rnd.any(vector<int>{20000, 25000, 30000});
            if (minY > maxY) swap(minY, maxY);

            pts.emplace_back(minX, minY);
            pts.emplace_back(minX, maxY);
            pts.emplace_back(maxX, minY);
            pts.emplace_back(maxX, maxY);

            int extra = rnd.next(0, 4);
            for (int i = 0; i < extra; ++i) {
                int x = rnd.next(minX, maxX);
                int y = rnd.next(minY, maxY);
                pts.emplace_back(x, y);
            }
            break;
        }

        case 9: { // Hand-crafted tricky small configuration
            // Base pattern around origin
            vector<pair<int,int>> base = {
                {0, 0},
                {0, 2},
                {2, 0},
                {2, 2},
                {1, 8},
                {5, 1}
            };
            pts = base;
            // Optional extra near one corner
            if (rnd.next(0, 1) == 1) {
                pts.emplace_back(2, 3);
            }
            break;
        }

        default:
            break;
    }

    // Safety: ensure at least 1 point, at most around 15 (all cases already do)
    if (pts.empty()) {
        pts.emplace_back(0, 0);
    }
    if ((int)pts.size() > 15) {
        pts.resize(15);
    }

    randomTransform(pts);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 4);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int type = rnd.next(0, 9);
        vector<pair<int,int>> pts;
        genCase(type, pts);

        int N = (int)pts.size();
        println(N);
        for (auto &p : pts) {
            println(p.first, p.second);
        }
    }

    return 0;
}
