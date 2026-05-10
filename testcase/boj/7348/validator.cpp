#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        set<int> used_rooms;
        int N = inf.readInt(1, 200, "N");
        inf.readEoln();

        // To check that each room appears at most once in all s/t in this testcase
        set<int> room_used;

        for (int i = 0; i < N; ++i) {
            int s = inf.readInt(1, 400, "s");
            inf.readSpace();
            int t = inf.readInt(1, 400, "t");
            inf.readEoln();

            ensuref(s != t, "s and t must be different at testcase %d, move %d: s=%d, t=%d", tc, i+1, s, t);

            ensuref(room_used.count(s) == 0, "Room %d used more than once as source or target in testcase %d", s, tc);
            ensuref(room_used.count(t) == 0, "Room %d used more than once as source or target in testcase %d", t, tc);
            room_used.insert(s);
            room_used.insert(t);
        }
    }

    inf.readEof();
}
