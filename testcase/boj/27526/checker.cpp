#include "testlib.h"

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int n, m, cells;
vector<char> expectedChars;

int factorial(int x) {
    int result = 1;
    for (int i = 2; i <= x; ++i) {
        result *= i;
    }
    return result;
}

string readBoard(InStream& stream, int index) {
    string board;
    board.reserve(cells);

    vector<int> seen(256, 0);
    for (int r = 0; r < n; ++r) {
        string row = stream.readToken();
        if ((int)row.size() != m) {
            stream.quitf(_wa,
                         "state %d row %d has length %d instead of %d",
                         index + 1,
                         r + 1,
                         (int)row.size(),
                         m);
        }
        stream.readEoln();

        for (char ch : row) {
            if (find(expectedChars.begin(), expectedChars.end(), ch) == expectedChars.end()) {
                stream.quitf(_wa, "state %d contains invalid character '%c'", index + 1, ch);
            }
            if (seen[(unsigned char)ch]) {
                stream.quitf(_wa, "state %d repeats character '%c'", index + 1, ch);
            }
            seen[(unsigned char)ch] = 1;
            board.push_back(ch);
        }
    }

    for (char ch : expectedChars) {
        if (!seen[(unsigned char)ch]) {
            stream.quitf(_wa, "state %d is missing character '%c'", index + 1, ch);
        }
    }

    return board;
}

bool adjacent(int a, int b) {
    int ar = a / m;
    int ac = a % m;
    int br = b / m;
    int bc = b % m;
    return abs(ar - br) + abs(ac - bc) == 1;
}

void validateTransition(InStream& stream, const string& previous, const string& current, int index) {
    vector<int> diff;
    for (int i = 0; i < cells; ++i) {
        if (previous[i] != current[i]) {
            diff.push_back(i);
        }
    }

    if (diff.size() != 2) {
        stream.quitf(_wa,
                     "transition to state %d changes %d cells instead of swapping two adjacent cells",
                     index + 1,
                     (int)diff.size());
    }
    if (!adjacent(diff[0], diff[1])) {
        stream.quitf(_wa,
                     "transition to state %d swaps non-adjacent cells %d and %d",
                     index + 1,
                     diff[0] + 1,
                     diff[1] + 1);
    }
    if (previous[diff[0]] != current[diff[1]] || previous[diff[1]] != current[diff[0]]) {
        stream.quitf(_wa, "transition to state %d is not a swap", index + 1);
    }
}

struct Claim {
    int states;
};

Claim readClaim(InStream& stream) {
    int totalStates = factorial(cells);
    vector<string> boards;
    boards.reserve(totalStates);
    unordered_set<string> seenBoards;
    seenBoards.reserve(totalStates * 2);

    string initial;
    initial.reserve(cells);
    for (int i = 0; i < cells; ++i) {
        initial.push_back(i + 1 == cells ? '#' : char('1' + i));
    }

    for (int state = 0; state < totalStates; ++state) {
        string board = readBoard(stream, state);
        if (state == 0) {
            if (board != initial) {
                stream.quitf(_wa, "first state is not the initial puzzle state");
            }
        } else {
            validateTransition(stream, boards.back(), board, state);
        }
        if (seenBoards.find(board) != seenBoards.end()) {
            stream.quitf(_wa, "state %d repeats a previous board", state + 1);
        }
        seenBoards.insert(board);
        boards.push_back(board);
    }

    stream.readEof();
    return {totalStates};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    cells = n * m;

    for (int i = 0; i < cells - 1; ++i) {
        expectedChars.push_back(char('1' + i));
    }
    expectedChars.push_back('#');

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.states != jury.states) {
        quitf(_wa,
              "participant printed %d states, jury printed %d states",
              participant.states,
              jury.states);
    }
    quitf(_ok, "valid sequence with %d states", participant.states);
}
