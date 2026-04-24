#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of integers
    int n = rnd.next(1, 10);
    // Bias for generating small or large numbers
    int tBias = rnd.next(-2, 2);
    // Probability to insert a line break after each character
    double breakProb = rnd.next();

    // Generate n natural numbers in [1, 1e6]
    vector<string> nums;
    nums.reserve(n);
    for (int i = 0; i < n; i++) {
        // rnd.wnext(1000000, tBias) yields in [0,1e6-1], +1 to get [1,1e6]
        int x = rnd.wnext(1000000, tBias) + 1;
        nums.push_back(to_string(x));
    }

    // Build the full comma-separated string S
    string S;
    for (int i = 0; i < n; i++) {
        S += nums[i];
        if (i + 1 < n) S += ',';
    }

    // Split S into multiple lines randomly
    vector<string> lines;
    string cur;
    for (int i = 0; i < (int)S.size(); i++) {
        cur.push_back(S[i]);
        if (i + 1 < (int)S.size() && rnd.next() < breakProb) {
            lines.push_back(cur);
            cur.clear();
        }
    }
    if (!cur.empty()) {
        lines.push_back(cur);
    }

    // Output the lines
    for (auto &line : lines) {
        println(line);
    }
    return 0;
}
