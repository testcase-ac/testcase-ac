#include "testlib.h"

#include <vector>

using namespace std;

struct CaseOutput {
    int length;
};

int n;

CaseOutput readCaseOutput(InStream& stream, int tc) {
    int length = stream.readInt(0, n, format("length for case %d", tc).c_str());
    stream.readEoln();

    vector<int> values(length);
    vector<bool> used(n + 1, false);
    for (int i = 0; i < length; ++i) {
        values[i] = stream.readInt(1, n, format("a[%d] for case %d", i + 1, tc).c_str());
        if (used[values[i]]) {
            stream.quitf(_wa, "case %d has duplicate value %d", tc, values[i]);
        }
        used[values[i]] = true;
        if (i + 1 < length) {
            stream.readSpace();
        }
    }
    stream.readEoln();

    for (int i = 0; i < length; ++i) {
        for (int j = i + 1; j < length; ++j) {
            for (int k = j + 1; k < length; ++k) {
                if ((values[i] ^ values[j] ^ values[k]) == 0) {
                    stream.quitf(
                        _wa,
                        "case %d has invalid triple %d, %d, %d",
                        tc,
                        values[i],
                        values[j],
                        values[k]);
                }
            }
        }
    }

    return {length};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int tc = 1; tc <= t; ++tc) {
        n = inf.readInt();

        CaseOutput jury = readCaseOutput(ans, tc);
        CaseOutput participant = readCaseOutput(ouf, tc);

        if (participant.length < jury.length) {
            quitf(
                _wa,
                "case %d participant length %d is smaller than jury length %d",
                tc,
                participant.length,
                jury.length);
        }
        if (participant.length > jury.length) {
            quitf(
                _fail,
                "case %d participant length %d is larger than jury length %d",
                tc,
                participant.length,
                jury.length);
        }
    }

    ans.readEof();
    ouf.readEof();
    quitf(_ok, "all %d case(s) match the jury objective", t);
}
