#include "testlib.h"
using namespace std;

struct Rec {
    string name;
    int W, D;
    int P; // required money
    int M; // owned money
};

pair<int,int> fromAbs(int absDay) {
    int W = absDay / 7 + 1;
    int D = absDay % 7;
    return {W, D};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Rec> recs;

    int scenario = rnd.next(0, 6); // 7 scenarios: 0..6

    if (scenario == 0) {
        // Scenario 0: N = 0 edge case
        // recs stays empty
    } else if (scenario == 1) {
        // Scenario 1: Single senior, maybe enough / not enough
        Rec r;
        r.name = "A";
        int absDay = rnd.next(0, 69);
        auto wd = fromAbs(absDay);
        r.W = wd.first;
        r.D = wd.second;
        bool enough = rnd.next(0, 1);
        if (enough) {
            r.P = rnd.next(0, 100000);
            r.M = rnd.next(r.P, 100000);
        } else {
            r.P = rnd.next(1, 100000);
            r.M = rnd.next(0, r.P - 1);
        }
        recs.push_back(r);
    } else if (scenario == 2) {
        // Scenario 2: Short consecutive streak (2-4 days) + a few extras
        int len = rnd.next(2, 4);
        int baseAbs = rnd.next(0, 70 - len); // ensure within range

        for (int i = 0; i < len; ++i) {
            Rec r;
            r.name = string(1, char('A' + i));
            int absDay = baseAbs + i;
            auto wd = fromAbs(absDay);
            r.W = wd.first;
            r.D = wd.second;
            r.P = rnd.next(1, 50000);
            r.M = rnd.next(r.P, 100000); // always enough
            recs.push_back(r);
        }

        int extraMax = 5 - len;
        int extraCnt = (extraMax > 0 ? rnd.next(0, extraMax) : 0);
        for (int j = 0; j < extraCnt; ++j) {
            Rec r;
            r.name = string(1, char('A' + len + j));
            int absDay = rnd.next(0, 69);
            auto wd = fromAbs(absDay);
            r.W = wd.first;
            r.D = wd.second;
            bool enough = rnd.next(0, 2) == 0; // 1/3 enough, 2/3 not
            if (enough) {
                r.P = rnd.next(0, 100000);
                r.M = rnd.next(r.P, 100000);
            } else {
                r.P = rnd.next(1, 100000);
                r.M = rnd.next(0, r.P - 1);
            }
            recs.push_back(r);
        }
    } else if (scenario == 3) {
        // Scenario 3: Medium random case (6-10 seniors), mixed affordability
        int N = rnd.next(6, 10);
        recs.resize(N);
        for (int i = 0; i < N; ++i) {
            Rec &r = recs[i];
            r.name = string(1, char('A' + i));
            int absDay = rnd.next(0, 69);
            auto wd = fromAbs(absDay);
            r.W = wd.first;
            r.D = wd.second;
            if (i == 0) {
                // force one enough
                r.P = rnd.next(0, 100000);
                r.M = rnd.next(r.P, 100000);
            } else if (i == 1) {
                // force one not enough
                r.P = rnd.next(1, 100000);
                r.M = rnd.next(0, r.P - 1);
            } else {
                bool enough = rnd.next(0, 1);
                if (enough) {
                    r.P = rnd.next(0, 100000);
                    r.M = rnd.next(r.P, 100000);
                } else {
                    r.P = rnd.next(1, 100000);
                    r.M = rnd.next(0, r.P - 1);
                }
            }
        }
    } else if (scenario == 4) {
        // Scenario 4: All appointments on the same day
        int N = rnd.next(3, 8);
        int absDay = rnd.next(0, 69);
        auto wd = fromAbs(absDay);
        int W = wd.first, D = wd.second;

        recs.resize(N);
        for (int i = 0; i < N; ++i) {
            Rec &r = recs[i];
            r.name = string(1, char('A' + i));
            r.W = W;
            r.D = D;
            if (i == 0) {
                // guaranteed enough
                r.P = rnd.next(0, 100000);
                r.M = rnd.next(r.P, 100000);
            } else if (i == 1) {
                // guaranteed not enough
                r.P = rnd.next(1, 100000);
                r.M = rnd.next(0, r.P - 1);
            } else {
                bool enough = rnd.next(0, 1);
                if (enough) {
                    r.P = rnd.next(0, 100000);
                    r.M = rnd.next(r.P, 100000);
                } else {
                    r.P = rnd.next(1, 100000);
                    r.M = rnd.next(0, r.P - 1);
                }
            }
        }
    } else if (scenario == 5) {
        // Scenario 5: Consecutive streak crossing week boundary (day 5,6, then 0 of next week)
        int weekStart = rnd.next(1, 9); // so weekStart+1 <= 10
        int len = 3; // days: 5,6,0(next week)
        int baseAbs = (weekStart - 1) * 7 + 5;

        for (int i = 0; i < len; ++i) {
            Rec r;
            r.name = string(1, char('A' + i));
            int absDay = baseAbs + i;
            auto wd = fromAbs(absDay);
            r.W = wd.first;
            r.D = wd.second;
            r.P = rnd.next(1, 50000);
            r.M = rnd.next(r.P, 100000); // always enough
            recs.push_back(r);
        }

        int extraCnt = rnd.next(0, 4);
        for (int j = 0; j < extraCnt; ++j) {
            Rec r;
            r.name = string(1, char('A' + len + j));
            int absDay = rnd.next(0, 69);
            auto wd = fromAbs(absDay);
            r.W = wd.first;
            r.D = wd.second;
            bool enough = rnd.next(0, 1);
            if (enough) {
                r.P = rnd.next(0, 100000);
                r.M = rnd.next(r.P, 100000);
            } else {
                r.P = rnd.next(1, 100000);
                r.M = rnd.next(0, r.P - 1);
            }
            recs.push_back(r);
        }
    } else if (scenario == 6) {
        // Scenario 6: 5 consecutive days with one middle gap (insufficient money)
        int startAbs = rnd.next(0, 65); // 5 consecutive days
        int gapPos = rnd.next(1, 3);    // gap in the middle: 1,2,3

        for (int i = 0; i < 5; ++i) {
            Rec r;
            r.name = string(1, char('A' + i));
            int absDay = startAbs + i;
            auto wd = fromAbs(absDay);
            r.W = wd.first;
            r.D = wd.second;
            if (i == gapPos) {
                // not enough on this day
                r.P = rnd.next(1, 100000);
                r.M = rnd.next(0, r.P - 1);
            } else {
                // enough on other days
                r.P = rnd.next(0, 100000);
                r.M = rnd.next(r.P, 100000);
            }
            recs.push_back(r);
        }

        // Optional extra seniors on random days to add noise
        int extraCnt = rnd.next(0, 3);
        for (int j = 0; j < extraCnt; ++j) {
            Rec r;
            r.name = string(1, char('A' + 5 + j));
            int absDay = rnd.next(0, 69);
            auto wd = fromAbs(absDay);
            r.W = wd.first;
            r.D = wd.second;
            bool enough = rnd.next(0, 1);
            if (enough) {
                r.P = rnd.next(0, 100000);
                r.M = rnd.next(r.P, 100000);
            } else {
                r.P = rnd.next(1, 100000);
                r.M = rnd.next(0, r.P - 1);
            }
            recs.push_back(r);
        }
    }

    int N = (int)recs.size();
    println(N);

    // First block: S W D P
    for (int i = 0; i < N; ++i) {
        println(recs[i].name, recs[i].W, recs[i].D, recs[i].P);
    }

    // Second block: S M in shuffled order
    vector<int> idx(N);
    for (int i = 0; i < N; ++i) idx[i] = i;
    shuffle(idx.begin(), idx.end());

    for (int id : idx) {
        println(recs[id].name, recs[id].M);
    }

    return 0;
}
