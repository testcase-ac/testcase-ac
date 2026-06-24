#include "testlib.h"
#include <vector>
using namespace std;

int n;
vector<int> available;

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n - 1, "answer[1]");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<int> used(n, 0);
    used[first]++;
    long long sum = first;

    for (int i = 1; i < n; ++i) {
        int value = stream.readInt(0, n - 1, format("answer[%d]", i + 1).c_str());
        used[value]++;
        sum += value;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after selected values");
    }

    for (int value = 0; value < n; ++value) {
        if (used[value] > available[value]) {
            stream.quitf(_wa,
                         "value %d is used %d times, but appears %d times in input",
                         value,
                         used[value],
                         available[value]);
        }
    }

    if (sum % n != 0) {
        stream.quitf(_wa, "selected values have sum %lld, which is not divisible by %d", sum, n);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    available.assign(n, 0);
    for (int i = 0; i < 2 * n - 1; ++i) {
        int value = inf.readInt();
        available[value]++;
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible && participant.impossible) {
        quitf(_ok, "both outputs claim no solution");
    }
    if (jury.impossible) {
        quitf(_fail, "participant found a valid witness while jury answer is -1");
    }
    if (participant.impossible) {
        quitf(_wa, "participant answered -1, but jury provides a valid witness");
    }

    quitf(_ok, "participant witness is valid");
}
