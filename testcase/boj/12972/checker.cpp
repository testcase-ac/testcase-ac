#include "testlib.h"
#include <algorithm>
#include <map>
#include <numeric>
#include <vector>
using namespace std;

int n;
map<int, int> inputTable;

struct Answer {
    vector<int> values;
};

Answer readAnswer(InStream& stream) {
    vector<int> values;
    values.reserve(n);
    for (int i = 0; i < n; ++i) {
        values.push_back(stream.readInt(1, 1000000000, format("a[%d]", i + 1)));
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d sequence values", n);
    }
    return {values};
}

void validateAnswer(InStream& stream, const Answer& answer) {
    map<int, int> table;
    for (int x : answer.values) {
        for (int y : answer.values) {
            ++table[gcd(x, y)];
        }
    }

    if (table != inputTable) {
        stream.quitf(_wa, "output sequence does not reproduce the input GCD table");
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    for (int i = 0; i < n * n; ++i) {
        int value = inf.readInt();
        ++inputTable[value];
    }

    Answer jury = readAnswer(ans);
    validateAnswer(ans, jury);

    Answer participant = readAnswer(ouf);
    validateAnswer(ouf, participant);

    quitf(_ok, "valid sequence of length %d", n);
}
