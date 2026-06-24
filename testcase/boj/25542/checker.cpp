#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
int l;
vector<string> candidates;

struct Output {
    bool impossible;
    string name;
};

bool isUppercaseName(const string& value) {
    if ((int)value.size() != l) {
        return false;
    }
    for (char ch : value) {
        if (ch < 'A' || ch > 'Z') {
            return false;
        }
    }
    return true;
}

bool isValidMeetingPlace(const string& value) {
    if (!isUppercaseName(value)) {
        return false;
    }

    for (const string& candidate : candidates) {
        int different = 0;
        for (int i = 0; i < l; ++i) {
            if (value[i] != candidate[i]) {
                ++different;
            }
        }
        if (different > 1) {
            return false;
        }
    }
    return true;
}

Output readOutput(InStream& stream) {
    string first = stream.readToken("([A-Z]+)", "first output token");

    if (first == "CALL") {
        string second = stream.readToken("([A-Z]+)", "second output token");
        if (second != "FRIEND") {
            stream.quitf(_wa, "expected FRIEND after CALL, found %s", second.c_str());
        }
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after CALL FRIEND");
        }
        return {true, ""};
    }

    if (!isUppercaseName(first)) {
        stream.quitf(_wa,
                     "answer must be an uppercase string of length %d or CALL FRIEND, found %s",
                     l,
                     first.c_str());
    }
    if (!isValidMeetingPlace(first)) {
        stream.quitf(_wa, "answer %s differs from at least one candidate by more than one letter", first.c_str());
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }
    return {false, first};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    l = inf.readInt();
    candidates.resize(n);
    for (int i = 0; i < n; ++i) {
        candidates[i] = inf.readToken();
    }

    Output jury = readOutput(ans);
    Output participant = readOutput(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim CALL FRIEND");
        }
        quitf(_fail, "participant found valid answer %s while jury says CALL FRIEND", participant.name.c_str());
    }

    if (participant.impossible) {
        quitf(_wa, "jury has valid answer %s, but participant says CALL FRIEND", jury.name.c_str());
    }

    quitf(_ok, "valid answer %s", participant.name.c_str());
}
