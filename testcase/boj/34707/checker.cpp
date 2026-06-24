#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n, k;
vector<int> p;
vector<int> positionOfValue;

struct Output {
    bool yes;
};

Output readOutput(InStream& stream, TResult invalidVerdict) {
    string verdict = stream.readToken("[A-Za-z]+", "verdict");

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(invalidVerdict, "extra output after NO");
        }
        return {false};
    }

    if (verdict != "YES") {
        stream.quitf(invalidVerdict, "verdict must be YES or NO, found %s", verdict.c_str());
    }

    vector<int> witness(k);
    for (int i = 0; i < k; ++i) {
        witness[i] = stream.readInt(1, n, format("witness[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after witness");
    }

    int firstPos = positionOfValue[witness[0]];
    if (firstPos + k > n) {
        stream.quitf(invalidVerdict, "witness does not fit in the input permutation from position %d", firstPos + 1);
    }

    for (int i = 0; i < k; ++i) {
        if (p[firstPos + i] != witness[i]) {
            stream.quitf(invalidVerdict,
                         "witness[%d]=%d does not match input position %d, which has %d",
                         i + 1, witness[i], firstPos + i + 1, p[firstPos + i]);
        }
    }

    int mn = *min_element(witness.begin(), witness.end());
    int mx = *max_element(witness.begin(), witness.end());
    if (mx - mn + 1 != k) {
        stream.quitf(invalidVerdict,
                     "witness values are not consecutive: min=%d max=%d length=%d",
                     mn, mx, k);
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    p.resize(n);
    positionOfValue.assign(n + 1, -1);
    for (int i = 0; i < n; ++i) {
        p[i] = inf.readInt();
        positionOfValue[p[i]] = i;
    }

    Output jury = readOutput(ans, _fail);
    Output participant = readOutput(ouf, _wa);

    if (!jury.yes) {
        if (!participant.yes) {
            quitf(_ok, "both outputs claim NO");
        }
        quitf(_fail, "participant found a valid witness while jury claims NO");
    }

    if (!participant.yes) {
        quitf(_wa, "jury has a valid witness but participant claims NO");
    }

    quitf(_ok, "participant provided a valid witness");
}
