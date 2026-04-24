#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

int readAns(InStream& stream, int A, int B, int testCase) {
    string output = stream.readLine();

    int n = A;

    for (size_t i = 0; i < output.size(); i++) {
        char cmd = output[i];

        if (cmd == 'D') {
            n = (n * 2) % 10000;
        } else if (cmd == 'S') {
            n = (n == 0) ? 9999 : n - 1;
        } else if (cmd == 'L') {
            string nStr = format("%04d", n);
            nStr = nStr.substr(1) + nStr[0];
            n = stoi(nStr);
        } else if (cmd == 'R') {
            string nStr = format("%04d", n);
            nStr = nStr.back() + nStr.substr(0, 3);
            n = stoi(nStr);
        } else {
            stream.quitf(_wa, "Case #%d: Invalid command '%c' at position %d", testCase, cmd, int(i + 1));
        }
    }

    if (n != B) {
        stream.quitf(_wa, "Case #%d: Final value %d does not match target %d", testCase, n, B);
    }

    return output.size();
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt();

    vector<int> A(T), B(T);

    for (int testCase = 0; testCase < T; testCase++) {
        A[testCase] = inf.readInt();
        B[testCase] = inf.readInt();
    }

    for (int testCase = 0; testCase < T; testCase++) {
        int jLength = readAns(ans, A[testCase], B[testCase], testCase + 1);
        int pLength = readAns(ouf, A[testCase], B[testCase], testCase + 1);

        if (pLength > jLength) {
            quitf(_wa, "Case #%d: Participant's sequence is longer than minimal length (%d > %d)", testCase + 1, pLength, jLength);
        } else if (pLength == jLength) {
            // Correct for this test case
            continue;
        } else { // pLength < jLength
            quitf(_fail, "Case #%d: Participant's sequence is shorter than jury's minimal length (%d < %d)", testCase + 1, pLength, jLength);
        }
    }

    quitf(_ok, "%d test cases passed.", T);
}
