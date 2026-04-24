#include "testlib.h"
#include <vector>
using namespace std;

int N;
vector<int> A;

// Reads an answer (from either jury or contestant), checks its validity,
// and returns the length of the reported subsequence.
// On invalid subsequence, quits with _wa if stream==ouf, or _fail if stream==ans.
int readAns(InStream &stream) {
    // Read reported length
    int len = stream.readInt(1, N, "length of LIS");
    stream.readEoln();
    int last_val = -1;
    int last_pos = -1;  // position in A of the last matched element

    // Read and validate each element of the subsequence
    for (int i = 0; i < len; i++) {
        int v = stream.readInt(1, 1000, format("element[%d]", i+1).c_str());
        // Check strictly increasing
        if (i > 0 && v <= last_val) {
            stream.quitf(_wa, "subsequence is not strictly increasing at position %d: %d <= %d",
                         i+1, v, last_val);
        }
        // Check it appears as a subsequence in A
        bool found = false;
        for (int j = last_pos + 1; j < N; j++) {
            if (A[j] == v) {
                found = true;
                last_pos = j;
                break;
            }
        }
        if (!found) {
            stream.quitf(_wa, "value %d (subsequence[%d]) does not appear in the input sequence after position %d",
                         v, i+1, last_pos+1);
        }
        last_val = v;
    }

    return len;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    N = inf.readInt();
    A.resize(N);
    for (int i = 0; i < N; i++) {
        A[i] = inf.readInt();
    }

    // Read jury and contestant answers
    int jury_len = readAns(ans);
    int part_len = readAns(ouf);

    // Compare lengths
    if (part_len < jury_len) {
        quitf(_wa, "reported LIS length is too small: expected %d, found %d", jury_len, part_len);
    } else if (part_len > jury_len) {
        quitf(_fail, "participant found a longer subsequence than jury: jury %d vs participant %d",
              jury_len, part_len);
    } else {
        quitf(_ok, "correct LIS length = %d", part_len);
    }
}
