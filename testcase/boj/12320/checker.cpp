#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Target {
    long long x;
    long long y;
};

struct Answer {
    vector<string> moves;
};

void validateCasePrefix(InStream& stream, int caseIndex) {
    string word = stream.readToken();
    if (word != "Case") {
        stream.quitf(_wa, "case %d: expected 'Case', found '%s'", caseIndex, word.c_str());
    }

    string label = stream.readToken();
    string expected = format("#%d:", caseIndex);
    if (label != expected) {
        stream.quitf(_wa, "case %d: expected '%s', found '%s'",
                     caseIndex, expected.c_str(), label.c_str());
    }
}

string readMoveString(InStream& stream, int caseIndex) {
    return stream.readToken("[NSEW]+", format("moves for case %d", caseIndex).c_str());
}

long long validateMoves(InStream& stream, int caseIndex, const Target& target, const string& moves) {
    long long x = 0;
    long long y = 0;
    for (int i = 0; i < (int)moves.size(); ++i) {
        long long jump = i + 1;
        if (moves[i] == 'N') {
            y += jump;
        } else if (moves[i] == 'S') {
            y -= jump;
        } else if (moves[i] == 'E') {
            x += jump;
        } else if (moves[i] == 'W') {
            x -= jump;
        } else {
            stream.quitf(_wa, "case %d: invalid direction '%c' at move %d",
                         caseIndex, moves[i], i + 1);
        }
    }

    if (x != target.x || y != target.y) {
        stream.quitf(_wa,
                     "case %d: moves end at (%lld, %lld), expected (%lld, %lld)",
                     caseIndex, x, y, target.x, target.y);
    }
    return moves.size();
}

Answer readAnswer(InStream& stream, const vector<Target>& targets) {
    Answer answer;
    answer.moves.reserve(targets.size());

    for (int caseIndex = 1; caseIndex <= (int)targets.size(); ++caseIndex) {
        validateCasePrefix(stream, caseIndex);
        string moves = readMoveString(stream, caseIndex);
        validateMoves(stream, caseIndex, targets[caseIndex - 1], moves);
        answer.moves.push_back(moves);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after case %d", (int)targets.size());
    }
    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<Target> targets(t);
    for (int i = 0; i < t; ++i) {
        targets[i].x = inf.readLong();
        targets[i].y = inf.readLong();
    }

    Answer jury = readAnswer(ans, targets);
    Answer participant = readAnswer(ouf, targets);

    for (int i = 0; i < t; ++i) {
        int caseIndex = i + 1;
        int juryLength = jury.moves[i].size();
        int participantLength = participant.moves[i].size();

        if (participantLength > juryLength) {
            quitf(_wa, "case %d: participant uses %d moves, jury uses %d",
                  caseIndex, participantLength, juryLength);
        }
        if (participantLength < juryLength) {
            quitf(_fail, "case %d: participant uses %d moves, better than jury's %d",
                  caseIndex, participantLength, juryLength);
        }
    }

    quitf(_ok, "all %d case(s) reach the targets with jury-optimal lengths", t);
}
