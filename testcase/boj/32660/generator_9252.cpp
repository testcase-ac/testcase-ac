#include "testlib.h"
using namespace std;

struct Point {
    long long x, y;
};

bool collinear(const Point &a, const Point &b, const Point &c) {
    long long x1 = b.x - a.x;
    long long y1 = b.y - a.y;
    long long x2 = c.x - a.x;
    long long y2 = c.y - a.y;
    return x1 * y2 - y1 * x2 == 0;
}

Point genPoint(long long lo, long long hi, const vector<Point>& existing) {
    while (true) {
        long long x = rnd.next(lo, hi);
        long long y = rnd.next(lo, hi);
        bool ok = true;
        for (const auto &p : existing) {
            if (p.x == x && p.y == y) {
                ok = false;
                break;
            }
        }
        if (!ok) continue;
        int sz = (int)existing.size();
        for (int i = 0; i < sz && ok; ++i) {
            for (int j = i + 1; j < sz && ok; ++j) {
                if (collinear(existing[i], existing[j], Point{x, y})) {
                    ok = false;
                }
            }
        }
        if (ok) return Point{x, y};
    }
}

vector<long long> genB(int M, int type) {
    vector<long long> B(M);
    for (int i = 0; i < M; ++i) {
        if (type == 0) {
            // small values
            B[i] = rnd.next(1, 10);
        } else if (type == 1) {
            // mix of very large and small
            if (rnd.next(0, 1) == 0) B[i] = 1000000000LL;
            else B[i] = rnd.next(1, 5);
        } else if (type == 2) {
            // wide range
            B[i] = rnd.next(1, 1000000000);
        } else {
            // large-only range
            B[i] = rnd.next(400000000, 1000000000);
        }
    }
    return B;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> reds, blues, all;
    vector<long long> B;
    int N = 0, M = 0;

    int scenario = rnd.next(0, 6);

    switch (scenario) {
        case 0: {
            // All blue points strictly inside convex hull of reds (answer = 0 case)
            reds.clear(); blues.clear(); all.clear();
            Point A{-10, -10}, Bp{-10, 10}, C{10, 10}, D{10, -10};
            reds.push_back(A);
            reds.push_back(Bp);
            reds.push_back(C);
            reds.push_back(D);
            all = reds;

            int Mloc = rnd.next(1, 6);
            for (int i = 0; i < Mloc; ++i) {
                // strictly inside rectangle: |x|,|y| <= 9
                Point p = genPoint(-9, 9, all);
                blues.push_back(p);
                all.push_back(p);
            }
            N = (int)reds.size();
            M = Mloc;
            B = genB(M, 0);
            break;
        }
        case 1: {
            // Single red point, several blues around
            reds.clear(); blues.clear(); all.clear();
            int Nloc = 1;
            int Mloc = rnd.next(1, 8);

            Point pr = genPoint(-10, 10, all);
            reds.push_back(pr);
            all.push_back(pr);

            for (int i = 0; i < Mloc; ++i) {
                Point pb = genPoint(-10, 10, all);
                blues.push_back(pb);
                all.push_back(pb);
            }
            N = Nloc;
            M = Mloc;
            B = genB(M, 2);
            break;
        }
        case 2: {
            // Few reds, many blues
            reds.clear(); blues.clear(); all.clear();
            int Nloc = rnd.next(2, 4);
            int Mloc = rnd.next(6, 10);

            for (int i = 0; i < Nloc; ++i) {
                Point pr = genPoint(-10, 10, all);
                reds.push_back(pr);
                all.push_back(pr);
            }
            for (int i = 0; i < Mloc; ++i) {
                Point pb = genPoint(-10, 10, all);
                blues.push_back(pb);
                all.push_back(pb);
            }
            N = Nloc;
            M = Mloc;
            B = genB(M, 1);
            break;
        }
        case 3: {
            // Many reds, few blues
            reds.clear(); blues.clear(); all.clear();
            int Nloc = rnd.next(6, 10);
            int Mloc = rnd.next(1, 5);

            for (int i = 0; i < Nloc; ++i) {
                Point pr = genPoint(-10, 10, all);
                reds.push_back(pr);
                all.push_back(pr);
            }
            for (int i = 0; i < Mloc; ++i) {
                Point pb = genPoint(-10, 10, all);
                blues.push_back(pb);
                all.push_back(pb);
            }
            N = Nloc;
            M = Mloc;
            B = genB(M, 0);
            break;
        }
        case 4: {
            // Balanced random cluster
            reds.clear(); blues.clear(); all.clear();
            int Nloc = rnd.next(3, 7);
            int Mloc = rnd.next(3, 7);

            for (int i = 0; i < Nloc; ++i) {
                Point pr = genPoint(-7, 7, all);
                reds.push_back(pr);
                all.push_back(pr);
            }
            for (int i = 0; i < Mloc; ++i) {
                Point pb = genPoint(-7, 7, all);
                blues.push_back(pb);
                all.push_back(pb);
            }
            N = Nloc;
            M = Mloc;
            int btype = rnd.next(0, 2); // 0,1,2
            B = genB(M, btype);
            break;
        }
        case 5: {
            // Reds and blues in separated clusters (easy to separate by a line)
            reds.clear(); blues.clear(); all.clear();
            int Nloc = rnd.next(2, 5);
            int Mloc = rnd.next(2, 5);

            // Reds in square [-10, -2]^2
            for (int i = 0; i < Nloc; ++i) {
                Point pr = genPoint(-10, -2, all);
                reds.push_back(pr);
                all.push_back(pr);
            }
            // Blues in square [2, 10]^2
            for (int i = 0; i < Mloc; ++i) {
                Point pb = genPoint(2, 10, all);
                blues.push_back(pb);
                all.push_back(pb);
            }
            N = Nloc;
            M = Mloc;
            B = genB(M, 1);
            break;
        }
        case 6: {
            // Extreme coordinates near limits
            reds.clear(); blues.clear(); all.clear();
            int Nloc = rnd.next(2, 4);
            int Mloc = rnd.next(2, 4);

            for (int i = 0; i < Nloc; ++i) {
                Point pr = genPoint(-1000000000LL, 1000000000LL, all);
                reds.push_back(pr);
                all.push_back(pr);
            }
            for (int i = 0; i < Mloc; ++i) {
                Point pb = genPoint(-1000000000LL, 1000000000LL, all);
                blues.push_back(pb);
                all.push_back(pb);
            }
            N = Nloc;
            M = Mloc;
            B = genB(M, 3);
            break;
        }
    }

    println(N, M);
    for (int i = 0; i < N; ++i)
        println(reds[i].x, reds[i].y);
    for (int i = 0; i < M; ++i)
        println(blues[i].x, blues[i].y, B[i]);

    return 0;
}
