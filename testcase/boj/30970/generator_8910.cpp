#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 6);

    vector<pair<int,int>> items;
    set<pair<int,int>> used;

    auto add = [&](int q, int p) {
        // assume (q,p) not used in hand-crafted parts
        items.push_back({q, p});
        used.insert({q, p});
    };

    auto addRandomUnique = [&](int qlo, int qhi, int plo, int phi) {
        while (true) {
            int q = rnd.next(qlo, qhi);
            int p = rnd.next(plo, phi);
            if (!used.count({q, p})) {
                add(q, p);
                break;
            }
        }
    };

    switch (scenario) {
        case 0: { // Very small N, possibly with a tie
            int N = 2;
            int tieType = rnd.next(0, 2); // 0: quality tie, 1: price tie, 2: no tie
            if (tieType == 0) {
                int Q = rnd.next(1, 20);
                int P1 = rnd.next(1, 20);
                int P2 = rnd.next(1, 20);
                if (P2 == P1) P2 = (P1 % 20) + 1;
                add(Q, P1);
                add(Q, P2);
            } else if (tieType == 1) {
                int P = rnd.next(1, 20);
                int Q1 = rnd.next(1, 20);
                int Q2 = rnd.next(1, 20);
                if (Q2 == Q1) Q2 = (Q1 % 20) + 1;
                add(Q1, P);
                add(Q2, P);
            } else {
                while ((int)items.size() < N) {
                    addRandomUnique(1, 20, 1, 20);
                }
            }
            break;
        }

        case 1: { // Many equal qualities (tie on quality)
            int N = rnd.next(4, 8);
            int commonQ = rnd.next(1, 20);
            int minCommon = 2;
            int maxCommon = N - 1;
            if (maxCommon < minCommon) maxCommon = minCommon;
            int cntCommon = rnd.next(minCommon, maxCommon);
            int baseP = 1;
            for (int i = 0; i < cntCommon; ++i) {
                add(commonQ, baseP + i); // P distinct, Q equal
            }
            for (int i = cntCommon; i < N; ++i) {
                while (true) {
                    int q = rnd.next(1, 20);
                    if (q == commonQ) continue;
                    int p = rnd.next(1, 30);
                    if (!used.count({q, p})) {
                        add(q, p);
                        break;
                    }
                }
            }
            break;
        }

        case 2: { // Many equal prices (tie on price)
            int N = rnd.next(4, 8);
            int commonP = rnd.next(1, 20);
            int minCommon = 2;
            int maxCommon = N - 1;
            if (maxCommon < minCommon) maxCommon = minCommon;
            int cntCommon = rnd.next(minCommon, maxCommon);
            int baseQ = 1;
            for (int i = 0; i < cntCommon; ++i) {
                add(baseQ + i, commonP); // Q distinct, P equal
            }
            for (int i = cntCommon; i < N; ++i) {
                while (true) {
                    int p = rnd.next(1, 30);
                    if (p == commonP) continue;
                    int q = rnd.next(1, 30);
                    if (!used.count({q, p})) {
                        add(q, p);
                        break;
                    }
                }
            }
            break;
        }

        case 3: { // 2x2 grid: ties on both quality and price
            int q1 = rnd.next(1, 20);
            int q2;
            do { q2 = rnd.next(1, 20); } while (q2 == q1);
            int p1 = rnd.next(1, 20);
            int p2;
            do { p2 = rnd.next(1, 20); } while (p2 == p1);

            add(q1, p1);
            add(q1, p2);
            add(q2, p1);
            add(q2, p2);

            int extra = rnd.next(0, 4);
            for (int i = 0; i < extra; ++i) {
                while (true) {
                    bool tieQ = rnd.next(0, 1); // choose to tie on Q or P
                    int q, p;
                    if (tieQ) {
                        q = (rnd.next(0, 1) == 0 ? q1 : q2);
                        p = rnd.next(1, 30);
                    } else {
                        p = (rnd.next(0, 1) == 0 ? p1 : p2);
                        q = rnd.next(1, 30);
                    }
                    if (!used.count({q, p})) {
                        add(q, p);
                        break;
                    }
                }
            }
            break;
        }

        case 4: { // Hand-crafted strong tie-breaking test
            // Quality tie: (10,5) vs (10,7)  -> min price should be chosen first
            // Price tie: (5,1) vs (7,1)     -> max quality should be chosen first
            add(10, 5); // A
            add(10, 7); // B
            add(5, 1);  // C
            add(7, 1);  // D
            add(9, 3);  // E
            add(2, 9);  // F
            break;
        }

        case 5: { // Edge values and extremes
            int N = rnd.next(5, 8);
            add(10000, 1);
            add(1, 10000);
            add(10000, 10000);
            add(1, 1);
            while ((int)items.size() < N) {
                int qType = rnd.next(0, 2);
                int pType = rnd.next(0, 2);
                int q, p;
                if (qType == 0) q = 1;
                else if (qType == 1) q = 10000;
                else q = rnd.next(2, 9999);
                if (pType == 0) p = 1;
                else if (pType == 1) p = 10000;
                else p = rnd.next(2, 9999);
                if (!used.count({q, p})) add(q, p);
            }
            break;
        }

        case 6: { // Medium N with guaranteed ties in both Q and P
            int N = rnd.next(10, 20);
            int q0 = rnd.next(1, 50);
            int p0 = rnd.next(1, 50);
            add(q0, p0);

            int p1;
            do { p1 = rnd.next(1, 50); } while (p1 == p0);
            add(q0, p1); // quality tie with first

            int q2;
            do { q2 = rnd.next(1, 50); } while (q2 == q0);
            int p2 = rnd.next(1, 50);
            while (used.count({q2, p2})) {
                p2 = rnd.next(1, 50);
            }
            add(q2, p2);

            int q3;
            while (true) {
                q3 = rnd.next(1, 50);
                if (q3 != q0 && q3 != q2 && !used.count({q3, p2})) break;
            }
            add(q3, p2); // price tie with third

            while ((int)items.size() < N) {
                addRandomUnique(1, 50, 1, 50);
            }
            break;
        }
    }

    shuffle(items.begin(), items.end());

    println((int)items.size());
    for (auto &it : items)
        println(it.first, it.second);

    return 0;
}
