#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    int m;
    int k;
    vector<vector<int>> wall;
};

struct Answer {
    bool possible;
};

string readVerdict(InStream& stream, int tc) {
    string token = stream.readToken();
    for (char& ch : token) {
        ch = char(toupper((unsigned char)ch));
    }
    if (token != "YES" && token != "NO") {
        stream.quitf(_wa, "test case %d: expected YES or NO, found '%s'", tc, token.c_str());
    }
    return token;
}

void validatePainting(InStream& stream, const TestCase& test, int tc) {
    vector<vector<int>> color(test.n, vector<int>(test.m));
    for (int i = 0; i < test.n; ++i) {
        for (int j = 0; j < test.m; ++j) {
            color[i][j] = stream.readInt(0, test.k, format("b[%d][%d] in test case %d", i + 1, j + 1, tc).c_str());
            if (test.wall[i][j] == 0) {
                if (color[i][j] != 0) {
                    stream.quitf(_wa,
                                 "test case %d: lamp at (%d, %d) has color %d",
                                 tc,
                                 i + 1,
                                 j + 1,
                                 color[i][j]);
                }
            } else if (color[i][j] == 0) {
                stream.quitf(_wa, "test case %d: tile at (%d, %d) is unpainted", tc, i + 1, j + 1);
            }
        }
    }

    vector<int> seen(test.k + 1, 0);
    int stamp = 0;
    for (int i = 0; i < test.n; ++i) {
        int j = 0;
        while (j < test.m) {
            if (test.wall[i][j] == 0) {
                ++j;
                continue;
            }
            ++stamp;
            while (j < test.m && test.wall[i][j] == 1) {
                int c = color[i][j];
                if (seen[c] == stamp) {
                    stream.quitf(_wa, "test case %d: repeated color %d in row segment at row %d", tc, c, i + 1);
                }
                seen[c] = stamp;
                ++j;
            }
        }
    }

    for (int j = 0; j < test.m; ++j) {
        int i = 0;
        while (i < test.n) {
            if (test.wall[i][j] == 0) {
                ++i;
                continue;
            }
            ++stamp;
            while (i < test.n && test.wall[i][j] == 1) {
                int c = color[i][j];
                if (seen[c] == stamp) {
                    stream.quitf(_wa, "test case %d: repeated color %d in column segment at column %d", tc, c, j + 1);
                }
                seen[c] = stamp;
                ++i;
            }
        }
    }
}

Answer readAnswer(InStream& stream, const TestCase& test, int tc) {
    string verdict = readVerdict(stream, tc);
    if (verdict == "NO") {
        return {false};
    }
    validatePainting(stream, test, tc);
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<TestCase> tests(t);
    for (int tc = 1; tc <= t; ++tc) {
        TestCase& test = tests[tc - 1];
        test.n = inf.readInt();
        test.m = inf.readInt();
        test.k = inf.readInt();
        test.wall.assign(test.n, vector<int>(test.m));
        for (int i = 0; i < test.n; ++i) {
            for (int j = 0; j < test.m; ++j) {
                test.wall[i][j] = inf.readInt();
            }
        }
    }

    for (int tc = 1; tc <= t; ++tc) {
        const TestCase& test = tests[tc - 1];
        Answer jury = readAnswer(ans, test, tc);
        Answer participant = readAnswer(ouf, test, tc);

        if (!jury.possible && participant.possible) {
            quitf(_fail, "test case %d: participant supplied a valid painting while jury says NO", tc);
        }
        if (jury.possible && !participant.possible) {
            quitf(_wa, "test case %d: jury has a painting but participant says NO", tc);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }
    quitf(_ok, "all %d test case(s) are valid", t);
}
