#include "testlib.h"

#include <vector>

using namespace std;

long long X, T;

struct Claim {
    bool impossible;
    long long presses;
};

Claim readClaim(InStream& stream) {
    long long n = stream.readLong(-1, 1000000000LL, "N");
    stream.readEoln();

    if (n == -1) {
        stream.readEof();
        return {true, -1};
    }
    if (n < 0) {
        stream.quitf(_wa, "N must be -1 or non-negative, found %lld", n);
    }
    if (n > T) {
        stream.quitf(_wa, "N=%lld exceeds T=%lld", n, T);
    }

    long long distance = 0;
    long long currentSpeed = 0;
    long long previousTime = 0;
    long long previousPressTime = -1;

    for (long long i = 0; i < n; ++i) {
        long long time = stream.readLong(0, T - 1, format("time[%lld]", i + 1).c_str());
        stream.readSpace();
        long long speed = stream.readLong(0LL, 8LL, format("button[%lld]", i + 1).c_str());
        stream.readEoln();

        if (!(speed == 0 || speed == 1 || speed == 4 || speed == 8)) {
            stream.quitf(_wa, "button[%lld]=%lld is not one of 0, 1, 4, 8", i + 1, speed);
        }
        if (time <= previousPressTime) {
            stream.quitf(_wa,
                         "press times must be strictly increasing, time[%lld]=%lld after %lld",
                         i + 1,
                         time,
                         previousPressTime);
        }

        distance += (time - previousTime) * currentSpeed;
        previousTime = time;
        previousPressTime = time;
        currentSpeed = speed;
    }

    distance += (T - previousTime) * currentSpeed;
    stream.readEof();

    if (distance != X) {
        stream.quitf(_wa, "schedule travels %lld meters instead of %lld", distance, X);
    }

    return {false, n};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    X = inf.readLong();
    T = inf.readLong();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid schedule with %lld presses while jury says impossible", participant.presses);
    }

    if (participant.impossible) {
        quitf(_wa, "participant says impossible, but jury has a valid schedule");
    }
    if (participant.presses < jury.presses) {
        quitf(_fail,
              "participant found fewer presses than jury: participant=%lld jury=%lld",
              participant.presses,
              jury.presses);
    }
    if (participant.presses > jury.presses) {
        quitf(_wa,
              "participant uses more presses than jury: participant=%lld jury=%lld",
              participant.presses,
              jury.presses);
    }

    quitf(_ok, "valid schedule with %lld presses", participant.presses);
}
