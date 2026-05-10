#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 200, "N");
    inf.readEoln();

    // 2. Read N x N adjacency matrix
    vector<vector<int>> cost(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        // Read the entire line as a string, then parse tokens
        string line = inf.readLine("[^]+", format("line %d", i+2).c_str());
        // Remove leading/trailing whitespace (shouldn't be any, but just in case)
        size_t start = line.find_first_not_of(" \t\r\n");
        size_t end = line.find_last_not_of(" \t\r\n");
        ensuref(start != string::npos, "Line %d is empty", i+2);
        line = line.substr(start, end - start + 1);

        // Split line into tokens
        vector<string> tokens;
        size_t pos = 0;
        while (pos < line.size()) {
            // Skip spaces
            while (pos < line.size() && isspace(line[pos])) ++pos;
            if (pos >= line.size()) break;
            size_t next = pos;
            // Find end of token
            while (next < line.size() && !isspace(line[next])) ++next;
            tokens.push_back(line.substr(pos, next - pos));
            pos = next;
        }
        ensuref((int)tokens.size() == N, "Line %d must contain exactly %d integers, found %d", i+2, N, (int)tokens.size());

        for (int j = 0; j < N; ++j) {
            // Parse integer
            string tok = tokens[j];
            // Check integer format: optional minus, digits, no leading zeros except "0"
            if (tok[0] == '-') {
                ensuref(tok.size() > 1, "Negative zero or lone minus not allowed at cost[%d][%d]", i+1, j+1);
                ensuref(tok[1] != '0' || tok == "-0", "Negative number with leading zero at cost[%d][%d]", i+1, j+1);
            } else {
                ensuref(tok[0] == '0' ? tok == "0" : (tok[0] >= '1' && tok[0] <= '9'), "Invalid leading digit at cost[%d][%d]", i+1, j+1);
                if (tok[0] == '0') ensuref(tok == "0", "Leading zero at cost[%d][%d]", i+1, j+1);
            }
            // Now parse
            int val = 0;
            bool neg = false;
            size_t k = 0;
            if (tok[0] == '-') {
                neg = true;
                k = 1;
            }
            for (; k < tok.size(); ++k) {
                ensuref(tok[k] >= '0' && tok[k] <= '9', "Non-digit character in cost[%d][%d]", i+1, j+1);
                val = val * 10 + (tok[k] - '0');
                ensuref(val <= 10000, "Absolute value too large at cost[%d][%d]", i+1, j+1);
            }
            if (neg) val = -val;

            // Range check
            if (i == j) {
                ensuref(val == 0, "Diagonal cost[%d][%d] must be 0, found %d", i+1, j+1, val);
            } else {
                ensuref(val != 0, "Off-diagonal cost[%d][%d] must not be 0", i+1, j+1);
                ensuref(val >= -10000 && val <= 10000, "cost[%d][%d] out of range [-10000,10000]", i+1, j+1);
            }
            cost[i][j] = val;
        }
    }

    // 3. Check symmetry: cost[i][j] == cost[j][i]
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            ensuref(cost[i][j] == cost[j][i],
                "Matrix is not symmetric: cost[%d][%d]=%d, cost[%d][%d]=%d",
                i+1, j+1, cost[i][j], j+1, i+1, cost[j][i]);
        }
    }

    inf.readEof();
}
