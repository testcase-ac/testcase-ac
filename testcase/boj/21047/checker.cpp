#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Answer {
    bool impossible;
};

int n;
vector<string> original;

long long parseNumber(const string& value) {
    long long result = 0;
    for (char ch : value) {
        result = result * 10 + (ch - '0');
    }
    return result;
}

bool isDigits(const string& value) {
    if (value.empty()) {
        return false;
    }
    for (char ch : value) {
        if (ch < '0' || ch > '9') {
            return false;
        }
    }
    return true;
}

Answer readAnswer(InStream& stream) {
    string first = stream.readToken("[0-9]+|impossible", "answer[1]");
    if (first == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {true};
    }

    vector<string> answer(n);
    answer[0] = first;
    for (int i = 1; i < n; ++i) {
        answer[i] = stream.readToken("[0-9]+", format("answer[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer array");
    }

    int changedIndex = -1;
    int changedDigitCount = 0;
    for (int i = 0; i < n; ++i) {
        if (!isDigits(answer[i])) {
            stream.quitf(_wa, "answer[%d] is not a nonnegative integer", i + 1);
        }
        if (answer[i].size() > 1 && answer[i][0] == '0') {
            stream.quitf(_wa, "answer[%d] has a leading zero", i + 1);
        }
        if (answer[i].size() != original[i].size()) {
            stream.quitf(_wa,
                         "answer[%d] changes length from %d to %d",
                         i + 1,
                         int(original[i].size()),
                         int(answer[i].size()));
        }

        int localDiffs = 0;
        for (size_t j = 0; j < answer[i].size(); ++j) {
            if (answer[i][j] != original[i][j]) {
                ++localDiffs;
            }
        }
        if (localDiffs > 0) {
            if (changedIndex != -1) {
                stream.quitf(_wa,
                             "more than one number was changed: answer[%d] and answer[%d]",
                             changedIndex + 1,
                             i + 1);
            }
            changedIndex = i;
            changedDigitCount = localDiffs;
        }
    }

    if (changedIndex == -1) {
        stream.quitf(_wa, "no digit was changed");
    }
    if (changedDigitCount != 1) {
        stream.quitf(_wa,
                     "answer[%d] changes %d digits instead of one",
                     changedIndex + 1,
                     changedDigitCount);
    }

    bool unsorted = false;
    for (int i = 0; i + 1 < n; ++i) {
        if (parseNumber(answer[i]) > parseNumber(answer[i + 1])) {
            unsorted = true;
            break;
        }
    }
    if (!unsorted) {
        stream.quitf(_wa, "changed array is still nondecreasing");
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    original.resize(n);
    for (int i = 0; i < n; ++i) {
        original[i] = inf.readToken();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "jury and participant both report impossible");
        }
        quitf(_fail, "participant provided a valid witness while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid witness but participant reports impossible");
    }

    quitf(_ok, "valid changed unsorted array");
}
