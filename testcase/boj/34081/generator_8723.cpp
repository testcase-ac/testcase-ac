#include "testlib.h"
using namespace std;

struct Pirate {
    long long x, y, c;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 6);

    vector<Pirate> pirates;
    long long L = 0;
    int N = 0;

    if (scenario == 0) {
        // Single pirate, simple edge
        N = 1;
        L = rnd.next(1, 20);
        bool inside = rnd.next(0, 1);
        long long r;
        if (inside) r = rnd.next(1, (int)L);
        else        r = rnd.next((int)L + 1, (int)L + 10);
        Pirate p;
        p.x = r;
        p.y = 0;
        p.c = rnd.next(1LL, 1000000000LL);
        pirates.push_back(p);
    } else if (scenario == 1) {
        // Mixed inside/outside, moderate L
        N = rnd.next(3, 10);
        L = rnd.next(2, 30);
        set<pair<long long,long long>> used;
        for (int i = 0; i < N; ++i) {
            bool inside = rnd.next(0, 99) < 60;
            Pirate p;
            while (true) {
                long long x = rnd.next(-(int)L, (int)L);
                long long y = rnd.next(-(int)L, (int)L);
                if (x == 0 && y == 0) continue;
                long long r2 = x * x + y * y;
                if (inside && r2 <= L * L && !used.count({x, y})) {
                    p.x = x; p.y = y; break;
                }
                if (!inside) {
                    x = rnd.next(-(int)(2 * L), (int)(2 * L));
                    y = rnd.next(-(int)(2 * L), (int)(2 * L));
                    if (x == 0 && y == 0) continue;
                    r2 = x * x + y * y;
                    if (r2 > L * L && !used.count({x, y})) {
                        p.x = x; p.y = y; break;
                    }
                }
            }
            used.insert({p.x, p.y});
            p.c = rnd.next(1LL, 1000000000LL);
            pirates.push_back(p);
        }
    } else if (scenario == 2) {
        // Many pirates very close to boundary, all with deadline 0
        L = rnd.next(5, 20);
        vector<Pirate> cand;
        for (int x = -L; x <= L; ++x) {
            for (int y = -L; y <= L; ++y) {
                if (x == 0 && y == 0) continue;
                long long r2 = 1LL * x * x + 1LL * y * y;
                if (r2 <= 1LL * L * L && r2 > 1LL * (L - 1) * (L - 1)) {
                    Pirate p;
                    p.x = x; p.y = y;
                    p.c = rnd.next(1LL, 1000000000LL);
                    cand.push_back(p);
                }
            }
        }
        shuffle(cand.begin(), cand.end());
        int maxN = min(15, (int)cand.size());
        int minN = min(7, maxN);
        if (minN < 2) minN = 2;
        N = rnd.next(minN, maxN);
        pirates.assign(cand.begin(), cand.begin() + N);
    } else if (scenario == 3) {
        // Mix of deadlines 0,1,2 with over-subscription
        L = rnd.next(7, 20);
        vector<Pirate> d0, d1, d2;
        long long L2 = 1LL * L * L;
        long long L1_2 = 1LL * (L - 1) * (L - 1);
        long long L2_2 = 1LL * (L - 2) * (L - 2);
        long long L3_2 = 1LL * (L - 3) * (L - 3);
        for (int x = -L; x <= L; ++x) {
            for (int y = -L; y <= L; ++y) {
                if (x == 0 && y == 0) continue;
                long long r2 = 1LL * x * x + 1LL * y * y;
                if (r2 <= L2 && r2 > L1_2) {
                    Pirate p {x, y, rnd.next(1LL, 1000000000LL)};
                    d0.push_back(p);
                } else if (r2 <= L1_2 && r2 > L2_2) {
                    Pirate p {x, y, rnd.next(1LL, 1000000000LL)};
                    d1.push_back(p);
                } else if (r2 <= L2_2 && r2 > L3_2) {
                    Pirate p {x, y, rnd.next(1LL, 1000000000LL)};
                    d2.push_back(p);
                }
            }
        }
        if (d0.size() >= 2 && d1.size() >= 1 && d2.size() >= 1) {
            shuffle(d0.begin(), d0.end());
            shuffle(d1.begin(), d1.end());
            shuffle(d2.begin(), d2.end());
            int cnt0 = rnd.next(2, min(6, (int)d0.size()));
            int cnt1 = rnd.next(1, min(5, (int)d1.size()));
            int cnt2 = rnd.next(1, min(4, (int)d2.size()));
            while (cnt0 + cnt1 + cnt2 > 15) {
                if (cnt2 > 1) --cnt2;
                else if (cnt1 > 1) --cnt1;
                else if (cnt0 > 2) --cnt0;
                else break;
            }
            N = cnt0 + cnt1 + cnt2;
            for (int i = 0; i < cnt0; ++i) pirates.push_back(d0[i]);
            for (int i = 0; i < cnt1; ++i) pirates.push_back(d1[i]);
            for (int i = 0; i < cnt2; ++i) pirates.push_back(d2[i]);
        } else {
            // Fallback to scenario 2 style if rings are too thin unexpectedly
            L = rnd.next(5, 20);
            vector<Pirate> cand;
            for (int x = -L; x <= L; ++x) {
                for (int y = -L; y <= L; ++y) {
                    if (x == 0 && y == 0) continue;
                    long long r2 = 1LL * x * x + 1LL * y * y;
                    if (r2 <= 1LL * L * L && r2 > 1LL * (L - 1) * (L - 1)) {
                        Pirate p {x, y, rnd.next(1LL, 1000000000LL)};
                        cand.push_back(p);
                    }
                }
            }
            shuffle(cand.begin(), cand.end());
            int maxN = min(15, (int)cand.size());
            int minN = min(7, maxN);
            if (minN < 2) minN = 2;
            N = rnd.next(minN, maxN);
            pirates.assign(cand.begin(), cand.begin() + N);
        }
    } else if (scenario == 4) {
        // Large coordinates and L near 1e9
        L = rnd.next(500000000, 1000000000);
        N = rnd.next(3, 8);
        // Some inside, some outside
        int insideCnt = min(rnd.next(1, 3), N);
        set<pair<long long,long long>> used;
        // Inside near boundary on axis
        for (int i = 0; i < insideCnt; ++i) {
            long long d = i + 1;
            long long x = L - d;
            long long y = 0;
            if (x == 0 && y == 0) x = 1; // just in case
            if (used.count({x, y})) continue;
            used.insert({x, y});
            Pirate p {x, y, rnd.next(1LL, 1000000000LL)};
            pirates.push_back(p);
        }
        // Remaining outside
        for (int i = insideCnt; i < N; ++i) {
            long long d = i - insideCnt + 1;
            long long x, y;
            if (L + d <= 1000000000LL) {
                x = L + d;
                y = 0;
            } else {
                x = L;
                y = d;
            }
            if (x == 0 && y == 0) x = 1;
            if (used.count({x, y})) { --i; continue; }
            used.insert({x, y});
            Pirate p {x, y, rnd.next(1LL, 1000000000LL)};
            pirates.push_back(p);
        }
    } else if (scenario == 5) {
        // Collinear pirates along a ray
        N = rnd.next(5, 10);
        L = rnd.next(5, 30);
        int dx, dy;
        if (rnd.next(0, 1) == 0) {
            dx = 1; dy = 0; // x-axis
        } else {
            dx = 1; dy = 1; // diagonal
        }
        set<long long> usedK;
        for (int i = 0; i < N; ++i) {
            bool firstHalf = (i < N / 2);
            while (true) {
                long long lo = firstHalf ? 1 : (L + 1);
                long long hi = firstHalf ? L : (L + 5);
                long long k = rnd.next((int)lo, (int)hi);
                if (usedK.insert(k).second) {
                    long long x = k * dx;
                    long long y = k * dy;
                    Pirate p {x, y, rnd.next(1LL, 1000000000LL)};
                    pirates.push_back(p);
                    break;
                }
            }
        }
    } else if (scenario == 6) {
        // Large total bounty to require 64-bit sums
        L = rnd.next(10, 40);
        N = rnd.next(8, 15);
        set<pair<long long,long long>> used;
        for (int i = 0; i < N; ++i) {
            bool inside = rnd.next(0, 99) < 70;
            Pirate p;
            while (true) {
                long long x = rnd.next(-(int)(2 * L), (int)(2 * L));
                long long y = rnd.next(-(int)(2 * L), (int)(2 * L));
                if (x == 0 && y == 0) continue;
                long long r2 = x * x + y * y;
                if (inside && r2 > L * L) continue;
                if (!inside && r2 <= L * L) continue;
                if (used.count({x, y})) continue;
                p.x = x; p.y = y;
                break;
            }
            used.insert({p.x, p.y});
            p.c = rnd.next(300000000LL, 1000000000LL);
            pirates.push_back(p);
        }
    }

    // Final shuffle and output
    shuffle(pirates.begin(), pirates.end());
    N = (int)pirates.size();

    println(N, L);
    for (auto &p : pirates) {
        println(p.x, p.y, p.c);
    }

    return 0;
}
