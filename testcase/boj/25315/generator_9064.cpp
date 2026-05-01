#include "testlib.h"
using namespace std;

struct P {
    long long x, y;
};

long long cross(const P &a, const P &b, const P &c) {
    // (b - a) x (c - a)
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool areCollinear(const P &a, const P &b, const P &c) {
    return cross(a, b, c) == 0;
}

// Generate 'cnt' points with coordinates in [-coordLim, coordLim],
// all distinct and with no three collinear.
void genRandomGeneralPositionPoints(int cnt, int coordLim, vector<P> &pts) {
    pts.clear();
    int attempts = 0;
    while ((int)pts.size() < cnt) {
        ++attempts;
        if (attempts > 1000000) {
            // In the very unlikely event of too many failures, enlarge range.
            coordLim *= 2;
            attempts = 0;
        }

        P p;
        p.x = rnd.next(-coordLim, coordLim);
        p.y = rnd.next(-coordLim, coordLim);

        bool ok = true;
        // distinct
        for (int i = 0; i < (int)pts.size(); ++i) {
            if (pts[i].x == p.x && pts[i].y == p.y) {
                ok = false;
                break;
            }
        }
        if (!ok) continue;

        // no three collinear
        for (int i = 0; i < (int)pts.size() && ok; ++i) {
            for (int j = i + 1; j < (int)pts.size(); ++j) {
                if (areCollinear(pts[i], pts[j], p)) {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) pts.push_back(p);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4); // 0..4
    int N;
    vector<P> pts;
    vector<pair<int,int>> seg; // segments as pairs of point indices

    if (mode == 0) {
        // Very small random case
        N = rnd.next(1, 3);
        genRandomGeneralPositionPoints(2 * N, 100, pts);

        vector<int> idx(2 * N);
        for (int i = 0; i < 2 * N; ++i) idx[i] = i;
        shuffle(idx.begin(), idx.end());

        seg.resize(N);
        for (int i = 0; i < N; ++i) {
            seg[i] = make_pair(idx[2 * i], idx[2 * i + 1]);
        }
    } else if (mode == 1) {
        // Small random, arbitrary intersections
        N = rnd.next(3, 8);
        genRandomGeneralPositionPoints(2 * N, 200, pts);

        vector<int> idx(2 * N);
        for (int i = 0; i < 2 * N; ++i) idx[i] = i;
        shuffle(idx.begin(), idx.end());

        seg.resize(N);
        for (int i = 0; i < N; ++i) {
            seg[i] = make_pair(idx[2 * i], idx[2 * i + 1]);
        }
    } else if (mode == 2) {
        // Many intersections: bipartite matching between left and right halves by x-order
        N = rnd.next(5, 12);
        genRandomGeneralPositionPoints(2 * N, 300, pts);

        vector<int> ord(2 * N);
        for (int i = 0; i < 2 * N; ++i) ord[i] = i;
        sort(ord.begin(), ord.end(), [&](int a, int b) {
            if (pts[a].x != pts[b].x) return pts[a].x < pts[b].x;
            return pts[a].y < pts[b].y;
        });

        vector<int> left(N), right(N);
        for (int i = 0; i < N; ++i) {
            left[i] = ord[i];
            right[i] = ord[i + N];
        }

        vector<int> perm(N);
        for (int i = 0; i < N; ++i) perm[i] = i;
        int sub = rnd.next(0, 2); // 0: identity, 1: reverse, 2: random
        if (sub == 1) {
            reverse(perm.begin(), perm.end());
        } else if (sub == 2) {
            shuffle(perm.begin(), perm.end());
        }

        seg.resize(N);
        for (int i = 0; i < N; ++i) {
            seg[i] = make_pair(left[i], right[perm[i]]);
        }
    } else if (mode == 3) {
        // Almost non-intersecting: connect nearby points in x-order
        N = rnd.next(5, 12);
        genRandomGeneralPositionPoints(2 * N, 400, pts);

        vector<int> ord(2 * N);
        for (int i = 0; i < 2 * N; ++i) ord[i] = i;
        sort(ord.begin(), ord.end(), [&](int a, int b) {
            if (pts[a].x != pts[b].x) return pts[a].x < pts[b].x;
            return pts[a].y < pts[b].y;
        });

        seg.resize(N);
        for (int i = 0; i < N; ++i) {
            seg[i] = make_pair(ord[2 * i], ord[2 * i + 1]);
        }
    } else {
        // Structured points on a parabola y = x^2: no three collinear
        N = rnd.next(3, 10);
        int M = 2 * N;
        pts.resize(M);
        for (int i = 0; i < M; ++i) {
            long long x = i + 1;
            pts[i].x = x;
            pts[i].y = x * x;
        }

        seg.resize(N);
        int sub = rnd.next(0, 1); // 0: random matching, 1: crossing left/right
        if (sub == 0) {
            vector<int> idx(M);
            for (int i = 0; i < M; ++i) idx[i] = i;
            shuffle(idx.begin(), idx.end());
            for (int i = 0; i < N; ++i) {
                seg[i] = make_pair(idx[2 * i], idx[2 * i + 1]);
            }
        } else {
            vector<int> left(N), right(N);
            for (int i = 0; i < N; ++i) {
                left[i] = i;
                right[i] = i + N;
            }

            vector<int> perm(N);
            for (int i = 0; i < N; ++i) perm[i] = i;
            int sub2 = rnd.next(0, 2); // 0: identity, 1: reverse, 2: random
            if (sub2 == 1) {
                reverse(perm.begin(), perm.end());
            } else if (sub2 == 2) {
                shuffle(perm.begin(), perm.end());
            }

            for (int i = 0; i < N; ++i) {
                seg[i] = make_pair(left[i], right[perm[i]]);
            }
        }
    }

    // Assign weights with varied patterns
    vector<long long> w(N);
    int wMode = rnd.next(0, 3);
    if (wMode == 0) {
        // All weights = 1
        for (int i = 0; i < N; ++i) w[i] = 1;
    } else if (wMode == 1) {
        // Small random weights
        for (int i = 0; i < N; ++i) w[i] = rnd.next(1, 10);
    } else if (wMode == 2) {
        // Wide-range random weights
        for (int i = 0; i < N; ++i) w[i] = rnd.next(1, (int)1e9);
    } else {
        // One very heavy slash, others light
        int heavy = rnd.next(0, N - 1);
        for (int i = 0; i < N; ++i) {
            if (i == heavy) w[i] = (long long)1e9;
            else w[i] = rnd.next(1, 5);
        }
    }

    // Shuffle order of slashes to avoid structured indices
    vector<int> order(N);
    for (int i = 0; i < N; ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    println(N);
    for (int id : order) {
        P a = pts[seg[id].first];
        P b = pts[seg[id].second];
        println(a.x, a.y, b.x, b.y, w[id]);
    }

    return 0;
}
