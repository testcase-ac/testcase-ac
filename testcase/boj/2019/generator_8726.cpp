#include "testlib.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Seg {
    int x1, y1, x2, y2;
};

void addSeg(vector<Seg>& segs, int x1, int y1, int x2, int y2) {
    segs.push_back({x1, y1, x2, y2});
}

void addRegularPolygon(vector<Seg>& segs, int cx, int cy, int k, int R,
                       vector<pair<int,int>> *outVertices = nullptr) {
    const double PI = acos(-1.0);
    for (int attempt = 0; attempt < 10; ++attempt) {
        vector<pair<int,int>> pts;
        double base = rnd.next(0, 359) * PI / 180.0;
        for (int i = 0; i < k; ++i) {
            double ang = base + 2.0 * PI * i / k;
            int x = cx + int(std::round(R * cos(ang)));
            int y = cy + int(std::round(R * sin(ang)));
            if (x < 0) x = 0;
            if (y < 0) y = 0;
            pts.push_back({x, y});
        }
        bool ok = true;
        for (int i = 0; i < k && ok; ++i)
            for (int j = i + 1; j < k; ++j)
                if (pts[i] == pts[j]) {
                    ok = false;
                    break;
                }
        if (!ok) continue;

        for (int i = 0; i < k; ++i) {
            auto p1 = pts[i];
            auto p2 = pts[(i + 1) % k];
            addSeg(segs, p1.first, p1.second, p2.first, p2.second);
        }
        if (outVertices) {
            outVertices->insert(outVertices->end(), pts.begin(), pts.end());
        }
        return;
    }
    // Fallback: axis-aligned square
    vector<pair<int,int>> pts;
    pts.push_back({cx - R, cy - R});
    pts.push_back({cx + R, cy - R});
    pts.push_back({cx + R, cy + R});
    pts.push_back({cx - R, cy + R});
    for (int i = 0; i < 4; ++i) {
        auto p1 = pts[i];
        auto p2 = pts[(i + 1) % 4];
        addSeg(segs, p1.first, p1.second, p2.first, p2.second);
    }
    if (outVertices) {
        outVertices->insert(outVertices->end(), pts.begin(), pts.end());
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Seg> segs;

    int type = rnd.next(0, 8);

    switch (type) {
        case 0: {
            // Single simple triangle
            addSeg(segs, 0, 0, 4, 0);
            addSeg(segs, 4, 0, 2, 3);
            addSeg(segs, 2, 3, 0, 0);
            break;
        }
        case 1: {
            // Multiple disjoint simple polygons (2-3)
            int polyCnt = rnd.next(2, 3);
            int baseX = 50;
            int baseY = 60;
            int spacing = 60;
            for (int p = 0; p < polyCnt; ++p) {
                int cx = baseX + p * spacing;
                int cy = baseY + rnd.next(-10, 10);
                int k = rnd.next(3, 6);
                int R = rnd.next(8, 15);
                addRegularPolygon(segs, cx, cy, k, R, nullptr);
            }
            break;
        }
        case 2: {
            // One triangle with a dangling segment attached (invalid polygon)
            addSeg(segs, 10, 10, 30, 10);
            addSeg(segs, 30, 10, 20, 25);
            addSeg(segs, 20, 25, 10, 10);
            // Dangling edge from a vertex
            addSeg(segs, 10, 10, 10, 0);
            break;
        }
        case 3: {
            // Two triangles sharing a vertex
            // First triangle
            addSeg(segs, 10, 10, 30, 10);
            addSeg(segs, 30, 10, 20, 25);
            addSeg(segs, 20, 25, 10, 10);
            // Second triangle sharing vertex (30,10)
            addSeg(segs, 30, 10, 50, 10);
            addSeg(segs, 50, 10, 40, 25);
            addSeg(segs, 40, 25, 30, 10);
            break;
        }
        case 4: {
            // Rectangular grid, 2x2 or 3x3 cells
            int w = rnd.next(2, 3);
            int h = rnd.next(2, 3);
            int len = 10;
            int x0 = 10, y0 = 10;
            // Horizontal lines
            for (int i = 0; i <= h; ++i) {
                int y = y0 + i * len;
                addSeg(segs, x0, y, x0 + w * len, y);
            }
            // Vertical lines
            for (int j = 0; j <= w; ++j) {
                int x = x0 + j * len;
                addSeg(segs, x, y0, x, y0 + h * len);
            }
            break;
        }
        case 5: {
            // Random graph on points (crossing segments allowed)
            int P = rnd.next(4, 7);
            vector<pair<int,int>> pts;
            while ((int)pts.size() < P) {
                int x = rnd.next(0, 80);
                int y = rnd.next(0, 80);
                bool dup = false;
                for (auto &p : pts) {
                    if (p.first == x && p.second == y) {
                        dup = true;
                        break;
                    }
                }
                if (!dup) pts.push_back({x, y});
            }
            int maxM = min(P * (P - 1) / 2, 15);
            int M = rnd.next(P - 1, maxM);
            vector<pair<int,int>> edges;
            while ((int)edges.size() < M) {
                int u = rnd.next(0, P - 1);
                int v = rnd.next(0, P - 1);
                if (u == v) continue;
                int a = min(u, v), b = max(u, v);
                bool dup = false;
                for (auto &e : edges) {
                    if (e.first == a && e.second == b) {
                        dup = true;
                        break;
                    }
                }
                if (dup) continue;
                edges.push_back({a, b});
                auto p1 = pts[u];
                auto p2 = pts[v];
                addSeg(segs, p1.first, p1.second, p2.first, p2.second);
            }
            break;
        }
        case 6: {
            // Multiple polygons plus some extra noise segments
            int polyCnt = rnd.next(2, 3);
            int baseX = 60;
            int baseY = 60;
            int spacing = 70;
            vector<pair<int,int>> allVertices;
            for (int p = 0; p < polyCnt; ++p) {
                int cx = baseX + p * spacing;
                int cy = baseY + rnd.next(-15, 15);
                int k = rnd.next(3, 5);
                int R = rnd.next(10, 18);
                vector<pair<int,int>> verts;
                addRegularPolygon(segs, cx, cy, k, R, &verts);
                allVertices.insert(allVertices.end(), verts.begin(), verts.end());
            }
            int noiseCnt = rnd.next(1, 5);
            for (int i = 0; i < noiseCnt; ++i) {
                int mode = rnd.next(0, 2);
                int x1, y1, x2, y2;
                if (mode == 0 && (int)allVertices.size() >= 2) {
                    int a = rnd.next(0, (int)allVertices.size() - 1);
                    int b = rnd.next(0, (int)allVertices.size() - 1);
                    if (a == b) b = (b + 1) % (int)allVertices.size();
                    x1 = allVertices[a].first;
                    y1 = allVertices[a].second;
                    x2 = allVertices[b].first;
                    y2 = allVertices[b].second;
                } else if (mode == 1 && !allVertices.empty()) {
                    int a = rnd.next(0, (int)allVertices.size() - 1);
                    x1 = allVertices[a].first;
                    y1 = allVertices[a].second;
                    x2 = rnd.next(0, 250);
                    y2 = rnd.next(0, 250);
                } else {
                    x1 = rnd.next(0, 250);
                    y1 = rnd.next(0, 250);
                    x2 = rnd.next(0, 250);
                    y2 = rnd.next(0, 250);
                    if (x1 == x2 && y1 == y2) x2 = (x2 + 5) % 250;
                }
                addSeg(segs, x1, y1, x2, y2);
            }
            break;
        }
        case 7: {
            // Very small cases: N = 1 or 2
            int variant = rnd.next(0, 2);
            if (variant == 0) {
                // Single segment
                addSeg(segs, 0, 0, 10, 0);
            } else {
                // Two segments: either sharing a point or disjoint
                if (rnd.next(0, 1) == 0) {
                    // Sharing endpoint -> angle
                    addSeg(segs, 0, 0, 10, 0);
                    addSeg(segs, 0, 0, 0, 10);
                } else {
                    // Disjoint segments
                    addSeg(segs, 0, 0, 10, 0);
                    addSeg(segs, 20, 5, 30, 5);
                }
            }
            break;
        }
        case 8: {
            // Sample from statement (23 segments, answer = 2 there)
            addSeg(segs, 70, 160, 100, 200);
            addSeg(segs, 60, 60, 70, 160);
            addSeg(segs, 100, 120, 130, 130);
            addSeg(segs, 90, 70, 140, 110);
            addSeg(segs, 70, 160, 70, 110);
            addSeg(segs, 70, 110, 120, 90);
            addSeg(segs, 70, 160, 120, 140);
            addSeg(segs, 120, 140, 120, 90);
            addSeg(segs, 90, 70, 100, 120);
            addSeg(segs, 130, 130, 140, 110);
            addSeg(segs, 60, 60, 110, 140);
            addSeg(segs, 110, 140, 160, 80);
            addSeg(segs, 150, 160, 160, 80);
            addSeg(segs, 120, 170, 160, 80);
            addSeg(segs, 120, 140, 150, 140);
            addSeg(segs, 140, 90, 160, 120);
            addSeg(segs, 160, 120, 170, 130);
            addSeg(segs, 170, 130, 190, 120);
            addSeg(segs, 200, 80, 220, 50);
            addSeg(segs, 200, 80, 230, 110);
            addSeg(segs, 220, 90, 230, 110);
            addSeg(segs, 220, 90, 230, 80);
            addSeg(segs, 220, 50, 230, 80);
            break;
        }
    }

    // Ensure within problem constraints and size limit goals
    if (segs.empty()) {
        // Fallback: simple segment
        addSeg(segs, 0, 0, 1, 0);
    }
    if ((int)segs.size() > 25) {
        // Very unlikely with the above construction, but trim if needed
        segs.resize(25);
    }

    println((int)segs.size());
    for (auto &s : segs) {
        println(s.x1, s.y1, s.x2, s.y2);
    }

    return 0;
}
