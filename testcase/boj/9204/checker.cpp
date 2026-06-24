#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Position {
    int col;
    int row;
};

struct TestCase {
    Position start;
    Position finish;
};

struct Answer {
    bool impossible;
};

vector<TestCase> cases;

bool samePosition(Position a, Position b) {
    return a.col == b.col && a.row == b.row;
}

bool sameDiagonal(Position a, Position b) {
    return abs(a.col - b.col) == abs(a.row - b.row);
}

string formatPosition(Position p) {
    string result;
    result += char('A' + p.col - 1);
    result += ' ';
    result += char('0' + p.row);
    return result;
}

Position readPosition(InStream& stream, int caseIndex, int index) {
    string col = stream.readWord("[A-H]", format("case %d position %d column", caseIndex, index).c_str());
    int row = stream.readInt(1, 8, format("case %d position %d row", caseIndex, index).c_str());
    return {col[0] - 'A' + 1, row};
}

Answer readAnswer(InStream& stream, int caseIndex) {
    string first = stream.readWord("Impossible|[0-4]", format("case %d first token", caseIndex).c_str());
    const TestCase& tc = cases[caseIndex - 1];

    if (first == "Impossible") {
        return {true};
    }

    int moves = first[0] - '0';
    vector<Position> path;
    path.reserve(moves + 1);
    for (int i = 0; i <= moves; ++i) {
        path.push_back(readPosition(stream, caseIndex, i + 1));
    }

    if (!samePosition(path.front(), tc.start)) {
        stream.quitf(_wa,
                     "case %d: path starts at %s instead of %s",
                     caseIndex,
                     formatPosition(path.front()).c_str(),
                     formatPosition(tc.start).c_str());
    }
    if (!samePosition(path.back(), tc.finish)) {
        stream.quitf(_wa,
                     "case %d: path ends at %s instead of %s",
                     caseIndex,
                     formatPosition(path.back()).c_str(),
                     formatPosition(tc.finish).c_str());
    }
    for (int i = 0; i < moves; ++i) {
        if (samePosition(path[i], path[i + 1])) {
            stream.quitf(_wa,
                         "case %d: consecutive positions %d and %d are equal",
                         caseIndex,
                         i + 1,
                         i + 2);
        }
        if (!sameDiagonal(path[i], path[i + 1])) {
            stream.quitf(_wa,
                         "case %d: move %d from %s to %s is not diagonal",
                         caseIndex,
                         i + 1,
                         formatPosition(path[i]).c_str(),
                         formatPosition(path[i + 1]).c_str());
        }
    }

    return {false};
}

void readInput() {
    int tests = inf.readInt();
    cases.reserve(tests);
    for (int i = 0; i < tests; ++i) {
        string startCol = inf.readWord();
        int startRow = inf.readInt();
        string finishCol = inf.readWord();
        int finishRow = inf.readInt();
        cases.push_back({{startCol[0] - 'A' + 1, startRow}, {finishCol[0] - 'A' + 1, finishRow}});
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    readInput();

    for (int caseIndex = 1; caseIndex <= (int)cases.size(); ++caseIndex) {
        Answer jury = readAnswer(ans, caseIndex);
        Answer participant = readAnswer(ouf, caseIndex);

        if (jury.impossible && participant.impossible) {
            continue;
        }
        if (!jury.impossible && participant.impossible) {
            quitf(_wa, "case %d: jury provides a path, but participant reports Impossible", caseIndex);
        }
        if (jury.impossible && !participant.impossible) {
            quitf(_fail, "case %d: participant provides a valid path while jury reports Impossible", caseIndex);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    quitf(_ok, "all %d case(s) match the jury baseline", (int)cases.size());
}
