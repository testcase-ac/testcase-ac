#include "testlib.h"

#include <vector>

using namespace std;

int n;

long long countSiftSwaps(vector<int> heap) {
    long long swaps = 0;

    for (int heapSize = n; heapSize >= 2; --heapSize) {
        swap(heap[1], heap[heapSize]);

        int current = 1;
        int limit = heapSize - 1;
        while (true) {
            int left = current * 2;
            if (left > limit) {
                break;
            }

            int child = left;
            int right = left + 1;
            if (right <= limit && heap[right] > heap[left]) {
                child = right;
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

struct Answer {
    long long swaps;
};

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
            stream.quitf(_wa,
                         "heap property fails at index %d: parent=%d left child=%d",
                         i,
                         heap[i],
                         heap[left]);
        }
        if (right <= n && heap[i] <= heap[right]) {
            stream.quitf(_wa,
                         "heap property fails at index %d: parent=%d right child=%d",
                         i,
                         heap[i],
                         heap[right]);
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
        quitf(_wa,
              "participant heap has fewer sift swaps: participant=%lld jury=%lld",
              participant.swaps,
              jury.swaps);
    }
    if (participant.swaps > jury.swaps) {
        quitf(_fail,
              "participant heap has more sift swaps than jury: participant=%lld jury=%lld",
              participant.swaps,
              jury.swaps);
    }

    quitf(_ok, "sift swaps=%lld", participant.swaps);
}
