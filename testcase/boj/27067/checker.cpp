#include "testlib.h"

#include <vector>

using namespace std;

int n;
vector<int> a;
vector<int> b;
vector<int> c;

struct Answer {
    vector<int> order;
    vector<int> moved;
};

bool isPermutation(const vector<int>& values) {
    vector<int> seen(n + 1, 0);
    for (int value : values) {
        if (value < 1 || value > n || seen[value]) return false;
        seen[value] = 1;
    }
    return true;
}

bool isForwardMoveFrom(const vector<int>& original, const vector<int>& transformed, int& moved) {
    int first = 0;
    while (first < n && original[first] == transformed[first]) ++first;
    if (first == n) return false;

    moved = transformed[first];
    vector<int> originalWithoutMoved;
    vector<int> transformedWithoutMoved;
    originalWithoutMoved.reserve(n - 1);
    transformedWithoutMoved.reserve(n - 1);

    int originalPos = -1;
    int transformedPos = -1;
    for (int i = 0; i < n; ++i) {
        if (original[i] == moved) {
            originalPos = i;
        } else {
            originalWithoutMoved.push_back(original[i]);
        }

        if (transformed[i] == moved) {
            transformedPos = i;
        } else {
            transformedWithoutMoved.push_back(transformed[i]);
        }
    }

    return transformedPos < originalPos && originalWithoutMoved == transformedWithoutMoved;
}

Answer readAnswer(InStream& stream) {
    Answer answer;
    answer.order.reserve(n);
    for (int i = 0; i < n; ++i) {
        answer.order.push_back(stream.readInt(1, n, format("order[%d]", i + 1).c_str()));
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }

    if (!isPermutation(answer.order)) {
        stream.quitf(_wa, "output is not a permutation of 1..%d", n);
    }

    answer.moved.assign(3, -1);
    if (!isForwardMoveFrom(answer.order, a, answer.moved[0])) {
        stream.quitf(_wa, "A cannot be obtained by moving exactly one stage forward");
    }
    if (!isForwardMoveFrom(answer.order, b, answer.moved[1])) {
        stream.quitf(_wa, "B cannot be obtained by moving exactly one stage forward");
    }
    if (!isForwardMoveFrom(answer.order, c, answer.moved[2])) {
        stream.quitf(_wa, "C cannot be obtained by moving exactly one stage forward");
    }

    if (answer.moved[0] == answer.moved[1] ||
        answer.moved[0] == answer.moved[2] ||
        answer.moved[1] == answer.moved[2]) {
        stream.quitf(_wa,
                     "moved stages are not distinct: A=%d B=%d C=%d",
                     answer.moved[0],
                     answer.moved[1],
                     answer.moved[2]);
    }

    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    a = inf.readInts(n, 1, n);
    b = inf.readInts(n, 1, n);
    c = inf.readInts(n, 1, n);

    readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok,
          "valid restoration; moved stages A=%d B=%d C=%d",
          participant.moved[0],
          participant.moved[1],
          participant.moved[2]);
}
