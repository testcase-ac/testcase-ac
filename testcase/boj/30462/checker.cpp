#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int N;
vector<int> B;

// Reads an answer from 'stream'. If the answer is "No", returns an empty vector.
// If the answer is "Yes", reads a permutation A of length N, checks it's a valid
// permutation and that for each i, mex(A[0..i]) == B[i]. On error, quits with
// _wa (if stream==ouf) or _fail (if stream==ans).
vector<int> readAns(InStream& stream) {
    string verdict = stream.readToken();
    if (verdict == "No") {
        return vector<int>();  // empty means "No"
    } else if (verdict == "Yes") {
        vector<int> A(N);
        vector<bool> used(N+1, false);
        // Read the permutation
        for (int i = 0; i < N; i++) {
            A[i] = stream.readInt(1, N, format("A[%d]", i+1).c_str());
            if (used[A[i]]) {
                stream.quitf(_wa, "value %d is used more than once", A[i]);
            }
            used[A[i]] = true;
        }
        // Check mex for each prefix
        vector<bool> seen(N+2, false);
        int currMex = 1;
        for (int i = 0; i < N; i++) {
            seen[A[i]] = true;
            while (seen[currMex]) currMex++;
            int expect = B[i];
            if (currMex != expect) {
                stream.quitf(_wa,
                    "mex for prefix of length %d is %d instead of %d",
                    i+1, currMex, expect);
            }
        }
        return A;
    } else {
        stream.quitf(_wa, "expected 'Yes' or 'No', found '%s'", verdict.c_str());
    }
    return vector<int>(); // unreachable
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    N = inf.readInt();
    B.resize(N);
    for (int i = 0; i < N; i++) {
        B[i] = inf.readInt();
    }
    // Read jury and participant answers
    vector<int> jur = readAns(ans);
    vector<int> part = readAns(ouf);

    // Compare
    if (jur.empty()) {
        // Jury says No
        if (part.empty()) {
            quitf(_ok, "Both say No");
        } else {
            quitf(_wa, "Jury says No but participant printed Yes");
        }
    } else {
        // Jury has a solution
        if (part.empty()) {
            quitf(_wa, "Participant says No but solution exists");
        } else {
            quitf(_ok, "OK");
        }
    }
    return 0;
}
