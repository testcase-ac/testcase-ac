#include "testlib.h"

#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct TestCase {
    int r;
    int c;
    vector<string> inputGrid;
    set<char> originalLetters;
};

vector<TestCase> tests;

void readInput() {
    int t = inf.readInt();
    tests.resize(t);

    for (int tc = 0; tc < t; ++tc) {
        TestCase& cur = tests[tc];
        cur.r = inf.readInt();
        cur.c = inf.readInt();
        cur.inputGrid.resize(cur.r);

        for (int i = 0; i < cur.r; ++i) {
            cur.inputGrid[i] = inf.readToken();
            for (char ch : cur.inputGrid[i]) {
                if (ch != '?') {
                    cur.originalLetters.insert(ch);
                }
            }
        }
    }
}

void readCaseHeader(InStream& stream, int tc) {
    string caseWord = stream.readToken("Case", format("case[%d] label", tc).c_str());
    string number = stream.readToken(format("#%d:", tc).c_str(),
                                     format("case[%d] number", tc).c_str());
    (void)caseWord;
    (void)number;
}

void validateRectangles(InStream& stream,
                        int tc,
                        const TestCase& cur,
                        const vector<string>& grid) {
    map<char, int> minRow;
    map<char, int> maxRow;
    map<char, int> minCol;
    map<char, int> maxCol;
    map<char, int> count;

    for (char ch : cur.originalLetters) {
        minRow[ch] = cur.r;
        maxRow[ch] = -1;
        minCol[ch] = cur.c;
        maxCol[ch] = -1;
        count[ch] = 0;
    }

    for (int i = 0; i < cur.r; ++i) {
        for (int j = 0; j < cur.c; ++j) {
            char ch = grid[i][j];
            if (!cur.originalLetters.count(ch)) {
                stream.quitf(_wa,
                             "case %d row %d column %d uses letter %c not present in input",
                             tc,
                             i + 1,
                             j + 1,
                             ch);
            }
            if (cur.inputGrid[i][j] != '?' && cur.inputGrid[i][j] != ch) {
                stream.quitf(_wa,
                             "case %d row %d column %d changed original letter %c to %c",
                             tc,
                             i + 1,
                             j + 1,
                             cur.inputGrid[i][j],
                             ch);
            }

            minRow[ch] = min(minRow[ch], i);
            maxRow[ch] = max(maxRow[ch], i);
            minCol[ch] = min(minCol[ch], j);
            maxCol[ch] = max(maxCol[ch], j);
            ++count[ch];
        }
    }

    for (char ch : cur.originalLetters) {
        int height = maxRow[ch] - minRow[ch] + 1;
        int width = maxCol[ch] - minCol[ch] + 1;
        if (count[ch] != height * width) {
            stream.quitf(_wa,
                         "case %d letter %c does not form a rectangle",
                         tc,
                         ch);
        }
    }
}

void readAnswer(InStream& stream) {
    for (int tc = 1; tc <= (int)tests.size(); ++tc) {
        const TestCase& cur = tests[tc - 1];
        readCaseHeader(stream, tc);
        stream.readEoln();

        vector<string> grid(cur.r);
        for (int i = 0; i < cur.r; ++i) {
            grid[i] = stream.readToken("[A-Z]+", format("case[%d] row[%d]", tc, i + 1).c_str());
            if ((int)grid[i].size() != cur.c) {
                stream.quitf(_wa,
                             "case %d row %d has length %d, expected %d",
                             tc,
                             i + 1,
                             (int)grid[i].size(),
                             cur.c);
            }
            stream.readEoln();
        }

        validateRectangles(stream, tc, cur, grid);
    }

    stream.readEof();
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    readInput();
    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid alphabet cake assignment");
}
