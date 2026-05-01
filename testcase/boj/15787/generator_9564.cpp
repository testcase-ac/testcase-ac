#include "testlib.h"
using namespace std;

struct Op {
    int type;
    int i;
    int x;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 4); // 0..4
    int N;
    vector<Op> ops;
    const unsigned FULL_MASK = (1u << 20) - 1;

    if (scenario == 0) {
        // Scenario 0: tiny random, ensure at least one shift
        N = rnd.next(1, 3);
        int Mtarget = rnd.next(1, 6);
        ops.reserve(Mtarget);
        bool hasShift = false;
        for (int k = 0; k < Mtarget; ++k) {
            int r = rnd.next(1, 100);
            int type;
            if (r <= 40) type = 1;
            else if (r <= 65) type = 2;
            else if (r <= 85) type = 3;
            else type = 4;

            int ti = rnd.next(1, N);
            int x = 0;
            if (type == 1 || type == 2) x = rnd.next(1, 20);
            if (type == 3 || type == 4) hasShift = true;

            ops.push_back({type, ti, x});
        }
        if (!hasShift && !ops.empty()) {
            ops.back().type = 3;
        }
    } else if (scenario == 1) {
        // Scenario 1: duplicates via only set/clear (1,2), no shifts
        N = rnd.next(2, 7);
        vector<unsigned int> desired(N, 0);

        // Base pattern B with 1..4 seats occupied
        int k = rnd.next(1, 4);
        vector<int> seatPool(20);
        for (int i = 0; i < 20; ++i) seatPool[i] = i + 1;
        shuffle(seatPool.begin(), seatPool.end());
        unsigned int B = 0;
        for (int i = 0; i < k; ++i) {
            int s = seatPool[i];
            B |= (1u << (s - 1));
        }

        int a = rnd.next(0, N - 1);
        int b = a;
        while (b == a) b = rnd.next(0, N - 1);
        desired[a] = desired[b] = B;

        auto genPatternNotB = [&](unsigned int Bmask) {
            while (true) {
                int kk = rnd.next(0, 4);
                vector<int> pool(20);
                for (int i = 0; i < 20; ++i) pool[i] = i + 1;
                shuffle(pool.begin(), pool.end());
                unsigned int m = 0;
                for (int i = 0; i < kk; ++i) {
                    int s = pool[i];
                    m |= (1u << (s - 1));
                }
                if (m != Bmask) return m;
            }
        };

        for (int i = 0; i < N; ++i) {
            if (i == a || i == b) continue;
            if (rnd.next(0, 2) == 0) {
                desired[i] = B;
            } else {
                desired[i] = genPatternNotB(B);
            }
        }

        // Build base operations to realize desired patterns
        for (int i = 0; i < N; ++i) {
            for (int bit = 0; bit < 20; ++bit) {
                if (desired[i] & (1u << bit)) {
                    ops.push_back({1, i + 1, bit + 1});
                }
            }
        }

        // Add a few guaranteed no-ops
        int extra = rnd.next(0, 3);
        for (int e = 0; e < extra; ++e) {
            int ti = rnd.next(0, N - 1);
            int seat = rnd.next(1, 20);
            bool bit = (desired[ti] >> (seat - 1)) & 1u;
            int type = bit ? 1 : 2; // set where final is 1, clear where final is 0
            ops.push_back({type, ti + 1, seat});
        }

        // Shuffle all operations; still final patterns are as desired
        shuffle(ops.begin(), ops.end());
    } else if (scenario == 2) {
        // Scenario 2: heavy shifts
        N = rnd.next(2, 6);
        int Mtarget = rnd.next(10, 25);
        ops.reserve(Mtarget);
        vector<unsigned int> mask(N, 0);
        bool hasPut = false;

        for (int k = 0; k < Mtarget; ++k) {
            int r = rnd.next(1, 100);
            int type;
            if (r <= 20) type = 1;
            else if (r <= 40) type = 2;
            else if (r <= 75) type = 3;
            else type = 4;

            int ti = rnd.next(1, N);
            int x = 0;
            if (type == 1 || type == 2) x = rnd.next(1, 20);
            if (type == 1) hasPut = true;

            // Update mask (not essential for output, but keeps it realistic)
            unsigned int &msk = mask[ti - 1];
            if (type == 1) {
                msk |= (1u << (x - 1));
            } else if (type == 2) {
                msk &= ~(1u << (x - 1));
            } else if (type == 3) {
                msk = (msk << 1) & FULL_MASK;
            } else if (type == 4) {
                msk >>= 1;
            }

            ops.push_back({type, ti, x});
        }

        if (!hasPut && !ops.empty()) {
            int ti = rnd.next(1, N);
            int x = rnd.next(1, 20);
            ops.back().type = 1;
            ops.back().i = ti;
            ops.back().x = x;
        }
    } else if (scenario == 3) {
        // Scenario 3: hand-crafted edge/No-op cases
        N = rnd.next(1, 3);

        // Train 1 edge cases
        ops.push_back({1, 1, 1});   // seat 1
        ops.push_back({1, 1, 20});  // seat 20
        ops.push_back({3, 1, 0});   // shift back: 1->2, 20 leaves
        ops.push_back({4, 1, 0});   // shift forward: 2->1
        ops.push_back({4, 1, 0});   // shift forward: 1 leaves
        ops.push_back({2, 1, 1});   // no-op (seat 1 empty)
        ops.push_back({2, 1, 20});  // no-op (seat 20 empty)
        ops.push_back({1, 1, 2});   // put at seat 2
        ops.push_back({4, 1, 0});   // shift forward: 2->1

        if (N >= 2) {
            // Train 2: drop from seat 20 by shifting back
            ops.push_back({1, 2, 20});
            ops.push_back({3, 2, 0});
        }
        if (N >= 3) {
            // Train 3: some mid seats with shifts
            ops.push_back({1, 3, 10});
            ops.push_back({3, 3, 0});
            ops.push_back({4, 3, 0});
        }
    } else {
        // Scenario 4: medium mixed, some guaranteed duplicate patterns
        N = rnd.next(6, 15);
        int Mmax = rnd.next(20, 40);
        vector<unsigned int> mask(N, 0);
        ops.reserve(Mmax);

        // Choose group of trains that will share identical sequence
        vector<int> perm(N);
        for (int i = 0; i < N; ++i) perm[i] = i + 1;
        shuffle(perm.begin(), perm.end());
        int c = rnd.next(2, min(3, N)); // 2 or 3 identical trains
        vector<int> group(c);
        for (int i = 0; i < c; ++i) group[i] = perm[i];

        int remainForOthers = Mmax - 5;
        int Lmax = min(7, remainForOthers / c);
        if (Lmax < 2) Lmax = 2;
        int L = rnd.next(2, Lmax);

        // Build prototype operations
        vector<Op> protoOps;
        protoOps.reserve(L);
        bool hasPut = false;
        for (int k = 0; k < L; ++k) {
            int r = rnd.next(1, 100);
            int type;
            if (r <= 30) type = 1;
            else if (r <= 55) type = 2;
            else if (r <= 80) type = 3;
            else type = 4;
            int x = 0;
            if (type == 1 || type == 2) x = rnd.next(1, 20);
            if (type == 1) hasPut = true;
            protoOps.push_back({type, 0, x});
        }
        if (!hasPut && !protoOps.empty()) {
            protoOps[0].type = 1;
            protoOps[0].x = rnd.next(1, 20);
        }

        // Apply prototype to each train in the group
        for (int t : group) {
            for (const auto &p : protoOps) {
                Op op{p.type, t, p.x};
                unsigned int &msk = mask[t - 1];
                if (op.type == 1) {
                    msk |= (1u << (op.x - 1));
                } else if (op.type == 2) {
                    msk &= ~(1u << (op.x - 1));
                } else if (op.type == 3) {
                    msk = (msk << 1) & FULL_MASK;
                } else if (op.type == 4) {
                    msk >>= 1;
                }
                ops.push_back(op);
            }
        }

        // Mark group trains
        vector<bool> inGroup(N + 1, false);
        for (int t : group) inGroup[t] = true;
        vector<int> others;
        for (int i = 1; i <= N; ++i)
            if (!inGroup[i]) others.push_back(i);

        int spare = Mmax - (int)ops.size();
        for (int s = 0; s < spare && !others.empty(); ++s) {
            int t = rnd.any(others);
            int r = rnd.next(1, 100);
            int type;
            if (r <= 35) type = 1;
            else if (r <= 60) type = 2;
            else if (r <= 80) type = 3;
            else type = 4;

            int x = 0;
            if (type == 1 || type == 2) x = rnd.next(1, 20);
            unsigned int &msk = mask[t - 1];
            if (type == 1) {
                msk |= (1u << (x - 1));
            } else if (type == 2) {
                msk &= ~(1u << (x - 1));
            } else if (type == 3) {
                msk = (msk << 1) & FULL_MASK;
            } else if (type == 4) {
                msk >>= 1;
            }
            ops.push_back({type, t, x});
        }
    }

    int M = (int)ops.size();
    println(N, M);
    for (const auto &op : ops) {
        if (op.type == 1 || op.type == 2)
            println(op.type, op.i, op.x);
        else
            println(op.type, op.i);
    }

    return 0;
}
