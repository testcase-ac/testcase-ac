#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N;
vector<int> solutions;

pair<int, int> readAns(InStream& stream) {
    // Read two integers from the stream
    int ans1 = stream.readInt(-1000000000, 1000000000, "ans1");
    int ans2 = stream.readInt(-1000000000, 1000000000, "ans2");

    // Ensure the numbers are distinct
    if (ans1 == ans2) {
        stream.quitf(_wa, "The two output numbers must be distinct.");
    }

    // Ensure they are in ascending order
    if (ans1 > ans2) {
        stream.quitf(_wa, "The two output numbers must be in ascending order.");
    }

    // Check if both numbers are present in the input
    if (!binary_search(solutions.begin(), solutions.end(), ans1)) {
        stream.quitf(_wa, "The number %d is not in the input array.", ans1);
    }

    if (!binary_search(solutions.begin(), solutions.end(), ans2)) {
        stream.quitf(_wa, "The number %d is not in the input array.", ans2);
    }

    return make_pair(ans1, ans2);
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Reading input
    N = inf.readInt(); // Read the number of solutions
    solutions.resize(N);
    for (int i = 0; i < N; i++) {
        solutions[i] = inf.readInt(-1000000000, 1000000000, "solutions[i]");
    }

    // Sort the solutions for easier validation and searching
    sort(solutions.begin(), solutions.end());

    // Reading the answers
    pair<int, int> jans = readAns(ans);  // Jury's answer
    pair<int, int> pans = readAns(ouf);  // Participant's answer

    // Calculate the sum for both answers
    int jury_sum = abs(jans.first + jans.second);
    int participant_sum = abs(pans.first + pans.second);

    // Determine which solution is better
    if (jury_sum < participant_sum) {
        quitf(_wa, "jury has the better answer: jury_sum = %d, participant_sum = %d", jury_sum, participant_sum);
    } else if (jury_sum == participant_sum) {
        quitf(_ok, "answer is correct: sum = %d", participant_sum);
    } else {
        quitf(_fail, ":( participant has the better answer: jury_sum = %d, participant_sum = %d", jury_sum, participant_sum);
    }

    return 0;
}
