#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
vector<string> expectedColors;

bool isWord(const string& s) {
    if (s.size() != 5) {
        return false;
    }
    for (char c : s) {
        if (c < 'A' || c > 'Z') {
            return false;
        }
    }
    return true;
}

string colorFor(const string& answer, const string& guess) {
    string result(5, 'B');
    vector<int> remaining(26, 0);

    for (int i = 0; i < 5; ++i) {
        if (answer[i] == guess[i]) {
            result[i] = 'G';
        } else {
            ++remaining[answer[i] - 'A'];
        }
    }

    for (int i = 0; i < 5; ++i) {
        if (result[i] == 'G') {
            continue;
        }
        int c = guess[i] - 'A';
        if (remaining[c] > 0) {
            result[i] = 'Y';
            --remaining[c];
        }
    }

    return result;
}

struct Output {
    bool impossible;
};

Output readOutput(InStream& stream) {
    string first = stream.readToken("[A-Z]+", "first output token");
    if (first == "IMPOSSIBLE") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after IMPOSSIBLE");
        }
        return {true};
    }

    if (!isWord(first)) {
        stream.quitf(_wa, "answer word must be five uppercase letters");
    }

    for (int i = 0; i < n; ++i) {
        string guess = stream.readToken("[A-Z]{5}", format("guess[%d]", i + 1).c_str());
        string actual = colorFor(first, guess);
        if (actual != expectedColors[i]) {
            stream.quitf(_wa,
                         "guess[%d] gives colors %s instead of %s",
                         i + 1,
                         actual.c_str(),
                         expectedColors[i].c_str());
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after witness");
    }
    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    expectedColors.resize(n);
    for (int i = 0; i < n; ++i) {
        expectedColors[i] = inf.readToken();
    }

    Output jury = readOutput(ans);
    Output participant = readOutput(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report IMPOSSIBLE");
        }
        quitf(_fail, "participant provided a valid witness while jury says IMPOSSIBLE");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports IMPOSSIBLE while jury provides a witness");
    }

    quitf(_ok, "participant witness is valid");
}
