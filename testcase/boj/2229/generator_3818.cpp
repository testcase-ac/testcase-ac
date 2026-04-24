#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of students
    int N = rnd.next(1, 10);
    // Choose a maximum score scale for diversity
    vector<int> maxOptions = {10, 100, 1000, 10000};
    int maxScore = rnd.any(maxOptions);
    // Generate random scores
    vector<int> scores(N);
    for (int i = 0; i < N; i++) {
        scores[i] = rnd.next(0, maxScore);
    }
    // Hyper-parameter: ordering regime
    // 0 = random, 1 = non-decreasing, 2 = non-increasing
    int regime = rnd.next(0, 2);
    if (regime == 1) {
        sort(scores.begin(), scores.end());
    } else if (regime == 2) {
        sort(scores.begin(), scores.end());
        reverse(scores.begin(), scores.end());
    }
    // Output
    println(N);
    println(scores);
    return 0;
}
