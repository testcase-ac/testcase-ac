#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct ParsedAnswer {
    int floor;
};

int n;
int k;
string mascot;

bool fitsMascot(int floor) {
    if (mascot == "annyong") {
        return floor % 2 == 1;
    }
    return floor % 2 == 0;
}

ParsedAnswer readAnswer(InStream& stream) {
    int floor = stream.readInt(1, n, "answer floor");
    stream.readEoln();
    stream.readEof();
    return {floor};
}

int distanceToNearestValidFloor() {
    int best = n + 1;
    for (int floor = 1; floor <= n; ++floor) {
        if (fitsMascot(floor)) {
            best = min(best, abs(floor - k));
        }
    }
    return best;
}

void validateAnswer(InStream& stream, ParsedAnswer answer, int bestDistance) {
    if (!fitsMascot(answer.floor)) {
        stream.quitf(_wa, "floor %d does not match mascot %s", answer.floor, mascot.c_str());
    }

    int distance = abs(answer.floor - k);
    if (distance != bestDistance) {
        stream.quitf(_wa,
                     "floor %d is not nearest: distance=%d nearest=%d",
                     answer.floor,
                     distance,
                     bestDistance);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    mascot = inf.readToken();
    k = inf.readInt();

    int bestDistance = distanceToNearestValidFloor();

    ParsedAnswer jury = readAnswer(ans);
    validateAnswer(ans, jury, bestDistance);

    ParsedAnswer participant = readAnswer(ouf);
    validateAnswer(ouf, participant, bestDistance);

    quitf(_ok, "accepted floor %d", participant.floor);
}
