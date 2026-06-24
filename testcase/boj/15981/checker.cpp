#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int n;

struct Answer {
    int tests;
};

Answer readAnswer(InStream& stream) {
    int tests = stream.readInt(0, 60, "K");
    stream.readEoln();

    vector<unsigned long long> signature(n + 1, 0);
    vector<int> seen(n + 1, 0);
    for (int test = 0; test < tests; ++test) {
        int count = stream.readInt(2, n, format("K_%d", test + 1).c_str());
        vector<int> touched;
        touched.reserve(count);
        for (int i = 0; i < count; ++i) {
            int button = stream.readInt(1, n, format("button[%d][%d]", test + 1, i + 1).c_str());
            if (seen[button]) {
                stream.quitf(_wa, "button %d appears more than once in test %d", button, test + 1);
            }
            seen[button] = 1;
            touched.push_back(button);
            signature[button] |= (1ULL << test);
        }
        stream.readEoln();
        for (int button : touched) {
            seen[button] = 0;
        }
    }
    stream.readEof();

    vector<unsigned long long> codes;
    codes.reserve(n);
    for (int button = 1; button <= n; ++button) {
        codes.push_back(signature[button]);
    }
    sort(codes.begin(), codes.end());
    for (int i = 1; i < n; ++i) {
        if (codes[i - 1] == codes[i]) {
            stream.quitf(_wa, "buttons are not uniquely identifiable");
        }
    }

    return {tests};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(3, 100000, "N");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.tests > jury.tests) {
        quitf(_wa, "jury uses fewer tests: jury=%d participant=%d", jury.tests, participant.tests);
    }
    if (participant.tests < jury.tests) {
        quitf(_fail, "participant found fewer tests: jury=%d participant=%d", jury.tests, participant.tests);
    }
    quitf(_ok, "answer uses %d tests", participant.tests);
}
