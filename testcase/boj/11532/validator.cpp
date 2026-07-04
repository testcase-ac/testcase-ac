#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;

namespace {

constexpr long double kMinRobustGap = 0.001L;
constexpr long double kMaxEventTime = 1000000000.0L;
constexpr long double kEps = 1e-10L;

struct Droplet {
    long double x;
    long double y;
    long double vx;
    long double vy;
    long double r;
};

long double sqr(long double x) {
    return x * x;
}

long double distanceBetween(const Droplet& a, const Droplet& b) {
    return sqrtl(sqr(a.x - b.x) + sqr(a.y - b.y));
}

long double robustGap(const Droplet& a, const Droplet& b) {
    return distanceBetween(a, b) - (a.r + b.r);
}

bool collisionTime(const Droplet& a, const Droplet& b, long double& t) {
    long double dx = a.x - b.x;
    long double dy = a.y - b.y;
    long double dvx = a.vx - b.vx;
    long double dvy = a.vy - b.vy;
    long double radius = a.r + b.r;

    long double aa = sqr(dvx) + sqr(dvy);
    long double bb = 2.0L * (dx * dvx + dy * dvy);
    long double cc = sqr(dx) + sqr(dy) - sqr(radius);

    if (aa <= kEps) {
        return false;
    }

    long double discriminant = bb * bb - 4.0L * aa * cc;
    if (discriminant < 0.0L) {
        return false;
    }

    long double root = sqrtl(max(0.0L, discriminant));
    long double first = (-bb - root) / (2.0L * aa);
    long double second = (-bb + root) / (2.0L * aa);

    if (first > kEps) {
        t = first;
        return true;
    }
    if (second > kEps) {
        t = second;
        return true;
    }
    return false;
}

void advance(vector<Droplet>& droplets, long double dt) {
    for (Droplet& d : droplets) {
        d.x += d.vx * dt;
        d.y += d.vy * dt;
    }
}

Droplet mergeDroplets(const Droplet& a, const Droplet& b) {
    long double wa = sqr(a.r);
    long double wb = sqr(b.r);
    long double total = wa + wb;

    return {
        (wa * a.x + wb * b.x) / total,
        (wa * a.y + wb * b.y) / total,
        (wa * a.vx + wb * b.vx) / total,
        (wa * a.vy + wb * b.vy) / total,
        sqrtl(total),
    };
}

void ensureSeparated(const vector<Droplet>& droplets, const char* stage,
                     long double minGap) {
    for (int i = 0; i < int(droplets.size()); ++i) {
        for (int j = i + 1; j < int(droplets.size()); ++j) {
            ensuref(robustGap(droplets[i], droplets[j]) > minGap - kEps,
                    "%s droplets %d and %d are too close",
                    stage, i + 1, j + 1);
        }
    }
}

void ensurePairRobustness(const vector<Droplet>& droplets) {
    for (int i = 0; i < int(droplets.size()); ++i) {
        for (int j = i + 1; j < int(droplets.size()); ++j) {
            const Droplet& a = droplets[i];
            const Droplet& b = droplets[j];
            long double dx = a.x - b.x;
            long double dy = a.y - b.y;
            long double dvx = a.vx - b.vx;
            long double dvy = a.vy - b.vy;
            long double vv = sqr(dvx) + sqr(dvy);
            long double closest = distanceBetween(a, b);

            if (vv > kEps) {
                long double t = -(dx * dvx + dy * dvy) / vv;
                if (t > 0.0L) {
                    long double cx = dx + dvx * t;
                    long double cy = dy + dvy * t;
                    closest = sqrtl(sqr(cx) + sqr(cy));
                }
            }

            long double gap = fabsl(closest - (a.r + b.r));
            ensuref(gap > kMinRobustGap - kEps,
                    "collision decision for droplets %d and %d is not robust",
                    i + 1, j + 1);
        }
    }
}

void validateSimulationGuarantees(vector<Droplet> droplets) {
    ensureSeparated(droplets, "initial", 0.0L);

    long double currentTime = 0.0L;
    long double previousEventTime = -numeric_limits<long double>::infinity();

    while (true) {
        ensurePairRobustness(droplets);

        long double bestTime = numeric_limits<long double>::infinity();
        int bestI = -1;
        int bestJ = -1;
        int eventCountAtBest = 0;

        for (int i = 0; i < int(droplets.size()); ++i) {
            for (int j = i + 1; j < int(droplets.size()); ++j) {
                long double t = 0.0L;
                if (!collisionTime(droplets[i], droplets[j], t)) {
                    continue;
                }
                if (t < bestTime - kEps) {
                    bestTime = t;
                    bestI = i;
                    bestJ = j;
                    eventCountAtBest = 1;
                } else if (fabsl(t - bestTime) <= kMinRobustGap - kEps) {
                    ++eventCountAtBest;
                }
            }
        }

        if (bestI == -1) {
            break;
        }

        long double nextEventTime = currentTime + bestTime;
        ensuref(nextEventTime <= kMaxEventTime + kEps,
                "agglomeration occurs after time 1e9");
        ensuref(nextEventTime - previousEventTime >= kMinRobustGap - kEps,
                "agglomerations are not separated by at least 0.001");
        ensuref(eventCountAtBest == 1,
                "multiple pairs collide within 0.001 of the same time");

        advance(droplets, bestTime);
        Droplet merged = mergeDroplets(droplets[bestI], droplets[bestJ]);

        vector<Droplet> next;
        next.reserve(droplets.size() - 1);
        for (int i = 0; i < int(droplets.size()); ++i) {
            if (i != bestI && i != bestJ) {
                next.push_back(droplets[i]);
            }
        }
        next.push_back(merged);
        droplets = next;

        ensureSeparated(droplets, "post-agglomeration", kMinRobustGap);
        previousEventTime = nextEventTime;
        currentTime = nextEventTime;
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "n");
    inf.readEoln();

    vector<Droplet> droplets;
    droplets.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-10000, 10000, "x");
        inf.readSpace();
        int y = inf.readInt(-10000, 10000, "y");
        inf.readSpace();
        int vx = inf.readInt(-10000, 10000, "vx");
        inf.readSpace();
        int vy = inf.readInt(-10000, 10000, "vy");
        inf.readSpace();
        int r = inf.readInt(1, 100, "r");
        inf.readEoln();

        droplets.push_back({(long double)x, (long double)y,
                            (long double)vx, (long double)vy,
                            (long double)r});
    }

    validateSimulationGuarantees(droplets);

    inf.readEof();
}
