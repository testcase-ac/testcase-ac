#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Target {
    int x;
    int y;
};

struct Answer {
    vector<string> moves;
};

int testCount;
vector<Target> targets;

Answer readAnswer(InStream& stream, TResult invalidResult) {
    Answer answer;
    answer.moves.reserve(testCount);

    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        string caseWord = stream.readToken();
        if (caseWord != "Case") {
            stream.quitf(invalidResult,
                         "case %d: expected 'Case', found '%s'",
                         caseIndex,
                         caseWord.c_str());
        }

        string caseNumber = stream.readToken();
        string expectedCaseNumber = format("#%d:", caseIndex);
        if (caseNumber != expectedCaseNumber) {
            stream.quitf(invalidResult,
                         "case %d: expected '%s', found '%s'",
                         caseIndex,
                         expectedCaseNumber.c_str(),
                         caseNumber.c_str());
        }

        string moves = stream.readToken();
        if (moves.size() > 500) {
            stream.quitf(invalidResult,
                         "case %d: move string has length %zu, exceeding 500",
                         caseIndex,
                         moves.size());
        }

        long long x = 0;
        long long y = 0;
        for (int i = 0; i < (int)moves.size(); ++i) {
            int distance = i + 1;
            char direction = moves[i];
            if (direction == 'N') {
                y += distance;
            } else if (direction == 'S') {
                y -= distance;
            } else if (direction == 'E') {
                x += distance;
            } else if (direction == 'W') {
                x -= distance;
            } else {
                stream.quitf(invalidResult,
                             "case %d: invalid direction '%c' at move %d",
                             caseIndex,
                             direction,
                             i + 1);
            }
        }

        const Target& target = targets[caseIndex - 1];
        if (x != target.x || y != target.y) {
            stream.quitf(invalidResult,
                         "case %d: moves end at (%lld, %lld), expected (%d, %d)",
                         caseIndex,
                         x,
                         y,
                         target.x,
                         target.y);
        }

        answer.moves.push_back(moves);
        stream.readEoln();
    }

    stream.readEof();
    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    testCount = inf.readInt();
    targets.reserve(testCount);
    for (int i = 0; i < testCount; ++i) {
        int x = inf.readInt();
        int y = inf.readInt();
        targets.push_back({x, y});
    }

    readAnswer(ans, _fail);
    readAnswer(ouf, _wa);

    quitf(_ok,
          "%d valid case%s; participant lengths match small-dataset bound",
          testCount,
          testCount == 1 ? "" : "s");
}
