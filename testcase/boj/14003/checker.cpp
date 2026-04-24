#include "testlib.h"
#include <vector>
using namespace std;

int N;
vector<long long> A;
const int MN = -1e9, MX = 1e9;


// Reads an answer (either jury or participant), checks its validity, and returns its length.
// On error: if stream == ouf, exits with _wa; if stream == ans, exits with _fail.
int readAns(InStream &stream) {
    // Read length of the subsequence
    int len = stream.readInt(1, N, "length of LIS");
    // Read the sequence values
    vector<long long> seq(len);
    for (int i = 0; i < len; i++) {
        seq[i] = stream.readInt(MN, MX, format("LIS[%d]", i+1).c_str());
    }
    // Check strictly increasing
    for (int i = 1; i < len; i++) {
        if (seq[i] <= seq[i-1]) {
            stream.quitf(_wa, "sequence is not strictly increasing at position %d: %lld followed by %lld",
                        i, seq[i-1], seq[i]);
        }
    }
    // Check subsequence property: each seq element appears in A in order
    int pos = 0;
    for (int i = 0; i < len; i++) {
        long long v = seq[i];
        while (pos < N && A[pos] != v) pos++;
        if (pos == N) {
            stream.quitf(_wa, "value %lld at position %d is not a subsequence of the input", v, i+1);
        }
        pos++;
    }
    return len;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input sequence
    N = inf.readInt();
    A.resize(N);
    for (int i = 0; i < N; i++) {
        A[i] = inf.readInt();
    }

    // Read jury and participant answers
    int juryLen = readAns(ans);
    int partLen = readAns(ouf);

    // Compare lengths
    if (partLen < juryLen) {
        quitf(_wa, "wrong length: expected %d, found %d", juryLen, partLen);
    } else if (partLen > juryLen) {
        // Participant claims a longer LIS than jury: impossible unless jury answer is wrong
        quitf(_fail, "participant found longer subsequence: jury %d, participant %d",
              juryLen, partLen);
    } else {
        quitf(_ok, "correct LIS length = %d", partLen);
    }
}
