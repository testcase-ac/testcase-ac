#include "testlib.h"

#include <string>

using namespace std;

int n;
string input;

struct Output {
    int length;
    string garland;
};

bool isSubsequence(const string& candidate) {
    int pos = 0;
    for (char ch : input) {
        if (pos < (int)candidate.size() && candidate[pos] == ch) {
            ++pos;
        }
    }
    return pos == (int)candidate.size();
}

bool isBeautiful(const string& garland) {
    int firstOne = (int)garland.find('1');
    if (firstOne == (int)string::npos) {
        return false;
    }

    int zeroBlock = firstOne;
    int zerosSinceLastOne = 0;
    for (int i = firstOne + 1; i < (int)garland.size(); ++i) {
        if (garland[i] == '0') {
            ++zerosSinceLastOne;
            if (zerosSinceLastOne > zeroBlock) {
                return false;
            }
        } else {
            if (zerosSinceLastOne != zeroBlock) {
                return false;
            }
            zerosSinceLastOne = 0;
        }
    }
    return zerosSinceLastOne == zeroBlock;
}

Output readOutput(InStream& stream) {
    int length = stream.readInt(1, n, "m");
    stream.readEoln();

    string garland = stream.readToken("[01]+", "garland");
    stream.readEoln();
    stream.readEof();

    if ((int)garland.size() != length) {
        stream.quitf(_wa, "garland length is %d but m is %d", (int)garland.size(), length);
    }
    if (!isSubsequence(garland)) {
        stream.quitf(_wa, "garland is not a subsequence of the input");
    }
    if (!isBeautiful(garland)) {
        stream.quitf(_wa, "garland is not beautiful");
    }

    return {length, garland};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 500000, "n");
    inf.readEoln();
    input = inf.readToken("[01]+", "s");
    inf.readEoln();
    inf.readEof();

    if ((int)input.size() != n) {
        quitf(_fail, "input length is %d but n is %d", (int)input.size(), n);
    }

    Output jury = readOutput(ans);
    Output participant = readOutput(ouf);

    if (participant.length < jury.length) {
        quitf(_wa, "jury has a longer garland: jury=%d participant=%d",
              jury.length, participant.length);
    }
    if (participant.length > jury.length) {
        quitf(_fail, "participant found a longer garland: jury=%d participant=%d",
              jury.length, participant.length);
    }

    quitf(_ok, "answer length %d", participant.length);
}
