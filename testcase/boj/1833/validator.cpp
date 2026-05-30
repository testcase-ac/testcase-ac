#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 200, "N");
    inf.readEoln();

    vector<vector<int>> cost(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        string line = inf.readLine();
        ensuref(!line.empty(), "line %d must not be empty", i + 2);
        ensuref(line.back() != ' ', "trailing space on line %d", i + 2);

        vector<string> tokens;
        size_t pos = 0;
        while (pos < line.size()) {
            ensuref(line[pos] == ' ' || line[pos] == '-' || (line[pos] >= '0' && line[pos] <= '9'),
                    "invalid character on line %d", i + 2);
            while (pos < line.size() && line[pos] == ' ') {
                ++pos;
            }
            if (pos == line.size()) {
                break;
            }
            size_t next = pos;
            while (next < line.size() && line[next] != ' ') {
                ensuref(line[next] == '-' || (line[next] >= '0' && line[next] <= '9'),
                        "invalid character in token on line %d", i + 2);
                ++next;
            }
            tokens.push_back(line.substr(pos, next - pos));
            pos = next;
        }
        ensuref(
            static_cast<int>(tokens.size()) == N,
            "line %d must contain exactly %d integers, found %d",
            i + 2, N, static_cast<int>(tokens.size())
        );

        for (int j = 0; j < N; ++j) {
            string tok = tokens[j];
            int start = tok[0] == '-' ? 1 : 0;
            ensuref(start == 0 || tok.size() > 1, "lone minus at cost[%d][%d]", i + 1, j + 1);
            if (start == 1) {
                ensuref(tok[start] >= '1' && tok[start] <= '9', "negative cost[%d][%d] must not be signed zero", i + 1, j + 1);
            } else {
                ensuref(tok[start] == '0' ? tok.size() == static_cast<size_t>(start + 1) : tok[start] >= '1',
                        "leading zero at cost[%d][%d]", i + 1, j + 1);
            }

            int val = 0;
            for (size_t k = start; k < tok.size(); ++k) {
                ensuref(tok[k] >= '0' && tok[k] <= '9', "non-digit character in cost[%d][%d]", i + 1, j + 1);
                val = val * 10 + (tok[k] - '0');
                ensuref(val <= 10000, "absolute value too large at cost[%d][%d]", i + 1, j + 1);
            }
            if (start == 1) {
                val = -val;
            }

            if (i == j) {
                ensuref(val == 0, "diagonal cost[%d][%d] must be 0, found %d", i + 1, j + 1, val);
            } else {
                ensuref(val != 0, "off-diagonal cost[%d][%d] must not be 0", i + 1, j + 1);
            }
            cost[i][j] = val;
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            ensuref(
                cost[i][j] == cost[j][i],
                "matrix is not symmetric: cost[%d][%d]=%d, cost[%d][%d]=%d",
                i + 1, j + 1, cost[i][j], j + 1, i + 1, cost[j][i]
            );
        }
    }

    inf.readEof();
}
