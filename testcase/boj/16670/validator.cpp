#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXQ = 300000;
    const int MAXT = 1000000;
    const int MAXD = 1000000;

    int q = inf.readInt(1, MAXQ, "q");
    inf.readEoln();

    // We need to verify:
    // - cancel events refer to valid join events (1-based index in event list)
    // - the referenced event is of type join
    // - it has not been canceled yet
    // - after each event, no two active knights have the same entrance time

    struct JoinInfo {
        bool exists = false;   // there is a '+' at this position
        bool active = false;   // not canceled yet
        int t = 0;
        int d = 0;
    };

    vector<JoinInfo> joins(q + 1); // index by event position (1..q)
    // For fast uniqueness check of active entrance times
    // times are in [1..1e6]
    vector<int> timeOwner(MAXT + 1, 0); // 0 = free, otherwise index of join event

    for (int ev = 1; ev <= q; ++ev) {
        char type = inf.readChar();
        inf.readSpace();

        if (type == '+') {
            int t = inf.readInt(1, MAXT, "t");
            inf.readSpace();
            int d = inf.readInt(1, MAXD, "d");
            inf.readEoln();

            // ensure uniqueness of t among active knights
            ensuref(timeOwner[t] == 0,
                    "Duplicate entrance time %d at event %d; already used by join event %d",
                    t, ev, timeOwner[t]);

            timeOwner[t] = ev;
            joins[ev].exists = true;
            joins[ev].active = true;
            joins[ev].t = t;
            joins[ev].d = d;
        } else if (type == '-') {
            int idx = inf.readInt(1, q, "i");
            inf.readEoln();

            ensuref(joins[idx].exists,
                    "Cancel at event %d refers to event %d which is not a join",
                    ev, idx);
            ensuref(joins[idx].active,
                    "Cancel at event %d refers to join event %d which is already canceled",
                    ev, idx);

            int t = joins[idx].t;
            // timeOwner[t] must point to this join
            ensuref(timeOwner[t] == idx,
                    "Internal inconsistency: timeOwner[%d]=%d, expected %d",
                    t, timeOwner[t], idx);
            timeOwner[t] = 0;
            joins[idx].active = false;
        } else if (type == '?') {
            int t = inf.readInt(1, MAXT, "t");
            inf.readEoln();
            // Nothing else to validate here (no further guarantees about answer).
        } else {
            ensuref(false, "Unknown event type '%c' at event %d", type, ev);
        }
    }

    inf.readEof();
}
