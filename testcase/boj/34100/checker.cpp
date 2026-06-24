#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    int m;
    vector<string> grid;
};

struct Answer {
    vector<bool> possible;
};

vector<TestCase> tests;

void requireCell(InStream& stream, vector<string>& out, int tc, int r, int c, char expected) {
    if (r < 0 || r >= (int)out.size() || c < 0 || c >= (int)out[r].size()) {
        stream.quitf(_wa, "testcase %d: block goes out of bounds at (%d, %d)", tc, r + 1, c + 1);
    }
    if (out[r][c] != expected) {
        stream.quitf(_wa,
                     "testcase %d: expected '%c' at (%d, %d), found '%c'",
                     tc,
                     expected,
                     r + 1,
                     c + 1,
                     out[r][c]);
    }
}

Answer readAnswer(InStream& stream) {
    Answer answer;
    answer.possible.resize(tests.size());

    for (int tc = 1; tc <= (int)tests.size(); ++tc) {
        const TestCase& test = tests[tc - 1];

        string first = stream.readToken();
        if (first == "-1") {
            answer.possible[tc - 1] = false;
            continue;
        }

        vector<string> out(test.n);
        out[0] = first;
        if ((int)out[0].size() != test.m) {
            stream.quitf(_wa,
                         "testcase %d: row 1 has length %d instead of %d",
                         tc,
                         (int)out[0].size(),
                         test.m);
        }
        for (int i = 1; i < test.n; ++i) {
            out[i] = stream.readToken();
            if ((int)out[i].size() != test.m) {
                stream.quitf(_wa,
                             "testcase %d: row %d has length %d instead of %d",
                             tc,
                             i + 1,
                             (int)out[i].size(),
                             test.m);
            }
        }

        for (int i = 0; i < test.n; ++i) {
            for (int j = 0; j < test.m; ++j) {
                char ch = out[i][j];
                if (test.grid[i][j] == '#') {
                    if (ch != '#') {
                        stream.quitf(_wa,
                                     "testcase %d: blocked cell (%d, %d) is output as '%c'",
                                     tc,
                                     i + 1,
                                     j + 1,
                                     ch);
                    }
                } else if (ch != 'a' && ch != 'b') {
                    stream.quitf(_wa,
                                 "testcase %d: empty cell (%d, %d) is output as '%c'",
                                 tc,
                                 i + 1,
                                 j + 1,
                                 ch);
                }
            }
        }

        for (int i = 0; i < test.n - 1; ++i) {
            for (int j = 0; j < test.m; ++j) {
                char ch = out[i][j];
                if (ch == '#') {
                    continue;
                }
                if (ch == 'a') {
                    requireCell(stream, out, tc, i + 1, j, 'a');
                    requireCell(stream, out, tc, i + 1, j + 1, 'a');
                    out[i][j] = out[i + 1][j] = out[i + 1][j + 1] = '#';
                } else if (ch == 'b') {
                    requireCell(stream, out, tc, i + 1, j - 1, 'b');
                    requireCell(stream, out, tc, i + 1, j, 'b');
                    out[i][j] = out[i + 1][j - 1] = out[i + 1][j] = '#';
                }
            }
        }

        for (int j = 0; j < test.m; ++j) {
            char ch = out[test.n - 1][j];
            if (ch != '#') {
                stream.quitf(_wa,
                             "testcase %d: cell (%d, %d) is not covered by a valid block",
                             tc,
                             test.n,
                             j + 1);
            }
        }

        answer.possible[tc - 1] = true;
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after all testcases");
    }
    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    tests.resize(t);
    for (int tc = 0; tc < t; ++tc) {
        tests[tc].n = inf.readInt();
        tests[tc].m = inf.readInt();
        tests[tc].grid.resize(tests[tc].n);
        for (int i = 0; i < tests[tc].n; ++i) {
            tests[tc].grid[i] = inf.readToken();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    for (int tc = 1; tc <= t; ++tc) {
        if (jury.possible[tc - 1] && !participant.possible[tc - 1]) {
            quitf(_wa, "testcase %d: jury provides a valid tiling, but participant reports impossible", tc);
        }
        if (!jury.possible[tc - 1] && participant.possible[tc - 1]) {
            quitf(_fail, "testcase %d: participant provides a valid tiling while jury reports impossible", tc);
        }
    }

    quitf(_ok, "participant output matches jury feasibility claims and all tilings are valid");
}
