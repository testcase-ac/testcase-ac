#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50000, "n");
    inf.readEoln();

    long long totalGoalRooms = 0;
    for (int room = 1; room < n; ++room) {
        int m = inf.readInt(0, n, "m");
        inf.readEoln();

        totalGoalRooms += m;
        ensuref(totalGoalRooms <= 1000000,
                "total number of goal rooms exceeds 1000000 after room %d", room);

        // CHECK: the statement says m = 0 has an empty list line, but official samples omit it.
        if (m == 0) {
            if (!inf.eof()) {
                inf.eoln();
            }
            continue;
        }

        int previous = 0;
        for (int i = 0; i < m; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            int goal = inf.readInt(1, n, "goal");
            ensuref(previous < goal,
                    "goal rooms for room %d are not strictly ascending at position %d", room, i + 1);
            previous = goal;
        }
        inf.readEoln();
    }

    inf.readEof();
}
