#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define int long long
vector<int> values;

// Function to read and validate the answer from a given stream (jury or participant).
int readAns(InStream& stream) {
    // Read three integers as the solution from the stream
    vector<int> solution(3);
    solution[0] = stream.readInt(-1000000000, 1000000000, "solution[0]");
    solution[1] = stream.readInt(-1000000000, 1000000000, "solution[1]");
    solution[2] = stream.readInt(-1000000000, 1000000000, "solution[2]");
    
    // Ensure the solution is sorted in ascending order.
    if (!(solution[0] < solution[1] && solution[1] < solution[2])) {
        stream.quitf(_wa, "Solution is not in ascending order.");
    }

    // Ensure all values are distinct and present in the input.
    for (int i = 0; i < 3; i++) {
        if (find(values.begin(), values.end(), solution[i]) == values.end()) {
            stream.quitf(_wa, "Value %d is not present in the input array.", solution[i]);
        }
    }

    // Calculate and return the absolute sum of the solution.
    int sum = solution[0] + solution[1] + solution[2];
    return abs(sum);
}

int32_t main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Reading input values from the input file.
    int n = inf.readInt(3, 5000, "N");
    values.resize(n);
    for (int i = 0; i < n; i++) {
        values[i] = inf.readInt(-1000000000, 1000000000, "value");
    }

    // Reading and validating the jury's answer.
    int juryAns = readAns(ans);

    // Reading and validating the contestant's answer.
    int participantAns = readAns(ouf);

    // Compare the sums.
    if (juryAns < participantAns) {
        quitf(_wa, "Jury has a better answer: juryAns = %lld, participantAns = %lld", juryAns, participantAns);
    } else if (juryAns == participantAns) {
        quitf(_ok, "Correct answer: sum = %lld", participantAns);
    } else {
        quitf(_fail, "Participant has a better answer: juryAns = %lld, participantAns = %lld", juryAns, participantAns);
    }

    return 0;
}
