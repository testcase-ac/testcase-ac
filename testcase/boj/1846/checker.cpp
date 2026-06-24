#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;

struct Answer {
    bool impossible;
};

int parseColumnToken(const string& token, InStream& stream, const char* name) {
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name);
    }
    for (char ch : token) {
        if (ch < '0' || ch > '9') {
            stream.quitf(_wa, "%s is not an integer", name);
        }
    }

    int value = stoi(token);
    if (value < 1 || value > n) {
        stream.quitf(_wa, "%s is %d, expected value in [1, %d]", name, value, n);
    }
    return value;
}

Answer readAnswer(InStream& stream) {
    string first = stream.readToken("-1|[0-9]{1,6}", "answer[1] or -1");
    if (first == "-1") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<int> usedColumn(n + 1, 0);
    vector<int> column(n + 1, 0);

    column[1] = parseColumnToken(first, stream, "answer[1]");
    usedColumn[column[1]] = 1;

    for (int row = 2; row <= n; ++row) {
        column[row] = stream.readInt(1, n, format("answer[%d]", row).c_str());
        if (usedColumn[column[row]]) {
            stream.quitf(_wa, "column %d is used more than once", column[row]);
        }
        usedColumn[column[row]] = 1;
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after placement");
    }

    for (int row = 1; row <= n; ++row) {
        if (column[row] == row) {
            stream.quitf(_wa, "rook at row %d column %d is on the main diagonal", row, column[row]);
        }
        if (row + column[row] == n + 1) {
            stream.quitf(_wa, "rook at row %d column %d is on the anti-diagonal", row, column[row]);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(3, 100000, "N");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid placement while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible, but jury has a valid placement");
    }

    quitf(_ok, "valid placement for N=%d", n);
}
