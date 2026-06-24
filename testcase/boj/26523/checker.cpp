#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

constexpr int TEST_CASES = 100;
constexpr int REQUIRED_CORRECT = 99;

vector<string> readAnswer(InStream& stream) {
    vector<string> labels;
    labels.reserve(TEST_CASES);

    for (int i = 0; i < TEST_CASES; ++i) {
        labels.push_back(stream.readToken("[AB]", format("answer[%d]", i + 1).c_str()));
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d answers", TEST_CASES);
    }

    return labels;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    vector<string> jury = readAnswer(ans);
    vector<string> participant = readAnswer(ouf);

    int matches = 0;
    for (int i = 0; i < TEST_CASES; ++i) {
        if (participant[i] == jury[i]) {
            ++matches;
        }
    }

    if (matches < REQUIRED_CORRECT) {
        quitf(_wa, "only %d of %d answers match the jury baseline", matches, TEST_CASES);
    }

    quitf(_ok, "%d of %d answers match the jury baseline", matches, TEST_CASES);
}
