#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int m, n;
vector<int> aTarget, bTarget;

struct Answer {
    string aMode;
    string bMode;
};

string readBinaryString(InStream& stream, int expectedLength, const char* name) {
    string value = stream.readToken();
    if ((int)value.size() != expectedLength) {
        stream.quitf(_wa, "%s has length %d instead of %d",
                     name, (int)value.size(), expectedLength);
    }
    for (int i = 0; i < expectedLength; ++i) {
        if (value[i] != '0' && value[i] != '1') {
            stream.quitf(_wa, "%s[%d] is '%c', expected 0 or 1",
                         name, i + 1, value[i]);
        }
    }
    return value;
}

Answer readAnswer(InStream& stream) {
    Answer answer;
    answer.aMode = readBinaryString(stream, m, "A modes");
    stream.readEoln();
    answer.bMode = readBinaryString(stream, n, "B modes");
    stream.readEoln();
    stream.readEof();

    vector<int> incomingToA(m, 0), incomingToB(n, 0);

    for (int i = 0; i < m; ++i) {
        if (answer.aMode[i] == '1') {
            int target = aTarget[i];
            if (answer.bMode[target] != '0') {
                stream.quitf(_wa,
                             "A[%d] sends to B[%d], but B[%d] is not receiving",
                             i + 1, target + 1, target + 1);
            }
            ++incomingToB[target];
        }
    }

    for (int j = 0; j < n; ++j) {
        if (answer.bMode[j] == '1') {
            int target = bTarget[j];
            if (answer.aMode[target] != '0') {
                stream.quitf(_wa,
                             "B[%d] sends to A[%d], but A[%d] is not receiving",
                             j + 1, target + 1, target + 1);
            }
            ++incomingToA[target];
        }
    }

    for (int i = 0; i < m; ++i) {
        if (answer.aMode[i] == '0' && incomingToA[i] == 0) {
            stream.quitf(_wa, "A[%d] is receiving but has no incoming sender", i + 1);
        }
    }
    for (int j = 0; j < n; ++j) {
        if (answer.bMode[j] == '0' && incomingToB[j] == 0) {
            stream.quitf(_wa, "B[%d] is receiving but has no incoming sender", j + 1);
        }
    }

    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    m = inf.readInt();
    n = inf.readInt();
    aTarget.resize(m);
    bTarget.resize(n);

    for (int i = 0; i < m; ++i) {
        aTarget[i] = inf.readInt() - 1;
    }
    for (int j = 0; j < n; ++j) {
        bTarget[j] = inf.readInt() - 1;
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid assignment");
}
