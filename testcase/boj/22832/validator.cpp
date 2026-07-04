#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

vector<int> parseIntLine(const string& line, int expectedCount, int minValue,
                         int maxValue, const char* context) {
    ensuref(!line.empty(), "%s line must not be empty", context);
    ensuref(line.front() != ' ' && line.back() != ' ',
            "%s line has leading or trailing space", context);

    vector<int> values;
    for (int i = 0; i < int(line.size());) {
        ensuref(line[i] >= '0' && line[i] <= '9',
                "%s line contains invalid character at position %d", context,
                i + 1);

        int start = i;
        while (i < int(line.size()) && line[i] >= '0' && line[i] <= '9') {
            ++i;
        }

        string token = line.substr(start, i - start);
        ensuref(token == "0" || token.front() != '0',
                "%s value has leading zero: %s", context, token.c_str());
        int value = atoi(token.c_str());
        ensuref(minValue <= value && value <= maxValue,
                "%s value %d outside range [%d, %d]", context, value, minValue,
                maxValue);
        values.push_back(value);

        if (i == int(line.size())) {
            break;
        }
        ensuref(line[i] == ' ', "%s line has invalid separator", context);
        while (i < int(line.size()) && line[i] == ' ') {
            ++i;
        }
        ensuref(i < int(line.size()), "%s line has trailing space", context);
    }

    ensuref(int(values.size()) == expectedCount,
            "%s line has %d values, expected %d", context, int(values.size()),
            expectedCount);
    return values;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int mapIndex = 0;
    while (true) {
        string dimensions = inf.readLine("[0-9\\ ]{3,20}", "dimensions");
        vector<int> size = parseIntLine(dimensions, 2, 0, 7, "dimensions");
        int w = size[0];
        int h = size[1];

        if (w == 0 && h == 0) {
            break;
        }
        ensuref(1 <= w && 1 <= h, "map %d has non-positive dimension %d x %d",
                mapIndex + 1, w, h);
        setTestCase(++mapIndex);

        int cargoCount = 0;
        int goalCount = 0;
        int warehousemanCount = 0;
        for (int row = 0; row < h; ++row) {
            string line = inf.readLine("[0-4\\ ]{1,30}", "row");
            vector<int> cells = parseIntLine(line, w, 0, 4, "row");
            for (int cell : cells) {
                cargoCount += cell == 2;
                goalCount += cell == 3;
                warehousemanCount += cell == 4;
            }
        }

        ensuref(cargoCount == 1, "map %d has %d cargo cells", mapIndex,
                cargoCount);
        ensuref(goalCount == 1, "map %d has %d goal cells", mapIndex,
                goalCount);
        ensuref(warehousemanCount == 1, "map %d has %d warehouseman cells",
                mapIndex, warehousemanCount);
    }

    ensuref(mapIndex >= 1, "input must contain at least one map");
    inf.readEof();
}
