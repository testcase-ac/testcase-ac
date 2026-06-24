#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Elevator {
    int first;
    int step;
};

struct Answer {
    bool impossible;
    int rides;
};

int n, m, startFloor, targetFloor;
vector<Elevator> elevators;

bool servesFloor(int elevatorId, int floor) {
    const Elevator& elevator = elevators[elevatorId];
    return floor >= elevator.first && (floor - elevator.first) % elevator.step == 0;
}

bool canTransfer(int lhs, int rhs) {
    const Elevator& a = elevators[lhs];
    const Elevator& b = elevators[rhs];

    if (a.step > b.step) {
        swap(lhs, rhs);
    }

    for (int floor = elevators[lhs].first; floor <= n; floor += elevators[lhs].step) {
        if (servesFloor(rhs, floor)) {
            return true;
        }
    }
    return false;
}

Answer readAnswer(InStream& stream) {
    int rides = stream.readInt(-1, m, "ride count");
    stream.readEoln();

    if (rides == -1) {
        stream.readEof();
        return {true, -1};
    }

    if (rides == 0) {
        stream.quitf(_wa, "ride count must be positive or -1");
    }

    vector<int> path(rides);
    for (int i = 0; i < rides; ++i) {
        path[i] = stream.readInt(1, m, format("elevator[%d]", i + 1).c_str());
        stream.readEoln();
    }
    stream.readEof();

    if (!servesFloor(path.front(), startFloor)) {
        stream.quitf(_wa,
                     "first elevator %d does not stop at start floor %d",
                     path.front(),
                     startFloor);
    }
    if (!servesFloor(path.back(), targetFloor)) {
        stream.quitf(_wa,
                     "last elevator %d does not stop at target floor %d",
                     path.back(),
                     targetFloor);
    }
    for (int i = 0; i + 1 < rides; ++i) {
        if (!canTransfer(path[i], path[i + 1])) {
            stream.quitf(_wa,
                         "cannot transfer between elevator %d and elevator %d",
                         path[i],
                         path[i + 1]);
        }
    }

    return {false, rides};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    elevators.assign(m + 1, {});
    for (int i = 1; i <= m; ++i) {
        elevators[i].first = inf.readInt();
        elevators[i].step = inf.readInt();
    }
    startFloor = inf.readInt();
    targetFloor = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail,
              "participant found a valid route with %d rides while jury reports impossible",
              participant.rides);
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury has a route with %d rides", jury.rides);
    }
    if (participant.rides < jury.rides) {
        quitf(_fail,
              "participant found a shorter valid route: participant=%d jury=%d",
              participant.rides,
              jury.rides);
    }
    if (participant.rides > jury.rides) {
        quitf(_wa,
              "participant route uses too many rides: participant=%d jury=%d",
              participant.rides,
              jury.rides);
    }

    quitf(_ok, "valid route with %d rides", participant.rides);
}
