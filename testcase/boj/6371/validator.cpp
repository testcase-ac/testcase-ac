#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

namespace {

bool isDiagramChar(char ch) {
    return ch == ' ' || ch == '-' || ch == '|' || ch == '+' || ch == ':' ||
           ch == '\\' || ch == ')' || ch == '>' || ch == '/' || ch == 'o' ||
           ch == '?' || ('A' <= ch && ch <= 'Z');
}

bool hasNonSpace(const string& line) {
    for (char ch : line) {
        if (ch != ' ') {
            return true;
        }
    }
    return false;
}

void validateDiagramLine(const string& line, int circuitIndex, int lineIndex) {
    ensuref(!line.empty(), "empty diagram line in circuit %d at line %d",
            circuitIndex, lineIndex);
    ensuref(line.size() <= 100, "diagram line too long in circuit %d at line %d: %d",
            circuitIndex, lineIndex, int(line.size()));
    ensuref(line.back() != ' ', "trailing space in circuit %d at diagram line %d",
            circuitIndex, lineIndex);
    ensuref(hasNonSpace(line), "blank diagram line in circuit %d at line %d",
            circuitIndex, lineIndex);

    for (int i = 0; i < int(line.size()); ++i) {
        ensuref(isDiagramChar(line[i]),
                "invalid diagram character in circuit %d at line %d column %d: %d",
                circuitIndex, lineIndex, i + 1, int(static_cast<unsigned char>(line[i])));
    }
}

void validateStateLine(const string& line, int circuitIndex, int stateIndex) {
    ensuref(line.size() == 26,
            "input state in circuit %d at index %d must have exactly 26 bits, got %d",
            circuitIndex, stateIndex, int(line.size()));
    for (int i = 0; i < 26; ++i) {
        ensuref(line[i] == '0' || line[i] == '1',
                "input state in circuit %d at index %d has invalid bit at position %d",
                circuitIndex, stateIndex, i + 1);
    }
}

void validateCircuitMarkers(const vector<string>& diagram, int circuitIndex) {
    // CHECK: The statement promises well-formed paths and gates; this validator
    // enforces the block format, bounds, alphabet, input presence, and unique
    // output marker without implementing a full circuit-topology parser.
    int inputLabels = 0;
    int outputs = 0;
    for (int r = 0; r < int(diagram.size()); ++r) {
        for (int c = 0; c < int(diagram[r].size()); ++c) {
            char ch = diagram[r][c];
            if ('A' <= ch && ch <= 'Z') {
                ++inputLabels;
            } else if (ch == '?') {
                ++outputs;
            }
        }
    }

    ensuref(inputLabels >= 1, "circuit %d must contain at least one logic input",
            circuitIndex);
    ensuref(outputs == 1, "circuit %d must contain exactly one output marker, got %d",
            circuitIndex, outputs);
}

}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int circuitIndex = 0;
    while (!inf.eof()) {
        ++circuitIndex;
        vector<string> diagram;

        while (true) {
            string line = inf.readLine();
            if (line == "*") {
                break;
            }
            ensuref(int(diagram.size()) < 100,
                    "circuit %d has more than 100 diagram lines", circuitIndex);
            validateDiagramLine(line, circuitIndex, int(diagram.size()) + 1);
            diagram.push_back(line);
        }

        ensuref(!diagram.empty(), "circuit %d has no diagram lines", circuitIndex);
        validateCircuitMarkers(diagram, circuitIndex);

        int stateCount = 0;
        while (true) {
            string line = inf.readLine();
            if (line == "*") {
                break;
            }
            ++stateCount;
            validateStateLine(line, circuitIndex, stateCount);
        }
        ensuref(stateCount >= 1, "circuit %d has no input state lines", circuitIndex);
    }

    ensuref(circuitIndex >= 1, "input must contain at least one circuit");
    inf.readEof();
}
