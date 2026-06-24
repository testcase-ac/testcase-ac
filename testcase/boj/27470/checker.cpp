#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

int n;
int requiredSize;
vector<int> inputValues;

struct Answer {
    bool possible;
};

bool consumeValue(vector<char>& used, int value) {
    auto range = equal_range(inputValues.begin(), inputValues.end(), value);
    for (auto it = range.first; it != range.second; ++it) {
        int index = (int)(it - inputValues.begin());
        if (!used[index]) {
            used[index] = 1;
            return true;
        }
    }
    return false;
}

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("[A-Za-z]+", "verdict");
    for (char& c : verdict) {
        c = (char)toupper(c);
    }

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }
    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    vector<char> used(inputValues.size(), 0);
    int subsetGcd = 0;
    for (int i = 0; i < requiredSize; ++i) {
        int value = stream.readInt(2, 1000000000, format("subset[%d]", i + 1).c_str());
        if (!consumeValue(used, value)) {
            stream.quitf(_wa, "subset[%d]=%d is not available in the input multiset", i + 1, value);
        }
        subsetGcd = gcd(subsetGcd, value);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after subset");
    }
    if (subsetGcd <= 1) {
        stream.quitf(_wa, "subset gcd is %d, expected greater than 1", subsetGcd);
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    requiredSize = (n + 1) / 2;
    inputValues = inf.readInts(n);
    sort(inputValues.begin(), inputValues.end());

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.possible) {
        if (!participant.possible) {
            quitf(_ok, "both outputs report NO");
        }
        quitf(_fail, "participant found a valid cool subset while jury reports NO");
    }
    if (!participant.possible) {
        quitf(_wa, "jury provides a valid cool subset but participant reports NO");
    }
    quitf(_ok, "valid cool subset of size %d", requiredSize);
}
