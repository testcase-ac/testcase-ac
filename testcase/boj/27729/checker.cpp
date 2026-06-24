#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int needA, needB;

long long scoreString(const string& s) {
    int len = (int)s.size();
    vector<unsigned char> hasSameDistance(len, 0);
    vector<int> positions[2];

    for (int i = 0; i < len; ++i) {
        positions[s[i] == 'b'].push_back(i);
    }

    for (const auto& pos : positions) {
        for (int i = 0; i < (int)pos.size(); ++i) {
            for (int j = i + 1; j < (int)pos.size(); ++j) {
                hasSameDistance[pos[j] - pos[i]] = 1;
            }
        }
    }

    long long score = 0;
    for (int d = 1; d < len; ++d) {
        if (hasSameDistance[d]) {
            score += d;
        }
    }
    return score;
}

struct Answer {
    long long claimed;
    long long actual;
    string s;
};

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(0LL, 200000000LL, "claimed value");
    stream.readEoln();

    string s = stream.readToken("[ab]+", "string");
    stream.readEoln();
    stream.readEof();

    int countA = 0;
    int countB = 0;
    for (char c : s) {
        if (c == 'a') {
            ++countA;
        } else {
            ++countB;
        }
    }

    if (countA != needA || countB != needB) {
        stream.quitf(_wa,
                     "string has %d a's and %d b's, expected %d a's and %d b's",
                     countA,
                     countB,
                     needA,
                     needB);
    }

    long long actual = scoreString(s);
    if (claimed != actual) {
        stream.quitf(_wa,
                     "claimed value %lld does not match string value %lld",
                     claimed,
                     actual);
    }

    return {claimed, actual, s};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    needA = inf.readInt(1, 10000, "N");
    needB = inf.readInt(1, 10000, "M");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.actual < jury.actual) {
        quitf(_wa,
              "jury has better value: jury=%lld participant=%lld",
              jury.actual,
              participant.actual);
    }
    if (participant.actual > jury.actual) {
        quitf(_fail,
              "participant found better value: jury=%lld participant=%lld",
              jury.actual,
              participant.actual);
    }

    quitf(_ok, "value=%lld", participant.actual);
}
