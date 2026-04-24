#include "testlib.h"
#include <map>
#include <vector>
#include <utility>
using namespace std;

int N;
map<pair<int,int>, int> freq;

// Reads an answer (jury or participant), checks its validity, computes and returns its length.
// On invalid output: if stream == ouf (participant) -> _wa; if stream == ans (jury) -> _fail.
int readAns(InStream &stream) {
    // Read the length K of the sequence
    int K = stream.readInt(1, N, "K");
    // Local copy of frequencies to track usage
    map<pair<int,int>, int> f = freq;
    vector<pair<int,int>> seq;
    seq.reserve(K);

    // Read intervals
    for (int i = 0; i < K; i++) {
        int a = stream.readInt(1, 1000000, format("A[%d]", i+1).c_str());
        int b = stream.readInt(1, 1000000, format("B[%d]", i+1).c_str());
        // Check a < b
        if (a >= b) {
            stream.quitf(_wa, "interval %d is invalid: [%d, %d], require A < B", i+1, a, b);
        }
        // Check it exists in input and not overused
        pair<int,int> p = make_pair(a, b);
        if (f[p] == 0) {
            stream.quitf(_wa, "interval %d = [%d, %d] not in input or used more times than given", i+1, a, b);
        }
        f[p]--;
        seq.push_back(p);
    }

    // Check nesting condition: each interval must contain the next
    for (int i = 1; i < K; i++) {
        auto &prev = seq[i-1];
        auto &cur  = seq[i];
        // prev.first <= cur.first  AND  cur.second <= prev.second
        if (prev.first > cur.first || prev.second < cur.second) {
            stream.quitf(_wa,
                "interval %d = [%d, %d] is not contained in previous [%d, %d]",
                i+1, cur.first, cur.second, prev.first, prev.second);
        }
    }

    return K;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input intervals
    N = inf.readInt();
    for (int i = 0; i < N; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        freq[make_pair(a,b)]++;
    }

    // Read and validate jury and participant answers
    int juryLen = readAns(ans);
    int partLen = readAns(ouf);

    // Compare lengths
    if (juryLen > partLen) {
        quitf(_wa, "jury's sequence is longer: %d vs %d", juryLen, partLen);
    } else if (juryLen < partLen) {
        quitf(_fail, "participant's sequence is longer than jury: %d vs %d", partLen, juryLen);
    } else {
        quitf(_ok, "correct length = %d", partLen);
    }
}
