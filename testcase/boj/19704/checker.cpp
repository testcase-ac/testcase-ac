#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

int n;
vector<long long> xs, ys;

struct Answer {
    long long x;
    long long y;
    __int128 cost;
};

__int128 absDiff(long long a, long long b) {
    return a >= b ? (__int128)a - b : (__int128)b - a;
}

string formatInt128(__int128 value) {
    if (value == 0) {
        return "0";
    }

    bool negative = value < 0;
    if (negative) {
        value = -value;
    }

    string result;
    while (value > 0) {
        result.push_back(char('0' + value % 10));
        value /= 10;
    }
    if (negative) {
        result.push_back('-');
    }
    reverse(result.begin(), result.end());
    return result;
}

__int128 travelCost(long long x, long long y) {
    __int128 total = 0;
    for (int i = 0; i < n; ++i) {
        total += absDiff(x, xs[i]) + absDiff(y, ys[i]);
    }
    return total;
}

Answer readAnswer(InStream& stream) {
    long long x = stream.readLong(-4000000000000000000LL, 4000000000000000000LL, "X");
    long long y = stream.readLong(-4000000000000000000LL, 4000000000000000000LL, "Y");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after coordinate");
    }
    return {x, y, travelCost(x, y)};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    xs.resize(n);
    ys.resize(n);
    for (int i = 0; i < n; ++i) {
        xs[i] = inf.readLong();
        ys[i] = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.cost > jury.cost) {
        quitf(_wa,
              "participant cost %s is worse than jury cost %s",
              formatInt128(participant.cost).c_str(),
              formatInt128(jury.cost).c_str());
    }
    if (participant.cost < jury.cost) {
        quitf(_fail,
              "participant found better cost %s than jury cost %s",
              formatInt128(participant.cost).c_str(),
              formatInt128(jury.cost).c_str());
    }

    quitf(_ok,
          "participant coordinate (%lld, %lld) matches jury cost %s",
          participant.x,
          participant.y,
          formatInt128(participant.cost).c_str());
}
