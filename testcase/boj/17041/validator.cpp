#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    const int INF = 1000000000;
    int possibleLow = 0;
    int possibleHigh = INF;
    bool hasNone = false;

    for (int i = 1; i <= n; ++i) {
        string type = inf.readToken("on|off|none", "type");
        inf.readSpace();
        int low = inf.readInt(0, 1000, "low");
        inf.readSpace();
        int high = inf.readInt(0, 1000, "high");
        inf.readEoln();

        ensuref(low <= high, "range lower endpoint exceeds upper endpoint at segment %d: %d > %d",
                i, low, high);

        if (type == "on") {
            possibleLow += low;
            possibleHigh = min(INF, possibleHigh + high);
        } else if (type == "off") {
            ensuref(possibleHigh >= low,
                    "no nonnegative traffic flow can satisfy off-ramp range at segment %d",
                    i);
            possibleLow = max(0, possibleLow - high);
            possibleHigh -= low;
        } else {
            hasNone = true;
            possibleLow = max(possibleLow, low);
            possibleHigh = min(possibleHigh, high);
        }

        ensuref(possibleLow <= possibleHigh,
                "sensor readings are inconsistent after segment %d", i);
    }

    ensuref(hasNone, "at least one segment must have type none");
    inf.readEof();
}
