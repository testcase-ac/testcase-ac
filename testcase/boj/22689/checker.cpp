#include "testlib.h"

#include <cstdarg>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

struct Dataset {
    int n;
    int m;
    vector<int> l;
};

struct Claim {
    bool goofy;
    bool validWitness;
};

vector<Dataset> datasets;

void quitFor(InStream& stream, TResult result, const char* format, ...) {
    char message[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    stream.quitf(result, "%s", message);
}

Claim readClaim(InStream& stream, const Dataset& data, int caseIndex, TResult invalidResult) {
    string token = stream.readToken();
    if (token == "Goofy") {
        return {true, false};
    }

    const int expectedLength = data.n + data.m - 1;
    if ((int)token.size() != expectedLength) {
        quitFor(stream, invalidResult,
                "case %d: binary sequence length is %d, expected %d",
                caseIndex, (int)token.size(), expectedLength);
    }

    vector<int> k(expectedLength);
    for (int i = 0; i < expectedLength; ++i) {
        if (token[i] != '0' && token[i] != '1') {
            quitFor(stream, invalidResult,
                    "case %d: character %d is '%c', expected 0 or 1",
                    caseIndex, i + 1, token[i]);
        }
        k[i] = token[i] - '0';
    }

    for (int j = 0; j < data.n; ++j) {
        int sum = 0;
        for (int i = j; i < j + data.m; ++i) {
            sum += k[i];
        }
        if (sum != data.l[j]) {
            quitFor(stream, invalidResult,
                    "case %d: window %d has sum %d, expected %d",
                    caseIndex, j + 1, sum, data.l[j]);
        }
    }

    return {false, true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    while (true) {
        int n = inf.readInt();
        int m = inf.readInt();
        if (n == 0 && m == 0) {
            break;
        }

        Dataset data;
        data.n = n;
        data.m = m;
        data.l.resize(n);
        for (int i = 0; i < n; ++i) {
            data.l[i] = inf.readInt();
        }
        datasets.push_back(data);
    }

    for (int i = 0; i < (int)datasets.size(); ++i) {
        Claim jury = readClaim(ans, datasets[i], i + 1, _fail);
        Claim participant = readClaim(ouf, datasets[i], i + 1, _wa);

        if (jury.goofy) {
            if (participant.goofy) {
                continue;
            }
            if (participant.validWitness) {
                quitf(_fail, "case %d: participant found a valid witness but jury says Goofy", i + 1);
            }
        } else {
            if (participant.goofy) {
                quitf(_wa, "case %d: participant says Goofy but jury has a valid witness", i + 1);
            }
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    quitf(_ok, "%d answer(s) accepted", (int)datasets.size());
}
