#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <set>
#include <string>
#include <vector>
using namespace std;

vector<string> splitSingleSpaces(const string& line, const char* name) {
    ensuref(!line.empty(), "%s must not be empty", name);
    ensuref(line.front() != ' ' && line.back() != ' ', "%s has leading or trailing space", name);
    ensuref(line.find("  ") == string::npos, "%s has repeated spaces", name);

    vector<string> parts;
    size_t start = 0;
    while (true) {
        size_t pos = line.find(' ', start);
        parts.push_back(line.substr(start, pos == string::npos ? string::npos : pos - start));
        if (pos == string::npos) break;
        start = pos + 1;
    }
    return parts;
}

int parsePositiveInt(const string& token, int low, int high, const char* name) {
    ensuref(!token.empty(), "%s is empty", name);
    ensuref(token == "0" || token[0] != '0', "%s has a leading zero: %s", name, token.c_str());
    int value = 0;
    for (char ch : token) {
        ensuref(isdigit(static_cast<unsigned char>(ch)), "%s is not numeric: %s", name, token.c_str());
        value = value * 10 + (ch - '0');
        ensuref(value <= high, "%s is above %d: %s", name, high, token.c_str());
    }
    ensuref(low <= value && value <= high, "%s is outside [%d, %d]: %d", name, low, high, value);
    return value;
}

int pointIndex(char ch) {
    ensuref('A' <= ch && ch <= 'H', "connection point is outside A-H: %c", ch);
    return ch - 'A';
}

bool isOutsidePoint(int square, int point, int h, int w) {
    int row = square / w;
    int col = square % w;
    if ((point == 0 || point == 1) && row == 0) return true;
    if ((point == 2 || point == 3) && col == w - 1) return true;
    if ((point == 4 || point == 5) && row == h - 1) return true;
    if ((point == 6 || point == 7) && col == 0) return true;
    return false;
}

int adjacentNode(int square, int point, int h, int w) {
    int row = square / w;
    int col = square % w;
    if (point == 0 && row > 0) return ((row - 1) * w + col) * 8 + 5;
    if (point == 1 && row > 0) return ((row - 1) * w + col) * 8 + 4;
    if (point == 2 && col + 1 < w) return (row * w + col + 1) * 8 + 7;
    if (point == 3 && col + 1 < w) return (row * w + col + 1) * 8 + 6;
    if (point == 4 && row + 1 < h) return ((row + 1) * w + col) * 8 + 1;
    if (point == 5 && row + 1 < h) return ((row + 1) * w + col) * 8 + 0;
    if (point == 6 && col > 0) return (row * w + col - 1) * 8 + 3;
    if (point == 7 && col > 0) return (row * w + col - 1) * 8 + 2;
    return -1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int board = 1;
    while (true) {
        int h = inf.readInt(0, 20, "h");
        inf.readSpace();
        int w = inf.readInt(0, 20, "w");
        inf.readEoln();

        if (h == 0 && w == 0) break;
        setTestCase(board++);
        ensuref(1 <= h && 1 <= w, "non-terminal board dimensions must be positive");

        int squares = h * w;
        vector<vector<int>> wired(squares, vector<int>(8, -1));
        vector<vector<int>> graph(squares * 8);
        vector<bool> described(squares, false);
        int describedCount = 0;

        while (true) {
            string line = inf.readLine("[0-9A-Z\\ ]{1,100}", "square_description_or_zero");
            if (line == "0") break;

            vector<string> parts = splitSingleSpaces(line, "square description");
            ensuref(parts.size() >= 2, "described square must list at least one wire pair");
            ensuref(parts.size() <= 5, "square has more than 4 wire pairs");

            int square = parsePositiveInt(parts[0], 1, squares, "square number") - 1;
            ensuref(!described[square], "square %d is described more than once", square + 1);
            described[square] = true;
            ++describedCount;
            ensuref(describedCount <= squares, "too many square descriptions");

            string previousPair;
            vector<bool> usedPoint(8, false);
            for (size_t i = 1; i < parts.size(); ++i) {
                const string& pair = parts[i];
                ensuref(pair.size() == 2, "wire pair must have length 2: %s", pair.c_str());
                int a = pointIndex(pair[0]);
                int b = pointIndex(pair[1]);
                ensuref(a < b, "wire pair must be alphabetical: %s", pair.c_str());
                ensuref(previousPair.empty() || previousPair < pair,
                        "wire pairs must be listed in alphabetical order");
                previousPair = pair;

                ensuref(!usedPoint[a] && !usedPoint[b],
                        "connection point reused in square %d", square + 1);
                usedPoint[a] = usedPoint[b] = true;
                wired[square][a] = b;
                wired[square][b] = a;

                int nodeA = square * 8 + a;
                int nodeB = square * 8 + b;
                graph[nodeA].push_back(nodeB);
                graph[nodeB].push_back(nodeA);
            }
        }

        for (int square = 0; square < squares; ++square) {
            for (int point = 0; point < 8; ++point) {
                if (wired[square][point] == -1) continue;
                int neighbor = adjacentNode(square, point, h, w);
                if (neighbor == -1) continue;

                ensuref(wired[neighbor / 8][neighbor % 8] != -1,
                        "wire at square %d point %c is broken at adjacent square %d point %c",
                        square + 1, char('A' + point), neighbor / 8 + 1, char('A' + neighbor % 8));
                if (square * 8 + point < neighbor) {
                    graph[square * 8 + point].push_back(neighbor);
                    graph[neighbor].push_back(square * 8 + point);
                }
            }
        }

        vector<bool> seen(squares * 8, false);
        for (int node = 0; node < squares * 8; ++node) {
            if (graph[node].empty() || seen[node]) continue;

            vector<int> stack = {node};
            seen[node] = true;
            int boundaryPoints = 0;
            while (!stack.empty()) {
                int cur = stack.back();
                stack.pop_back();
                int square = cur / 8;
                int point = cur % 8;
                if (isOutsidePoint(square, point, h, w)) ++boundaryPoints;

                for (int nxt : graph[cur]) {
                    if (!seen[nxt]) {
                        seen[nxt] = true;
                        stack.push_back(nxt);
                    }
                }
            }
            ensuref(boundaryPoints == 2,
                    "each wire path must begin and end at the board edge, found %d boundary points",
                    boundaryPoints);
        }

        string startsLine = inf.readLine("[0-9A-H\\ ]{1,10000}", "starting_points");
        vector<string> starts = splitSingleSpaces(startsLine, "starting points");
        set<pair<int, int>> seenStarts;
        for (const string& start : starts) {
            ensuref(start.size() >= 2, "starting point is too short: %s", start.c_str());
            int point = pointIndex(start.back());
            int square = parsePositiveInt(start.substr(0, start.size() - 1), 1, squares,
                                          "starting point square") -
                         1;
            ensuref(isOutsidePoint(square, point, h, w),
                    "starting point %s is not on the outside of the board", start.c_str());
            ensuref(wired[square][point] != -1,
                    "starting point %s does not use a wired connection point", start.c_str());
            // CHECK: The statement does not explicitly forbid duplicate starting points; reject them
            // because the input describes a set of starting points.
            ensuref(seenStarts.insert({square, point}).second,
                    "duplicate starting point: %s", start.c_str());
        }

        inf.readEoln();
    }

    inf.readEof();
}
