#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(2, 100000, "m");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(0, 1, "state_i");
    }
    inf.readEoln();

    vector<int> roomDegree(n + 1, 0);
    vector<int> lastSeenSwitch(n + 1, 0);

    for (int switchId = 1; switchId <= m; ++switchId) {
        // CHECK: The statement gives no lower bound for K, so switches with no
        // connected rooms are accepted.
        int k = inf.readInt(0, n, "k");
        for (int j = 1; j <= k; ++j) {
            inf.readSpace();
            int room = inf.readInt(1, n, "room");
            ensuref(lastSeenSwitch[room] != switchId,
                    "room %d is repeated in switch %d", room, switchId);
            lastSeenSwitch[room] = switchId;
            ++roomDegree[room];
            ensuref(roomDegree[room] <= 2,
                    "room %d is connected to more than two switches", room);
        }
        inf.readEoln();
    }

    for (int room = 1; room <= n; ++room) {
        ensuref(roomDegree[room] == 2,
                "room %d is connected to %d switches, expected 2",
                room,
                roomDegree[room]);
    }

    inf.readEof();
}
