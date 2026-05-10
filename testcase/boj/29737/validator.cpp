#include "testlib.h"
#include <set>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and W
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int W = inf.readInt(1, 100, "W");
    inf.readEoln();

    set<string> nicknames;

    for (int friendIdx = 0; friendIdx < N; ++friendIdx) {
        // 2. Read nickname S
        string S = inf.readToken("[a-z]{1,100}", "S");
        inf.readEoln();

        // 3. Check for duplicate nicknames
        ensuref(nicknames.count(S) == 0, "Duplicate nickname found: %s", S.c_str());
        nicknames.insert(S);

        // 4. Read 7 lines, each of length W, only O/X/F allowed
        vector<string> streaks;
        for (int i = 0; i < 7; ++i) {
            string line = inf.readLine("[OXF]{"+to_string(W)+"}", "streak_line");
            ensuref((int)line.size() == W, "Line length for friend %s, day %d is not W=%d", S.c_str(), i+1, W);
            streaks.push_back(line);
        }
        ensuref((int)streaks.size() == 7, "Expected 7 streak lines for friend %s, got %d", S.c_str(), (int)streaks.size());

        // 5. Flatten to 1D vector for easier global checks (if needed)
        vector<char> days;
        for (int j = 0; j < W; ++j) {
            for (int i = 0; i < 7; ++i) {
                char c = streaks[i][j];
                ensuref(c == 'O' || c == 'X' || c == 'F', "Invalid character '%c' at week %d, day %d for friend %s", c, j+1, i+1, S.c_str());
                days.push_back(c);
            }
        }
        ensuref((int)days.size() == 7*W, "Total days for friend %s is not 7*W = %d", S.c_str(), 7*W);

        // No further global properties to check
    }

    inf.readEof();
}
