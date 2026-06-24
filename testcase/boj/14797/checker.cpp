#include "testlib.h"

#include <algorithm>
#include <array>
#include <string>
#include <vector>

using namespace std;

struct CaseInput {
    int rows;
    int cols;
    vector<string> grid;
    array<bool, 26> originalLetters;
};

struct Answer {
    vector<vector<string>> grids;
};

void readCaseHeader(InStream& stream, int tc) {
    string actual = stream.readToken();
    if (actual != "Case") {
        stream.quitf(_wa, "case %d header starts with '%s' instead of 'Case'", tc, actual.c_str());
    }
    string marker = stream.readToken();
    if (marker != format("#%d:", tc)) {
        stream.quitf(_wa, "case %d header marker is '%s' instead of '#%d:'", tc, marker.c_str(), tc);
    }
    stream.readEoln();
}

Answer readAnswer(InStream& stream, const vector<CaseInput>& cases) {
    Answer answer;
    answer.grids.reserve(cases.size());

    for (int tc = 1; tc <= (int)cases.size(); ++tc) {
        const CaseInput& input = cases[tc - 1];
        readCaseHeader(stream, tc);

        vector<string> output(input.rows);
        for (int r = 0; r < input.rows; ++r) {
            output[r] = stream.readToken(format("[A-Z]{%d}", input.cols).c_str(),
                                         format("case %d row %d", tc, r + 1).c_str());
            stream.readEoln();
            if ((int)output[r].size() != input.cols) {
                stream.quitf(_wa,
                             "case %d row %d has length %d instead of %d",
                             tc,
                             r + 1,
                             (int)output[r].size(),
                             input.cols);
            }
            for (int c = 0; c < input.cols; ++c) {
                char ch = output[r][c];
                if (ch < 'A' || ch > 'Z') {
                    stream.quitf(_wa,
                                 "case %d row %d column %d contains '%c', expected uppercase letter",
                                 tc,
                                 r + 1,
                                 c + 1,
                                 ch);
                }
                if (!input.originalLetters[ch - 'A']) {
                    stream.quitf(_wa,
                                 "case %d row %d column %d uses new letter '%c'",
                                 tc,
                                 r + 1,
                                 c + 1,
                                 ch);
                }
                if (input.grid[r][c] != '?' && input.grid[r][c] != ch) {
                    stream.quitf(_wa,
                                 "case %d row %d column %d changed original letter '%c' to '%c'",
                                 tc,
                                 r + 1,
                                 c + 1,
                                 input.grid[r][c],
                                 ch);
                }
            }
        }

        for (int letter = 0; letter < 26; ++letter) {
            if (!input.originalLetters[letter]) {
                continue;
            }

            char ch = char('A' + letter);
            int minRow = input.rows;
            int maxRow = -1;
            int minCol = input.cols;
            int maxCol = -1;
            int count = 0;

            for (int r = 0; r < input.rows; ++r) {
                for (int c = 0; c < input.cols; ++c) {
                    if (output[r][c] == ch) {
                        minRow = min(minRow, r);
                        maxRow = max(maxRow, r);
                        minCol = min(minCol, c);
                        maxCol = max(maxCol, c);
                        ++count;
                    }
                }
            }

            if (count == 0) {
                stream.quitf(_wa, "case %d omits original letter '%c'", tc, ch);
            }

            for (int r = minRow; r <= maxRow; ++r) {
                for (int c = minCol; c <= maxCol; ++c) {
                    if (output[r][c] != ch) {
                        stream.quitf(_wa,
                                     "case %d letter '%c' is not a filled rectangle; row %d column %d contains '%c'",
                                     tc,
                                     ch,
                                     r + 1,
                                     c + 1,
                                     output[r][c]);
                    }
                }
            }
        }

        answer.grids.push_back(output);
    }

    stream.readEof();
    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = inf.readInt();
    vector<CaseInput> cases;
    cases.reserve(testCount);

    for (int tc = 1; tc <= testCount; ++tc) {
        CaseInput input;
        input.rows = inf.readInt();
        input.cols = inf.readInt();
        input.originalLetters.fill(false);
        input.grid.resize(input.rows);

        for (int r = 0; r < input.rows; ++r) {
            input.grid[r] = inf.readToken();
            for (int c = 0; c < input.cols; ++c) {
                char ch = input.grid[r][c];
                if (ch >= 'A' && ch <= 'Z') {
                    input.originalLetters[ch - 'A'] = true;
                }
            }
        }

        cases.push_back(input);
    }

    Answer jury = readAnswer(ans, cases);
    Answer participant = readAnswer(ouf, cases);
    if (jury.grids.size() != participant.grids.size()) {
        quitf(_fail, "internal checker error while comparing parsed answers");
    }

    quitf(_ok, "participant output is a valid filled cake");
}
