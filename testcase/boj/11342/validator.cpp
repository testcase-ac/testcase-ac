#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

vector<string> splitLine(const string& line, int caseIndex) {
    ensuref(!line.empty(), "case %d line is empty", caseIndex);
    ensuref(line.front() != ' ', "case %d line has a leading space", caseIndex);
    ensuref(line.back() != ' ', "case %d line has a trailing space", caseIndex);

    vector<string> tokens;
    string current;
    for (char ch : line) {
        ensuref(ch == ' ' || ch == '/' || ch == 'X' || ('0' <= ch && ch <= '9'),
                "case %d has invalid character '%c'", caseIndex, ch);
        if (ch == ' ') {
            ensuref(!current.empty(), "case %d has repeated spaces", caseIndex);
            tokens.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    ensuref(!current.empty(), "case %d has an empty trailing token", caseIndex);
    tokens.push_back(current);
    return tokens;
}

bool isPinToken(const string& token) {
    return token.size() == 1 && '0' <= token[0] && token[0] <= '9';
}

int pinValue(const string& token) {
    return token[0] - '0';
}

void requirePinToken(const vector<string>& tokens, int index, int caseIndex) {
    ensuref(index < (int)tokens.size(), "case %d ended before token %d", caseIndex, index + 1);
    ensuref(isPinToken(tokens[index]), "case %d token %d must be a pin count from 0 to 9",
            caseIndex, index + 1);
}

int validateRegularFrame(const vector<string>& tokens, int index, int frame, int caseIndex) {
    ensuref(index < (int)tokens.size(), "case %d ended before frame %d", caseIndex, frame);
    if (tokens[index] == "X") {
        return index + 1;
    }

    requirePinToken(tokens, index, caseIndex);
    int first = pinValue(tokens[index]);

    ensuref(index + 1 < (int)tokens.size(), "case %d ended inside frame %d", caseIndex, frame);
    if (tokens[index + 1] == "/") {
        return index + 2;
    }

    requirePinToken(tokens, index + 1, caseIndex);
    int second = pinValue(tokens[index + 1]);
    ensuref(first + second < 10, "case %d frame %d open frame knocks down %d pins",
            caseIndex, frame, first + second);
    return index + 2;
}

int validateTenthFrame(const vector<string>& tokens, int index, int caseIndex) {
    ensuref(index < (int)tokens.size(), "case %d ended before frame 10", caseIndex);

    if (tokens[index] == "X") {
        ensuref(index + 1 < (int)tokens.size(), "case %d ended after tenth-frame strike", caseIndex);
        if (tokens[index + 1] == "X") {
            ensuref(index + 2 < (int)tokens.size(), "case %d ended after two tenth-frame strikes",
                    caseIndex);
            ensuref(tokens[index + 2] == "X" || isPinToken(tokens[index + 2]),
                    "case %d third tenth-frame token after two strikes must be X or a pin count",
                    caseIndex);
            return index + 3;
        }

        requirePinToken(tokens, index + 1, caseIndex);
        int second = pinValue(tokens[index + 1]);
        ensuref(index + 2 < (int)tokens.size(), "case %d ended inside tenth frame", caseIndex);
        if (tokens[index + 2] == "/") {
            return index + 3;
        }
        requirePinToken(tokens, index + 2, caseIndex);
        int third = pinValue(tokens[index + 2]);
        ensuref(second + third < 10, "case %d tenth frame after strike has invalid open pair %d",
                caseIndex, second + third);
        return index + 3;
    }

    requirePinToken(tokens, index, caseIndex);
    int first = pinValue(tokens[index]);
    ensuref(index + 1 < (int)tokens.size(), "case %d ended inside tenth frame", caseIndex);

    if (tokens[index + 1] == "/") {
        ensuref(index + 2 < (int)tokens.size(), "case %d ended after tenth-frame spare", caseIndex);
        ensuref(tokens[index + 2] == "X" || isPinToken(tokens[index + 2]),
                "case %d tenth-frame spare bonus must be X or a pin count", caseIndex);
        return index + 3;
    }

    requirePinToken(tokens, index + 1, caseIndex);
    int second = pinValue(tokens[index + 1]);
    ensuref(first + second < 10, "case %d tenth-frame open pair knocks down %d pins",
            caseIndex, first + second);
    return index + 2;
}

void validateGameLine(const string& line, int caseIndex) {
    vector<string> tokens = splitLine(line, caseIndex);
    int index = 0;
    for (int frame = 1; frame <= 9; ++frame) {
        index = validateRegularFrame(tokens, index, frame, caseIndex);
    }
    index = validateTenthFrame(tokens, index, caseIndex);
    ensuref(index == (int)tokens.size(), "case %d has extra tokens after frame 10", caseIndex);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no game-count bound; this local cap keeps inputs inspectable
    // while allowing the maximum default aggregate of 100000 bowling games.
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);
        string line = inf.readLine("[^]{1,1000}", "game");
        validateGameLine(line, caseIndex);
    }

    inf.readEof();
}
