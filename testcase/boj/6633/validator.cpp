#include "testlib.h"

#include <array>
#include <string>

using namespace std;

const int kPoints[10][6] = {
    {1, 1, 1, 1, 1, 1},
    {0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
};

const int kBars[10][7] = {
    {1, 1, 1, 0, 1, 1, 1},
    {0, 0, 1, 0, 0, 1, 0},
    {1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {0, 1, 1, 1, 0, 1, 0},
    {1, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1},
};

const int kBarIndex[7][5] = {
    {-1, 0, 0, 0, -1},
    {1, -1, -1, -1, 2},
    {1, -1, -1, -1, 2},
    {-1, 3, 3, 3, -1},
    {4, -1, -1, -1, 5},
    {4, -1, -1, -1, 5},
    {-1, 6, 6, 6, -1},
};

bool matchesCell(char scanned, char expected) {
    return scanned == '.' || scanned == expected;
}

bool isAllowedDisplayChar(char ch) {
    return ch == '+' || ch == '-' || ch == '|' || ch == 'o' || ch == '.' || ch == ' ';
}

void ensureDisplayLine(const string& line, int displayIndex, int rowIndex) {
    ensuref(line.size() == 29, "display %d row %d has length %d", displayIndex, rowIndex, int(line.size()));
    for (int col = 0; col < 29; ++col) {
        ensuref(isAllowedDisplayChar(line[col]),
                "display %d row %d column %d has invalid character code %d",
                displayIndex,
                rowIndex,
                col + 1,
                int(static_cast<unsigned char>(line[col])));
    }
}

void renderDigit(array<string, 7>& expected, int colOffset, int digit) {
    for (int i = 0; i < 3; ++i) {
        expected[3 * i][colOffset] = kPoints[digit][i] ? '+' : ' ';
        expected[3 * i][colOffset + 4] = kPoints[digit][i + 3] ? '+' : ' ';
    }
    for (int row = 0; row < 7; ++row) {
        for (int col = 0; col < 5; ++col) {
            int bar = kBarIndex[row][col];
            if (bar == -1) {
                continue;
            }
            char segmentChar = bar % 3 == 0 ? '-' : '|';
            expected[row][colOffset + col] = kBars[digit][bar] ? segmentChar : ' ';
        }
    }
}

array<string, 7> renderTime(int hour, int minute) {
    array<string, 7> expected;
    expected.fill(string(29, ' '));
    expected[2][14] = 'o';
    expected[4][14] = 'o';

    renderDigit(expected, 0, hour / 10);
    renderDigit(expected, 7, hour % 10);
    renderDigit(expected, 17, minute / 10);
    renderDigit(expected, 24, minute % 10);

    return expected;
}

bool matchesDisplay(const array<string, 7>& display, const array<string, 7>& expected) {
    for (int row = 0; row < 7; ++row) {
        for (int col = 0; col < 29; ++col) {
            if (!matchesCell(display[row][col], expected[row][col])) {
                return false;
            }
        }
    }
    return true;
}

bool hasPossibleTime(const array<string, 7>& display) {
    for (int hour = 0; hour <= 23; ++hour) {
        for (int minute = 0; minute <= 59; ++minute) {
            if (matchesDisplay(display, renderTime(hour, minute))) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int displayCount = 0;
    while (true) {
        string firstLine = inf.readLine();
        if (firstLine == "end") {
            break;
        }

        ++displayCount;
        // CHECK: The statement gives no display-count bound; cap it for practical validation.
        ensuref(displayCount <= 100000, "too many displays: %d", displayCount);

        array<string, 7> display;
        display[0] = firstLine;
        ensureDisplayLine(display[0], displayCount, 1);
        for (int row = 1; row < 7; ++row) {
            display[row] = inf.readLine();
            ensureDisplayLine(display[row], displayCount, row + 1);
        }

        ensuref(hasPossibleTime(display), "display %d does not match any valid time", displayCount);

        string blank1 = inf.readLine("[ ]{0}", "blank_line_1");
        string blank2 = inf.readLine("[ ]{0}", "blank_line_2");
        ensuref(blank1.empty() && blank2.empty(), "display %d must be followed by two empty lines", displayCount);
    }

    ensuref(displayCount >= 1, "input must contain at least one display before end");
    inf.readEof();
}
