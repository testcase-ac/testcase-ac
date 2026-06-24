#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

struct TestCase {
    string first;
    string second;
};

struct Claim {
    vector<string> names;
};

static bool containsSubsequence(const string& text, const string& pattern) {
    size_t pos = 0;
    for (char ch : text) {
        if (pos < pattern.size() && ch == pattern[pos]) {
            ++pos;
        }
    }
    return pos == pattern.size();
}

static Claim readClaim(InStream& stream, const vector<TestCase>& tests) {
    Claim claim;
    claim.names.reserve(tests.size());

    for (size_t i = 0; i < tests.size(); ++i) {
        string name = stream.readToken("[A-Za-z]{1,200}",
                                       format("name[%d]", int(i + 1)).c_str());

        if (!containsSubsequence(name, tests[i].first)) {
            stream.quitf(_wa,
                         "name[%d] does not contain first fruit as a subsequence",
                         int(i + 1));
        }
        if (!containsSubsequence(name, tests[i].second)) {
            stream.quitf(_wa,
                         "name[%d] does not contain second fruit as a subsequence",
                         int(i + 1));
        }
        claim.names.push_back(name);
    }

    stream.readEof();
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    vector<TestCase> tests;
    while (!inf.seekEof()) {
        TestCase test;
        test.first = inf.readToken("[A-Za-z]{1,100}", "first fruit");
        test.second = inf.readToken("[A-Za-z]{1,100}", "second fruit");
        tests.push_back(test);
    }

    Claim jury = readClaim(ans, tests);
    Claim participant = readClaim(ouf, tests);

    for (size_t i = 0; i < tests.size(); ++i) {
        size_t juryLength = jury.names[i].size();
        size_t participantLength = participant.names[i].size();
        if (participantLength > juryLength) {
            quitf(_wa,
                  "name[%d] is longer than jury answer: participant=%d jury=%d",
                  int(i + 1), int(participantLength), int(juryLength));
        }
        if (participantLength < juryLength) {
            quitf(_fail,
                  "name[%d] is shorter than jury answer: participant=%d jury=%d",
                  int(i + 1), int(participantLength), int(juryLength));
        }
    }

    quitf(_ok, "%d names accepted", int(tests.size()));
}
