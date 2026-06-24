#include "testlib.h"

#include <vector>

using namespace std;

struct TestCase {
    int n;
    vector<int> trophy;
};

struct Output {
    vector<int> lengths;
};

vector<TestCase> tests;

Output readOutput(InStream& stream) {
    Output output;
    output.lengths.reserve(tests.size());

    for (int tc = 0; tc < (int)tests.size(); ++tc) {
        const TestCase& test = tests[tc];
        int length = stream.readInt(1, test.n, format("length[%d]", tc + 1).c_str());
        output.lengths.push_back(length);

        int previousIndex = 0;
        int previousTrophy = 0;
        for (int i = 0; i < length; ++i) {
            int index = stream.readInt(1, test.n, format("path[%d][%d]", tc + 1, i + 1).c_str());
            if (index <= previousIndex) {
                stream.quitf(_wa,
                             "test case %d path index %d is not strictly after previous index %d",
                             tc + 1,
                             index,
                             previousIndex);
            }
            int trophy = test.trophy[index - 1];
            if (i > 0 && trophy <= previousTrophy) {
                stream.quitf(_wa,
                             "test case %d trophy at path position %d has size %d after previous size %d",
                             tc + 1,
                             i + 1,
                             trophy,
                             previousTrophy);
            }
            previousIndex = index;
            previousTrophy = trophy;
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after all test cases");
    }
    return output;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    tests.reserve(t);
    for (int tc = 0; tc < t; ++tc) {
        TestCase test;
        test.n = inf.readInt();
        test.trophy = inf.readInts(test.n);
        tests.push_back(test);
    }

    Output jury = readOutput(ans);
    Output participant = readOutput(ouf);

    for (int tc = 0; tc < t; ++tc) {
        int juryLength = jury.lengths[tc];
        int participantLength = participant.lengths[tc];
        if (participantLength < juryLength) {
            quitf(_wa,
                  "test case %d jury has longer path: jury=%d participant=%d",
                  tc + 1,
                  juryLength,
                  participantLength);
        }
        if (participantLength > juryLength) {
            quitf(_fail,
                  "test case %d participant found longer path: jury=%d participant=%d",
                  tc + 1,
                  juryLength,
                  participantLength);
        }
    }

    quitf(_ok, "all %d test case(s) match jury path lengths", t);
}
