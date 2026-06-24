#include "testlib.h"

#include <vector>

using namespace std;

int n;

struct Answer {
    long long swaps;
};

long long countSiftSwaps(vector<int> heap) {
    long long swaps = 0;
    for (int size = n; size >= 2; --size) {
        swap(heap[1], heap[size]);
        int current = 1;
        int limit = size - 1;
        while (true) {
            int child = current * 2;
            if (child > limit) {
                break;
            }
            if (child + 1 <= limit && heap[child + 1] > heap[child]) {
                ++child;
            }
            if (heap[current] > heap[child]) {
                break;
            }
            swap(heap[current], heap[child]);
            ++swaps;
            current = child;
        }
    }
    return swaps;
}

Answer readAnswer(InStream& stream) {
    vector<int> heap(n + 1);
    vector<int> seen(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        heap[i] = stream.readInt(1, n, format("heap[%d]", i).c_str());
        if (seen[heap[i]]) {
            stream.quitf(_wa, "value %d appears more than once", heap[i]);
        }
        seen[heap[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after heap");
    }

    for (int i = 1; i <= n; ++i) {
        int left = i * 2;
        int right = left + 1;
        if (left <= n && heap[i] <= heap[left]) {
            stream.quitf(_wa, "heap[%d]=%d is not greater than left child heap[%d]=%d",
                         i, heap[i], left, heap[left]);
        }
        if (right <= n && heap[i] <= heap[right]) {
            stream.quitf(_wa, "heap[%d]=%d is not greater than right child heap[%d]=%d",
                         i, heap[i], right, heap[right]);
        }
    }

    return {countSiftSwaps(heap)};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100000, "n");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.swaps < jury.swaps) {
        quitf(_wa, "jury has better answer: jury=%lld participant=%lld",
              jury.swaps, participant.swaps);
    }
    if (participant.swaps > jury.swaps) {
        quitf(_fail, "participant found better answer: jury=%lld participant=%lld",
              jury.swaps, participant.swaps);
    }
    quitf(_ok, "answer uses %lld sift swaps", participant.swaps);
}
