#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose Q with some variability but always small
    int mode = rnd.next(0, 9);
    int Q;
    if (mode < 3) Q = rnd.next(1, 3);
    else if (mode < 7) Q = rnd.next(3, 7);
    else Q = rnd.next(7, 10);

    bool forceAdios = rnd.next(0, 1); // whether we guarantee at least one failure

    vector<int> type(Q), val(Q);
    int cur = 0; // current number of unsolved problems in the forum

    if (!forceAdios) {
        // Generate a sequence that never causes dissolution
        for (int i = 0; i < Q; i++) {
            if (cur == 0) {
                // Must add problems
                int x;
                // Prefer small x but sometimes larger
                if (rnd.next(0, 4) == 0) x = rnd.next(5, 10);
                else x = rnd.next(1, 4);
                type[i] = 1;
                val[i] = x;
                cur += x;
            } else {
                int chooseType = rnd.next(1, 2);
                if (chooseType == 1) {
                    int x;
                    if (rnd.next(0, 4) == 0) x = rnd.next(5, 10);
                    else x = rnd.next(1, 4);
                    type[i] = 1;
                    val[i] = x;
                    cur += x;
                } else {
                    int up = min(cur, 10);
                    int y = rnd.next(1, up);
                    type[i] = 2;
                    val[i] = y;
                    cur -= y;
                }
            }
        }
    } else {
        // Generate a sequence that definitely causes dissolution at least once
        int posFail = rnd.next(1, Q); // 1-based index of the failing event
        cur = 0;

        for (int i = 1; i <= Q; i++) {
            if (i < posFail) {
                // Safe prefix: never fails, keep 0 <= cur <= 9
                if (cur == 0) {
                    // Must add, but cap so cur <= 9
                    int maxAdd = min(9 - cur, 10);
                    int x = rnd.next(1, maxAdd);
                    type[i - 1] = 1;
                    val[i - 1] = x;
                    cur += x;
                } else {
                    int chooseType = rnd.next(1, 2);
                    if (chooseType == 1 && cur < 9) {
                        int maxAdd = min(9 - cur, 10);
                        int x = rnd.next(1, maxAdd);
                        type[i - 1] = 1;
                        val[i - 1] = x;
                        cur += x;
                    } else {
                        int up = min(cur, 10);
                        int y = rnd.next(1, up);
                        type[i - 1] = 2;
                        val[i - 1] = y;
                        cur -= y;
                    }
                }
            } else if (i == posFail) {
                // Failing event: type 2 with y > cur, and y <= 10
                type[i - 1] = 2;
                int lo = cur + 1;
                if (lo > 10) lo = 10; // theoretically shouldn't happen since cur <= 9
                int y = rnd.next(lo, 10);
                val[i - 1] = y;
                // After this, logic doesn't matter; dissolution is guaranteed
                cur -= y;
            } else {
                // Remaining events can be arbitrary but must respect value bounds
                int tp = rnd.next(1, 2);
                int v = rnd.next(1, 10);
                type[i - 1] = tp;
                val[i - 1] = v;
            }
        }
    }

    println(Q);
    for (int i = 0; i < Q; i++) {
        println(type[i], val[i]);
    }

    return 0;
}
