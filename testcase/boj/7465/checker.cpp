#include "testlib.h"

#include <set>
#include <string>
#include <utility>

using namespace std;

using int64 = long long;
using Design = pair<int64, int64>;

int64 n;
const int64 MAX_SIDE = 10000000LL;

__int128 square(int64 x) {
    return static_cast<__int128>(x) * x;
}

NORETURN void quitStream(InStream& stream, TResult result, const char* message) {
    stream.quitf(result, "%s", message);
}

NORETURN void quitStream(InStream& stream, TResult result, const string& message) {
    stream.quitf(result, "%s", message.c_str());
}

set<Design> readOutput(InStream& stream, TResult invalidResult) {
    int k = stream.readInt(0, 1000000, "number of graveyard designs");
    set<Design> designs;

    for (int i = 0; i < k; ++i) {
        int len = stream.readInt(1, 10000000, format("design[%d].length", i + 1).c_str());
        int64 first = stream.readLong(1LL, MAX_SIDE, format("design[%d].side[1]", i + 1).c_str());

        __int128 sum = square(first);
        int64 previous = first;
        for (int j = 2; j <= len; ++j) {
            int64 side = stream.readLong(1LL, MAX_SIDE, format("design[%d].side[%d]", i + 1, j).c_str());
            if (side != previous + 1) {
                quitStream(stream,
                           invalidResult,
                           format("design %d has non-successive side lengths: %lld followed by %lld",
                                  i + 1,
                                  previous,
                                  side));
            }
            sum += square(side);
            previous = side;
        }

        if (sum != n) {
            quitStream(stream, invalidResult, format("design %d has sum different from n", i + 1));
        }
        if (!designs.insert({first, previous}).second) {
            quitStream(stream, invalidResult, format("design %d duplicates an earlier design", i + 1));
        }
    }

    if (!stream.seekEof()) {
        quitStream(stream, invalidResult, "extra output after graveyard designs");
    }
    return designs;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readLong(1, 100000000000000LL, "n");

    set<Design> jury = readOutput(ans, _fail);
    set<Design> participant = readOutput(ouf, _wa);

    if (participant != jury) {
        quitf(_wa,
              "design set differs: expected %d designs, found %d designs",
              static_cast<int>(jury.size()),
              static_cast<int>(participant.size()));
    }

    quitf(_ok, "found %d graveyard designs", static_cast<int>(participant.size()));
}
