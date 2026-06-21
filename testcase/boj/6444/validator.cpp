#include "testlib.h"

#include <climits>
#include <cctype>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct Formula {
    int cell;
    vector<int> refs;
};

static bool isCanonicalInteger(const string& s) {
    int pos = 0;
    if (s.empty()) return false;
    if (s[0] == '-') {
        if (s.size() == 1) return false;
        pos = 1;
    }
    if (s[pos] == '0') return pos + 1 == (int)s.size();
    for (int i = pos; i < (int)s.size(); ++i) {
        if (!isdigit((unsigned char)s[i])) return false;
    }
    return true;
}

static long long parseInteger(const string& s) {
    long long sign = 1;
    int pos = 0;
    if (s[0] == '-') {
        sign = -1;
        pos = 1;
    }
    long long value = 0;
    for (int i = pos; i < (int)s.size(); ++i) {
        value = value * 10 + (s[i] - '0');
    }
    return sign * value;
}

static int parseColumn(const string& letters) {
    int value = 0;
    for (char ch : letters) {
        value = value * 26 + (ch - 'A' + 1);
    }
    return value;
}

static int parseCellName(const string& name, int maxColumns, int maxRows) {
    int pos = 0;
    while (pos < (int)name.size() && name[pos] >= 'A' && name[pos] <= 'Z') {
        ++pos;
    }

    ensuref(1 <= pos && pos <= 3, "cell reference has invalid column letters: %s", name.c_str());
    ensuref(pos < (int)name.size(), "cell reference has no row number: %s", name.c_str());

    string letters = name.substr(0, pos);
    string rowText = name.substr(pos);
    ensuref(isCanonicalInteger(rowText), "cell reference has invalid row number: %s", name.c_str());

    int column = parseColumn(letters);
    long long row = parseInteger(rowText);
    ensuref(1 <= column && column <= 18278, "cell reference column out of global bounds: %s", name.c_str());
    ensuref(1 <= row && row <= 999, "cell reference row out of global bounds: %s", name.c_str());
    ensuref(column <= maxColumns && row <= maxRows, "cell reference outside spreadsheet: %s", name.c_str());

    return (int)(row - 1) * maxColumns + (column - 1);
}

static vector<int> parseFormula(const string& token, int maxColumns, int maxRows) {
    ensuref(token.size() >= 2 && token[0] == '=', "invalid formula token: %s", token.c_str());

    vector<int> refs;
    int start = 1;
    for (int i = 1; i <= (int)token.size(); ++i) {
        if (i == (int)token.size() || token[i] == '+') {
            ensuref(start < i, "formula has an empty cell reference: %s", token.c_str());
            refs.push_back(parseCellName(token.substr(start, i - start), maxColumns, maxRows));
            start = i + 1;
        } else {
            ensuref((token[i] >= 'A' && token[i] <= 'Z') || isdigit((unsigned char)token[i]),
                    "formula has invalid character in token: %s", token.c_str());
        }
    }

    return refs;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int columns = inf.readInt(1, 18278, "M");
        inf.readSpace();
        int rows = inf.readInt(1, 999, "N");
        inf.readEoln();

        long long cellCount = 1LL * columns * rows;
        ensuref(cellCount <= 1700000LL, "test case has too many cells: %lld", cellCount);

        vector<long long> values(cellCount, 0);
        vector<unsigned char> isFormula(cellCount, 0);
        vector<int> formulaIndex(cellCount, -1);
        vector<Formula> formulas;
        long long referenceCount = 0;

        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < columns; ++column) {
                string token = inf.readToken("[^ ]+", "cell");
                int cell = row * columns + column;

                if (!token.empty() && token[0] == '=') {
                    vector<int> refs = parseFormula(token, columns, rows);
                    referenceCount += (long long)refs.size();
                    ensuref(referenceCount <= 250000LL, "test case has too many formula references: %lld", referenceCount);
                    isFormula[cell] = 1;
                    formulaIndex[cell] = (int)formulas.size();
                    formulas.push_back({cell, refs});
                } else {
                    ensuref(isCanonicalInteger(token), "cell value is not a canonical integer: %s", token.c_str());
                    long long value = parseInteger(token);
                    ensuref(-100000LL <= value && value <= 100000LL, "cell value out of bounds: %lld", value);
                    values[cell] = value;
                }

                if (column + 1 == columns) {
                    inf.readEoln();
                } else {
                    inf.readSpace();
                }
            }
        }

        vector<vector<int>> dependents(formulas.size());
        vector<int> pendingFormulaRefs(formulas.size(), 0);

        for (int i = 0; i < (int)formulas.size(); ++i) {
            for (int ref : formulas[i].refs) {
                if (isFormula[ref]) {
                    int refIndex = formulaIndex[ref];
                    ++pendingFormulaRefs[i];
                    dependents[refIndex].push_back(i);
                } else {
                    values[formulas[i].cell] += values[ref];
                }
            }
        }

        queue<int> ready;
        for (int i = 0; i < (int)formulas.size(); ++i) {
            if (pendingFormulaRefs[i] == 0) ready.push(i);
        }

        int resolved = 0;
        while (!ready.empty()) {
            int formula = ready.front();
            ready.pop();
            ++resolved;

            long long value = values[formulas[formula].cell];
            ensuref(value <= INT_MAX, "formula value exceeds 2^31-1 at formula index %d", formula + 1);

            for (int dependent : dependents[formula]) {
                values[formulas[dependent].cell] += value;
                --pendingFormulaRefs[dependent];
                if (pendingFormulaRefs[dependent] == 0) {
                    ready.push(dependent);
                }
            }
        }

        ensuref(resolved == (int)formulas.size(), "formula dependency graph contains a cycle");
    }

    inf.readEof();
}
