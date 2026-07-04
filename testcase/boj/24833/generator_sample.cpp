#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const long long kMinTemp = -1000000000LL;
const long long kMaxTemp = 1000000000LL;

struct Visit {
    long long t;
    long long l;
    long long h;
};

long long clampTemp(long long x) {
    return max(kMinTemp, min(kMaxTemp, x));
}

Visit makeInterval(long long t, long long center, long long radius) {
    center = clampTemp(center);
    long long l = max(kMinTemp, center - radius);
    long long h = min(kMaxTemp, center + radius);
    return {t, l, h};
}

void printCase(long long m, const vector<Visit>& visits) {
    println((int)visits.size(), m);
    for (const Visit& visit : visits) {
        println(visit.t, visit.l, visit.h);
    }
}

vector<Visit> makeReachableCase(long long m, int n) {
    vector<Visit> visits;
    long long t = 0;
    long long current = m;
    for (int i = 0; i < n; ++i) {
        long long dt = rnd.next(0, 8);
        if (i == 0 && dt == 0) {
            dt = 1;
        }
        t += dt;
        long long move = rnd.next(-dt, dt);
        current = clampTemp(current + move);
        long long radius = rnd.next(0, 4);
        visits.push_back(makeInterval(t, current, radius));
    }
    return visits;
}

vector<Visit> makeUnreachableCase(long long m) {
    int n = rnd.next(2, 6);
    vector<Visit> visits = makeReachableCase(m, n);
    int bad = rnd.next((int)visits.size());
    long long previousTime = bad == 0 ? 0 : visits[bad - 1].t;
    long long previousCenter = bad == 0 ? m : (visits[bad - 1].l + visits[bad - 1].h) / 2;
    long long dt = visits[bad].t - previousTime;
    long long gap = dt + rnd.next(1, 5);
    long long target = previousCenter + (rnd.next(0, 1) == 0 ? -gap : gap);
    visits[bad] = makeInterval(visits[bad].t, target, rnd.next(0, 1));
    return visits;
}

vector<Visit> makeBoundaryCase(long long m) {
    (void)m;
    vector<Visit> visits;
    long long t = 1;
    long long edge = rnd.next(0, 1) == 0 ? kMinTemp : kMaxTemp;
    int n = rnd.next(2, 5);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            t += rnd.next(0, 3);
        }
        long long radius = rnd.next(0, 2);
        visits.push_back(makeInterval(t, edge, radius));
        if (rnd.next(0, 1)) {
            edge = -edge;
        }
    }
    return visits;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int q = rnd.next(4, 10);
    println(q);
    for (int tc = 0; tc < q; ++tc) {
        int mode = rnd.next(0, 4);
        long long m;
        if (mode == 4) {
            m = rnd.next(0, 1) == 0 ? kMinTemp : kMaxTemp;
        } else {
            m = rnd.next(-20, 20);
        }

        vector<Visit> visits;
        if (mode == 0) {
            visits = makeReachableCase(m, rnd.next(1, 8));
        } else if (mode == 1) {
            visits = makeUnreachableCase(m);
        } else if (mode == 2) {
            long long t = rnd.next(1, 10);
            long long center = clampTemp(m + rnd.next(-5, 5));
            int n = rnd.next(2, 6);
            for (int i = 0; i < n; ++i) {
                visits.push_back(makeInterval(t, center + rnd.next(-2, 2), rnd.next(0, 3)));
            }
        } else if (mode == 3) {
            visits = {
                makeInterval(1, m, 0),
                makeInterval(1000000000LL, rnd.next(-20, 20), rnd.next(0, 10))
            };
        } else {
            visits = makeBoundaryCase(m);
        }

        printCase(m, visits);
    }

    return 0;
}
