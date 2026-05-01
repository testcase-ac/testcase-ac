#include "testlib.h"
using namespace std;

long long cross(const pair<int,int>& a, const pair<int,int>& b, const pair<int,int>& c) {
    // cross product (b - a) x (c - a)
    long long x1 = b.first - a.first;
    long long y1 = b.second - a.second;
    long long x2 = c.first - a.first;
    long long y2 = c.second - a.second;
    return x1 * y2 - x2 * y1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 4); // number of test cases

    for (int tc = 0; tc < T; ++tc) {
        // choose n with some variability but still small
        int n;
        int sizeType = rnd.next(0, 9);
        if (sizeType < 4)       n = rnd.next(3, 6);   // small
        else if (sizeType < 8) n = rnd.next(7, 15);  // medium
        else                   n = rnd.next(16, 22); // a bit larger but still readable

        int type = rnd.next(0, 2); // 0: random grid subset, 1: many collinear + one off, 2: points in triangle
        vector<pair<int,int>> pts;

        if (type == 0) {
            // Type 0: random distinct points from a small grid, ensure not all collinear
            vector<pair<int,int>> cand;
            for (int x = -5; x <= 5; ++x)
                for (int y = -5; y <= 5; ++y)
                    cand.push_back({x, y});
            shuffle(cand.begin(), cand.end());
            pts.assign(cand.begin(), cand.begin() + n);

            // Check if all points are collinear; if so, fix by moving one point off the line
            bool allCollinear = true;
            pair<int,int> a = pts[0];
            pair<int,int> b = pts[1];
            for (int i = 2; i < n; ++i) {
                if (cross(a, b, pts[i]) != 0) {
                    allCollinear = false;
                    break;
                }
            }
            if (allCollinear) {
                // Find a new point not on line ab and not already used
                vector<pair<int,int>> cand2;
                for (int x = -10; x <= 10; ++x)
                    for (int y = -10; y <= 10; ++y)
                        cand2.push_back({x, y});
                shuffle(cand2.begin(), cand2.end());

                for (auto q : cand2) {
                    bool used = false;
                    for (auto &p : pts) {
                        if (p == q) {
                            used = true;
                            break;
                        }
                    }
                    if (used) continue;
                    if (cross(a, b, q) != 0) {
                        pts[2] = q; // replace one of the collinear points
                        allCollinear = false;
                        break;
                    }
                }
            }
            shuffle(pts.begin(), pts.end());
        } else if (type == 1) {
            // Type 1: many collinear points with exactly one clearly off-line point
            int x0 = rnd.next(-5, 5);
            int y0 = rnd.next(-5, 5);
            int dx = 0, dy = 0;
            while (dx == 0 && dy == 0) {
                dx = rnd.next(-3, 3);
                dy = rnd.next(-3, 3);
            }
            // n-1 collinear points
            for (int i = 0; i < n - 1; ++i) {
                pts.push_back({x0 + dx * i, y0 + dy * i});
            }
            // one off-line point
            pair<int,int> off;
            if (dx != 0)
                off = {x0, y0 + 1};
            else
                off = {x0 + 1, y0};

            // ensure it's not accidentally one of the collinear points (very unlikely, but check)
            bool clash = false;
            do {
                clash = false;
                for (auto &p : pts) {
                    if (p == off) {
                        clash = true;
                        break;
                    }
                }
                if (clash) {
                    if (dx != 0)
                        off.second++;
                    else
                        off.first++;
                }
            } while (clash);

            pts.push_back(off);
            shuffle(pts.begin(), pts.end());
        } else { // type == 2
            // Type 2: integer points inside/on a small right triangle
            int ox = rnd.next(-5, 5);
            int oy = rnd.next(-5, 5);
            int scale = rnd.next(2, 6); // triangle size

            // Generate all integer lattice points inside/on right triangle with vertices:
            // (ox, oy), (ox + scale, oy), (ox, oy + scale)
            vector<pair<int,int>> cand;
            for (int x = 0; x <= scale; ++x) {
                for (int y = 0; y <= scale; ++y) {
                    if (x + y <= scale) {
                        cand.push_back({ox + x, oy + y});
                    }
                }
            }
            shuffle(cand.begin(), cand.end());

            // Ensure the three vertices are present first (non-collinear base triangle)
            pair<int,int> v0 = {ox, oy};
            pair<int,int> v1 = {ox + scale, oy};
            pair<int,int> v2 = {ox, oy + scale};
            pts.push_back(v0);
            pts.push_back(v1);
            pts.push_back(v2);

            // Fill remaining points from cand, skipping duplicates
            for (auto &p : cand) {
                if ((int)pts.size() >= n) break;
                bool used = false;
                for (auto &q : pts) {
                    if (p == q) {
                        used = true;
                        break;
                    }
                }
                if (!used) pts.push_back(p);
            }

            // In rare case cand size < n (very small scale & large n), pad with random points near triangle
            while ((int)pts.size() < n) {
                int x = rnd.next(ox - 2, ox + scale + 2);
                int y = rnd.next(oy - 2, oy + scale + 2);
                pair<int,int> p = {x, y};
                bool used = false;
                for (auto &q : pts) {
                    if (p == q) {
                        used = true;
                        break;
                    }
                }
                if (!used) pts.push_back(p);
            }

            shuffle(pts.begin(), pts.end());
        }

        // Just in case, assert we have at least one non-collinear triple
        bool allCollinear = true;
        pair<int,int> a = pts[0];
        pair<int,int> b = pts[1];
        for (int i = 2; i < (int)pts.size(); ++i) {
            if (cross(a, b, pts[i]) != 0) {
                allCollinear = false;
                break;
            }
        }
        if (allCollinear) {
            // As a fallback (should practically never happen), forcibly adjust one point
            vector<pair<int,int>> cand2;
            for (int x = -10; x <= 10; ++x)
                for (int y = -10; y <= 10; ++y)
                    cand2.push_back({x, y});
            shuffle(cand2.begin(), cand2.end());
            for (auto q : cand2) {
                bool used = false;
                for (auto &p : pts) {
                    if (p == q) {
                        used = true;
                        break;
                    }
                }
                if (used) continue;
                if (cross(a, b, q) != 0) {
                    pts[2] = q;
                    break;
                }
            }
        }

        int n_out = (int)pts.size();
        println(n_out);
        for (auto &p : pts)
            println(p.first, p.second);
    }

    println(0);
    return 0;
}
