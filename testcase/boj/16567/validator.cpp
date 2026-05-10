#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    // 2. Read N binary values
    vector<int> state = inf.readInts(N, 0, 1, "initial_state");
    inf.readEoln();

    // 3. Read M queries
    for (int q = 0; q < M; ++q) {
        string line = inf.readLine("[^]+", "trial_line");
        // Remove leading/trailing spaces (shouldn't be any, but let's check)
        ensuref(!line.empty(), "Trial line %d is empty", q+1);

        if (line == "0") {
            // ok
        } else {
            // Should be "1 i"
            // Check format: must be "1 <space> i" and nothing else
            // Split by space
            size_t space_pos = line.find(' ');
            ensuref(space_pos != string::npos, "Trial line %d: Expected space in '1 i' format", q+1);
            string first = line.substr(0, space_pos);
            string second = line.substr(space_pos+1);
            ensuref(first == "1", "Trial line %d: Expected '1' as first token, got '%s'", q+1, first.c_str());
            // No extra spaces allowed
            ensuref(second.find(' ') == string::npos, "Trial line %d: Extra spaces detected in '1 i' format", q+1);
            // Parse i
            ensuref(!second.empty(), "Trial line %d: Missing index after '1'", q+1);
            // Check that second is a valid integer in [1, N], no leading zeros unless "0"
            ensuref(second.size() <= 7, "Trial line %d: Index too long", q+1); // 1,000,000 is 7 digits
            // Check all digits
            for (char c : second) {
                ensuref('0' <= c && c <= '9', "Trial line %d: Index contains non-digit: '%s'", q+1, second.c_str());
            }
            // No leading zeros unless "0"
            ensuref(second == "0" || second[0] != '0', "Trial line %d: Index has leading zeros: '%s'", q+1, second.c_str());
            int idx = atoi(second.c_str());
            ensuref(1 <= idx && idx <= N, "Trial line %d: Index %d out of range [1, %d]", q+1, idx, N);
        }
    }

    inf.readEof();
}
