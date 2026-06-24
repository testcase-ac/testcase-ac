#include "testlib.h"

#include <vector>

using namespace std;

int n, k, p;

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "first output token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }
    if (first < 1) {
        stream.quitf(_wa, "first insertion value must be -1 or in [1, %d], found %d", n, first);
    }

    vector<int> used(n + 1, 0);
    vector<int> heap(1, 0);
    vector<int> sequence(n);
    sequence[0] = first;

    for (int i = 1; i < n; ++i) {
        sequence[i] = stream.readInt(1, n, format("insertion[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after insertion sequence");
    }

    for (int i = 0; i < n; ++i) {
        int value = sequence[i];
        if (used[value]) {
            stream.quitf(_wa, "value %d is inserted more than once", value);
        }
        used[value] = 1;

        heap.push_back(value);
        int pos = (int)heap.size() - 1;
        while (pos > 1 && heap[pos] < heap[pos / 2]) {
            swap(heap[pos], heap[pos / 2]);
            pos /= 2;
        }
    }

    if (heap[p] != k) {
        stream.quitf(_wa, "after insertion heap[%d] is %d instead of %d", p, heap[p], k);
    }
    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 200000, "N");
    k = inf.readInt(1, n, "k");
    p = inf.readInt(1, n, "p");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both jury and participant report impossible");
        }
        quitf(_fail, "participant found a valid insertion sequence while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury provides a valid insertion sequence");
    }

    quitf(_ok, "valid insertion sequence");
}
