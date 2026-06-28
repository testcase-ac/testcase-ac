#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

// BOJ 25923 has many valid shortest cycles, so compare route certificates by
// their validated total distance instead of exact text.
struct Answer {
    bool impossible;
    long long distance;
};

int n;
int k;

Answer readAnswer(InStream& stream) {
    const long long maxDistance = 1LL * n * (n - 1);
    long long claimed = stream.readLong(-1, maxDistance, "answer length");

    if (claimed == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, -1};
    }

    vector<int> route(n + 1);
    vector<int> seen(n + 1, 0);
    for (int i = 0; i <= n; ++i) {
        route[i] = stream.readInt(1, n, format("route[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after route");
    }

    if (route.front() != 1) {
        stream.quitf(_wa, "route starts at %d instead of 1", route.front());
    }
    if (route.back() != 1) {
        stream.quitf(_wa, "route ends at %d instead of 1", route.back());
    }

    for (int i = 1; i < n; ++i) {
        int booth = route[i];
        if (booth == 1) {
            stream.quitf(_wa, "booth 1 appears before the final return");
        }
        if (seen[booth]) {
            stream.quitf(_wa, "booth %d is repeated", booth);
        }
        seen[booth] = 1;
    }
    for (int booth = 2; booth <= n; ++booth) {
        if (!seen[booth]) {
            stream.quitf(_wa, "booth %d is missing", booth);
        }
    }

    long long actual = 0;
    for (int i = 1; i <= n; ++i) {
        int prev = route[i - 1];
        int cur = route[i];
        int distance = abs(cur - prev);
        if (distance > k) {
            stream.quitf(_wa,
                         "move %d from %d to %d has distance %d greater than K=%d",
                         i,
                         prev,
                         cur,
                         distance,
                         k);
        }
        if ((prev & cur) == 0) {
            stream.quitf(_wa, "move %d from %d to %d has bitwise AND 0", i, prev, cur);
        }
        actual += distance;
    }

    if (actual != claimed) {
        stream.quitf(_wa, "claimed length %lld does not match route length %lld", claimed, actual);
    }

    return {false, actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid route of length %lld but jury reports -1",
              participant.distance);
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports -1 but jury has a route of length %lld", jury.distance);
    }
    if (participant.distance > jury.distance) {
        quitf(_wa,
              "participant route is longer than jury route: participant=%lld jury=%lld",
              participant.distance,
              jury.distance);
    }
    if (participant.distance < jury.distance) {
        quitf(_fail,
              "participant route is shorter than jury route: participant=%lld jury=%lld",
              participant.distance,
              jury.distance);
    }

    quitf(_ok, "route length %lld", participant.distance);
}
