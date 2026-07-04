#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

namespace {

const string kIndentUnit = "   ";
const string kVars = "abcdefghijklmnopqrstuvwxyz";

string indent(int depth) {
    string result;
    for (int i = 0; i < depth; ++i) result += kIndentUnit;
    return result;
}

char var() {
    return kVars[rnd.next((int)kVars.size())];
}

string term() {
    int kind = rnd.next(4);
    if (kind == 0) return to_string(rnd.next(0, 999));
    if (kind == 1) return string(1, var());
    return to_string(rnd.next(0, 999)) + string(1, var());
}

string expr() {
    int terms = rnd.next(1, 4);
    string result = term();
    for (int i = 1; i < terms; ++i) {
        result += rnd.next(2) == 0 ? " + " : " - ";
        result += term();
    }
    return result;
}

void addAssignment(vector<string>& lines, int depth) {
    lines.push_back(indent(depth) + string(1, var()) + " = " + expr());
}

void addPrint(vector<string>& lines, int depth, int multiplier, int& printExecutions) {
    if (printExecutions + multiplier > 20) return;
    lines.push_back(indent(depth) + "PRINT " + string(1, var()));
    printExecutions += multiplier;
}

void addRandomStatements(vector<string>& lines, int depth, int multiplier,
                         int count, int& printExecutions) {
    for (int i = 0; i < count; ++i) {
        addAssignment(lines, depth);
        if (rnd.next(100) < 45) addPrint(lines, depth, multiplier, printExecutions);
    }
}

void addRepeatBlock(vector<string>& lines, int depth, int count,
                    int multiplier, int& printExecutions, bool nested) {
    lines.push_back(indent(depth) + "REPEAT " + to_string(count));
    int innerMultiplier = multiplier * count;
    addRandomStatements(lines, depth + 1, innerMultiplier, rnd.next(1, 3), printExecutions);
    if (nested) {
        int innerCount = rnd.next(2, 5);
        lines.push_back(indent(depth + 1) + "REPEAT " + to_string(innerCount));
        addRandomStatements(lines, depth + 2, innerMultiplier * innerCount,
                            rnd.next(1, 3), printExecutions);
        lines.push_back(indent(depth + 1) + "STOP");
    }
    addRandomStatements(lines, depth + 1, innerMultiplier, rnd.next(1, 3), printExecutions);
    lines.push_back(indent(depth) + "STOP");
}

void addModuloStress(vector<string>& lines, int& printExecutions) {
    char x = var();
    lines.push_back(indent(1) + string(1, x) + " = " + to_string(rnd.next(900, 999)));
    int repeatCount = rnd.next(50000, 100000);
    lines.push_back(indent(1) + "REPEAT " + to_string(repeatCount));
    lines.push_back(indent(2) + string(1, x) + " = " +
                    to_string(rnd.next(2, 999)) + string(1, x) +
                    " + " + to_string(rnd.next(0, 999)));
    lines.push_back(indent(1) + "STOP");
    addPrint(lines, 1, 1, printExecutions);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> lines;
    lines.push_back("BEGIN");

    int printExecutions = 0;
    int mode = rnd.next(4);

    addRandomStatements(lines, 1, 1, rnd.next(1, 4), printExecutions);

    if (mode == 0) {
        addRandomStatements(lines, 1, 1, rnd.next(5, 10), printExecutions);
    } else if (mode == 1) {
        addRepeatBlock(lines, 1, rnd.next(2, 6), 1, printExecutions, false);
    } else if (mode == 2) {
        addRepeatBlock(lines, 1, rnd.next(2, 4), 1, printExecutions, true);
    } else {
        addModuloStress(lines, printExecutions);
        addRepeatBlock(lines, 1, rnd.next(2, 4), 1, printExecutions, false);
    }

    while ((int)lines.size() < 49 && rnd.next(100) < 70) {
        if (rnd.next(100) < 75) {
            addAssignment(lines, 1);
        } else {
            addPrint(lines, 1, 1, printExecutions);
        }
    }

    if (printExecutions == 0) addPrint(lines, 1, 1, printExecutions);

    lines.push_back("STOP");
    for (const string& line : lines) println(line);

    return 0;
}
