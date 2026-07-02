#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Output {
    bool possible;
};

int n;
vector<int> requiredAudience;

Output readOutput(InStream& stream) {
    string verdict = stream.readToken("[A-Z]+", "verdict");
    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }
    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    string assignment = stream.readToken("[123]+", "assignment");
    if ((int)assignment.size() != n) {
        stream.quitf(_wa, "assignment length is %d, expected %d", (int)assignment.size(), n);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after assignment");
    }

    vector<int> groupSize(3, 0);
    vector<int> group(n);
    for (int i = 0; i < n; ++i) {
        group[i] = assignment[i] - '1';
        ++groupSize[group[i]];
    }

    for (int i = 0; i < n; ++i) {
        int audienceGroup = (group[i] + 1) % 3;
        int audienceSize = groupSize[audienceGroup];
        if (audienceSize < requiredAudience[i]) {
            stream.quitf(_wa,
                         "student %d is in group %d and needs at least %d listeners, but group %d has %d",
                         i + 1,
                         group[i] + 1,
                         requiredAudience[i],
                         audienceGroup + 1,
                         audienceSize);
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    requiredAudience.resize(n);
    for (int i = 0; i < n; ++i) {
        requiredAudience[i] = inf.readInt();
    }

    Output jury = readOutput(ans);
    Output participant = readOutput(ouf);

    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant provided a valid assignment while jury says NO");
    }
    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury has a valid assignment but participant says NO");
    }

    quitf(_ok, participant.possible ? "valid assignment" : "both outputs report NO");
}
