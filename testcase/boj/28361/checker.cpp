#include "testlib.h"

#include <vector>

using namespace std;

int n;

struct Answer {
    long long moves;
};

int directionOfMove(int from, int to) {
    int clockwise = to - from;
    if (clockwise <= 0) {
        clockwise += n;
    }

    int counterClockwise = from - to;
    if (counterClockwise <= 0) {
        counterClockwise += n;
    }

    if (clockwise >= 1 && clockwise <= 2) {
        return 1;
    }
    if (counterClockwise >= 1 && counterClockwise <= 2) {
        return -1;
    }
    return 0;
}

Answer readAnswer(InStream& stream) {
    long long k = stream.readLong(0, 2LL * n + 5, "K");
    stream.readEoln();

    vector<char> visited(n + 1, 0);
    int prev = stream.readInt(1, n, "path[1]");
    if (prev != 1) {
        stream.quitf(_wa, "path[1] is %d instead of 1", prev);
    }
    visited[prev] = 1;

    int sameDirectionRun = 0;
    int lastDirection = 0;
    for (long long i = 1; i <= k; ++i) {
        int cur = stream.readInt(1, n, format("path[%lld]", i + 1).c_str());
        if (cur == prev) {
            stream.quitf(_wa, "path[%lld] repeats house %d consecutively", i + 1, cur);
        }

        int direction = directionOfMove(prev, cur);
        if (direction == 0) {
            stream.quitf(_wa, "move %lld from %d to %d has circular distance greater than 2", i, prev, cur);
        }
        if (direction == lastDirection) {
            ++sameDirectionRun;
        } else {
            lastDirection = direction;
            sameDirectionRun = 1;
        }
        if (sameDirectionRun >= 3) {
            stream.quitf(_wa, "moves %lld..%lld use the same direction three times in a row", i - 2, i);
        }

        visited[cur] = 1;
        prev = cur;
    }
    stream.readEoln();
    stream.readEof();

    if (prev != 1) {
        stream.quitf(_wa, "path ends at %d instead of 1", prev);
    }
    for (int house = 1; house <= n; ++house) {
        if (!visited[house]) {
            stream.quitf(_wa, "house %d is not visited", house);
        }
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(5, 1000000, "N");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.moves < jury.moves) {
        quitf(_fail, "participant found a better tour: jury=%lld participant=%lld", jury.moves, participant.moves);
    }
    if (participant.moves > jury.moves) {
        quitf(_wa, "jury has a better tour: jury=%lld participant=%lld", jury.moves, participant.moves);
    }
    quitf(_ok, "valid optimal tour with %lld moves", participant.moves);
}
