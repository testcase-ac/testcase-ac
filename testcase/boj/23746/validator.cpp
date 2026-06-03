#include "testlib.h"

#include <array>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 26, "N");
    inf.readEoln();

    array<int, 26> patternLengths{};
    vector<bool> seen(26, false);
    for (int i = 0; i < n; ++i) {
        string pattern = inf.readToken("[a-z]{1,1000}", "pattern");
        inf.readSpace();
        string symbol = inf.readToken("[A-Z]", "symbol");
        inf.readEoln();

        int index = symbol[0] - 'A';
        ensuref(!seen[index], "uppercase symbol %c is repeated", symbol[0]);
        seen[index] = true;
        patternLengths[index] = static_cast<int>(pattern.size());
    }

    string compressed = inf.readToken("[A-Z]{1,1000}", "compressed");
    inf.readEoln();

    int decompressedLength = 0;
    for (int i = 0; i < static_cast<int>(compressed.size()); ++i) {
        int index = compressed[i] - 'A';
        ensuref(seen[index], "compressed[%d] uses undefined symbol %c", i + 1, compressed[i]);
        decompressedLength += patternLengths[index];
    }

    int s = inf.readInt(1, decompressedLength, "S");
    inf.readSpace();
    inf.readInt(s, decompressedLength, "E");
    inf.readEoln();

    inf.readEof();
}
