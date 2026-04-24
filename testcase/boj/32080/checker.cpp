#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int N;
vector<int> C_in;

// Reads an answer from 'stream' (jury or participant).
// Returns 0 if the answer is "-1" (impossible),
// or 1 if a valid solution (A, B) is read and its merge matches C_in.
// On invalid format or incorrect merge, quits with _wa (for ouf) or _fail (for ans).
int readAns(InStream& stream) {
    // Read the first integer: either -1 or the first element of A.
    int first = stream.readInt(-1, 2*N, "first value");
    if (first == -1) {
        // Answer claims impossible
        return 0;
    }
    // Otherwise, read A and B arrays.
    vector<int> A(N), B(N);
    A[0] = first;
    for (int i = 1; i < N; i++) {
        A[i] = stream.readInt(1, 2*N, format("A[%d]", i+1).c_str());
    }
    for (int i = 0; i < N; i++) {
        B[i] = stream.readInt(1, 2*N, format("B[%d]", i+1).c_str());
    }
    // Simulate the merge procedure.
    vector<int> merged;
    merged.reserve(2*N);
    int i = 0, j = 0;
    while (i < N && j < N) {
        if (A[i] < B[j]) {
            merged.push_back(A[i++]);
        } else {
            merged.push_back(B[j++]);
        }
    }
    while (i < N) merged.push_back(A[i++]);
    while (j < N) merged.push_back(B[j++]);
    // Check that the merged result equals the input C_in.
    for (int k = 0; k < 2*N; k++) {
        if (merged[k] != C_in[k]) {
            stream.quitf(_wa,
                "at position %d expected %d but got %d in merged array",
                k+1, C_in[k], merged[k]);
        }
    }
    return 1;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input C from inf.
    N = inf.readInt();
    C_in.resize(2*N);
    for (int i = 0; i < 2*N; i++) {
        C_in[i] = inf.readInt();
    }
    // Read jury and participant answers.
    int jans = readAns(ans);
    int pans = readAns(ouf);
    // Compare existence flags.
    if (jans > pans) {
        // Jury says possible, participant says impossible.
        quitf(_wa, "output is -1 but a solution exists");
    } else if (jans == pans) {
        // Both agree on possibility/impossibility and validation passed.
        quitf(_ok, ""); 
    } else {
        // Participant found a solution but jury says impossible => judge data bug.
        quitf(_fail, "participant found a solution but jury says impossible");
    }
}
