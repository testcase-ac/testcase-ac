#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of problems
    int N = rnd.next(1, 10);

    // Hyper-parameter: choose maximum operand value from a small set
    vector<int> maxOptions = {0, 10, 100, 1000};
    int maxVal = rnd.any(maxOptions);

    // Hyper-parameter: probability of a P=NP problem
    double pSkip = rnd.next(0.0, 1.0);

    vector<string> lines;
    bool hasSum = false, hasSkip = false;
    // Generate each line
    for (int i = 0; i < N; i++) {
        if (rnd.next() < pSkip) {
            lines.push_back("P=NP");
            hasSkip = true;
        } else {
            int a = rnd.next(0, maxVal);
            int b = rnd.next(0, maxVal);
            lines.push_back(to_string(a) + "+" + to_string(b));
            hasSum = true;
        }
    }

    // Ensure at least one sum problem
    if (!hasSum) {
        int idx = rnd.next(0, N - 1);
        int a = rnd.next(0, maxVal);
        int b = rnd.next(0, maxVal);
        lines[idx] = to_string(a) + "+" + to_string(b);
        hasSum = true;
    }
    // If possible, ensure at least one P=NP problem
    if (!hasSkip && N >= 2) {
        int idx;
        do {
            idx = rnd.next(0, N - 1);
        } while (lines[idx] == "P=NP");
        lines[idx] = "P=NP";
        hasSkip = true;
    }

    // Shuffle order for randomness
    shuffle(lines.begin(), lines.end());

    // Output
    println(N);
    for (auto &s : lines) {
        println(s);
    }
    return 0;
}
