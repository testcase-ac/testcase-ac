#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

int n;

struct Answer {
    bool hasSolution;
};

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("Yes|No", "verdict");

    if (verdict == "No") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after No");
        }
        return {false};
    }

    vector<long long> sums;
    sums.reserve(2 * n);
    vector<long long> columnSums(n, 0);

    for (int i = 0; i < n; ++i) {
        long long rowSum = 0;
        for (int j = 0; j < n; ++j) {
            int value = stream.readInt(-1, 1, format("M[%d][%d]", i + 1, j + 1).c_str());
            rowSum += value;
            columnSums[j] += value;
        }
        sums.push_back(rowSum);
    }
    for (long long columnSum : columnSums) {
        sums.push_back(columnSum);
    }

    set<long long> distinct(sums.begin(), sums.end());
    if (distinct.size() != sums.size()) {
        stream.quitf(_wa, "row and column sums are not pairwise distinct");
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after matrix");
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000, "n");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.hasSolution != participant.hasSolution) {
        if (!jury.hasSolution && participant.hasSolution) {
            quitf(_fail, "participant found a valid matrix but jury says No");
        }
        quitf(_wa, "expected %s, found %s",
              jury.hasSolution ? "Yes" : "No",
              participant.hasSolution ? "Yes" : "No");
    }

    quitf(_ok, "answer is %s", participant.hasSolution ? "Yes" : "No");
}
