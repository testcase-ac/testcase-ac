#include "testlib.h"

#include <array>
#include <string>
#include <vector>

using namespace std;

struct Claim {
    bool impossible;
    int moves;
};

array<vector<int>, 7> graphEdges() {
    array<vector<int>, 7> edges;
    for (int i = 0; i < 6; ++i) {
        edges[i].push_back((i + 5) % 6);
        edges[i].push_back((i + 1) % 6);
        edges[i].push_back(6);
        edges[6].push_back(i);
    }
    return edges;
}

bool adjacent(const array<vector<int>, 7>& edges, int from, int to) {
    for (int next : edges[from]) {
        if (next == to) {
            return true;
        }
    }
    return false;
}

Claim readClaim(InStream& stream,
                TResult invalidResult,
                const string& initial,
                const array<vector<int>, 7>& edges,
                int caseIndex) {
    string first = stream.readToken();
    if (first == "-1") {
        return {true, -1};
    }

    int moveCount = 0;
    try {
        size_t parsed = 0;
        moveCount = stoi(first, &parsed);
        if (parsed != first.size()) {
            stream.quitf(invalidResult, "case %d has malformed move count '%s'", caseIndex, first.c_str());
        }
    } catch (...) {
        stream.quitf(invalidResult, "case %d has malformed move count '%s'", caseIndex, first.c_str());
    }

    if (moveCount < 0) {
        stream.quitf(invalidResult, "case %d has negative move count %d", caseIndex, moveCount);
    }

    string moves;
    if (moveCount > 0) {
        moves = stream.readToken();
    }
    if (static_cast<int>(moves.size()) != moveCount) {
        stream.quitf(invalidResult,
                     "case %d move count is %d but move string length is %d",
                     caseIndex,
                     moveCount,
                     static_cast<int>(moves.size()));
    }

    array<char, 7> board;
    array<int, 6> position;
    for (int i = 0; i < 6; ++i) {
        int token = initial[i] - 'A';
        board[i] = initial[i];
        position[token] = i;
    }
    board[6] = '.';
    int empty = 6;

    for (int i = 0; i < moveCount; ++i) {
        char moved = moves[i];
        if (moved < 'A' || moved > 'F') {
            stream.quitf(invalidResult, "case %d move %d uses invalid token '%c'", caseIndex, i + 1, moved);
        }
        int token = moved - 'A';
        int from = position[token];
        if (!adjacent(edges, from, empty)) {
            stream.quitf(invalidResult,
                         "case %d move %d token %c cannot move from position %d to empty position %d",
                         caseIndex,
                         i + 1,
                         moved,
                         from + 1,
                         empty == 6 ? 7 : empty + 1);
        }

        swap(board[from], board[empty]);
        position[token] = empty;
        empty = from;
    }

    for (int i = 0; i < 6; ++i) {
        if (board[i] != static_cast<char>('A' + i)) {
            stream.quitf(invalidResult,
                         "case %d sequence ends with token %c at position %d",
                         caseIndex,
                         board[i],
                         i + 1);
        }
    }
    if (empty != 6) {
        stream.quitf(invalidResult, "case %d sequence does not leave the center empty", caseIndex);
    }

    return {false, moveCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int tests = inf.readInt();
    vector<string> initial(tests);
    for (int i = 0; i < tests; ++i) {
        initial[i] = inf.readToken();
    }

    const auto edges = graphEdges();
    for (int i = 0; i < tests; ++i) {
        Claim jury = readClaim(ans, _fail, initial[i], edges, i + 1);
        Claim participant = readClaim(ouf, _wa, initial[i], edges, i + 1);

        if (jury.impossible) {
            if (!participant.impossible) {
                quitf(_fail, "case %d participant found a valid solution but jury says -1", i + 1);
            }
            continue;
        }

        if (participant.impossible) {
            quitf(_wa, "case %d has a jury solution of length %d but participant says -1", i + 1, jury.moves);
        }
        if (participant.moves < jury.moves) {
            quitf(_fail,
                  "case %d participant found shorter solution: participant=%d jury=%d",
                  i + 1,
                  participant.moves,
                  jury.moves);
        }
        if (participant.moves > jury.moves) {
            quitf(_wa,
                  "case %d solution is not shortest: participant=%d jury=%d",
                  i + 1,
                  participant.moves,
                  jury.moves);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }
    quitf(_ok, "all %d case(s) match the jury baseline", tests);
}
