#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct Elevator {
    long long first;
    long long step;
};

struct Claim {
    bool impossible;
    int rides;
};

long long N;
int M;
long long A, B;
vector<Elevator> elevators;

long long floorMod(long long value, long long mod) {
    long long result = value % mod;
    if (result < 0) {
        result += mod;
    }
    return result;
}

long long extendedGcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extendedGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

bool stopsAt(int elevatorIndex, long long floor) {
    const Elevator& e = elevators[elevatorIndex];
    return floor >= e.first && floor <= N && (floor - e.first) % e.step == 0;
}

bool shareStop(int leftIndex, int rightIndex) {
    const Elevator& left = elevators[leftIndex];
    const Elevator& right = elevators[rightIndex];

    long long g = gcd(left.step, right.step);
    long long diff = right.first - left.first;
    if (diff % g != 0) {
        return false;
    }

    long long leftReduced = left.step / g;
    long long rightReduced = right.step / g;
    long long x, y;
    extendedGcd(leftReduced, rightReduced, x, y);

    __int128 multiplier = (__int128)(diff / g) * x;
    long long mod = rightReduced;
    long long t = floorMod((long long)(multiplier % mod), mod);
    __int128 candidate = (__int128)left.first + (__int128)left.step * t;
    __int128 period = (__int128)left.step * rightReduced;
    long long lowerBound = max(left.first, right.first);

    if (candidate < lowerBound) {
        __int128 need = lowerBound - candidate;
        candidate += ((need + period - 1) / period) * period;
    }
    return candidate <= N;
}

Claim readClaim(InStream& stream) {
    int firstToken = stream.readInt(-1, M, "ride count or -1");
    if (firstToken == -1) {
        stream.readEoln();
        stream.readEof();
        return {true, -1};
    }

    int rides = firstToken;
    if (rides == 0) {
        stream.quitf(_wa, "ride count is 0, but A and B are different");
    }
    stream.readEoln();

    vector<int> sequence(rides);
    for (int i = 0; i < rides; ++i) {
        sequence[i] = stream.readInt(1, M, format("elevator[%d]", i + 1).c_str()) - 1;
        stream.readEoln();
    }
    stream.readEof();

    if (!stopsAt(sequence.front(), A)) {
        stream.quitf(_wa, "first elevator %d does not stop at A=%lld",
                     sequence.front() + 1, A);
    }
    if (!stopsAt(sequence.back(), B)) {
        stream.quitf(_wa, "last elevator %d does not stop at B=%lld",
                     sequence.back() + 1, B);
    }
    for (int i = 0; i + 1 < rides; ++i) {
        if (!shareStop(sequence[i], sequence[i + 1])) {
            stream.quitf(_wa, "elevators %d and %d have no common stop",
                         sequence[i] + 1, sequence[i + 1] + 1);
        }
    }

    return {false, rides};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    N = inf.readLong();
    M = inf.readInt();
    elevators.resize(M);
    for (int i = 0; i < M; ++i) {
        elevators[i].first = inf.readLong();
        elevators[i].step = inf.readLong();
    }
    A = inf.readLong();
    B = inf.readLong();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant supplied a valid %d-ride path while jury reports impossible",
              participant.rides);
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible, but jury has a %d-ride path", jury.rides);
    }
    if (participant.rides < jury.rides) {
        quitf(_fail, "participant found a shorter valid path: jury=%d participant=%d",
              jury.rides, participant.rides);
    }
    if (participant.rides > jury.rides) {
        quitf(_wa, "participant path is not shortest: jury=%d participant=%d",
              jury.rides, participant.rides);
    }

    quitf(_ok, "valid shortest path with %d rides", participant.rides);
}
