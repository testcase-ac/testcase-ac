#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

vector<string> splitOperations(const string& line, char delimiter) {
    vector<string> parts;
    string current;
    for (char ch : line) {
        if (ch == delimiter) {
            parts.push_back(current);
            current.clear();
        } else {
            current += ch;
        }
    }
    parts.push_back(current);
    return parts;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 9, "n");
    inf.readSpace();
    int c = inf.readInt(n, 9, "c");
    inf.readEoln();

    vector<bool> used(c + 1, false);
    int totalCards = 0;
    for (int i = 1; i <= n; ++i) {
        int count = inf.readInt(1, c, "card_count");
        totalCards += count;
        for (int j = 0; j < count; ++j) {
            inf.readSpace();
            int card = inf.readInt(1, c, "card");
            ensuref(!used[card], "card %d is used more than once", card);
            used[card] = true;
        }
        inf.readEoln();
    }
    ensuref(totalCards == c, "all cards must be used exactly once, found %d of %d", totalCards, c);

    int totalOperations = 0;
    for (int cardIndex = 1; cardIndex <= c; ++cardIndex) {
        string line = inf.readLine("[A-Z0-9a-z,\\ ]{1,100}", "operations");
        vector<string> operations = splitOperations(line, ',');
        ensuref(!operations.empty(), "card %d must contain at least one operation", cardIndex);

        for (const string& operation : operations) {
            ensuref(!operation.empty(), "empty operation on card %d", cardIndex);
            ++totalOperations;

            if (operation.size() == 5 && operation.substr(0, 4) == "ADD ") {
                char ch = operation[4];
                ensuref('a' <= ch && ch <= 'z',
                        "ADD argument on card %d must be lowercase, found '%c'", cardIndex, ch);
            } else if (operation.size() == 5 && operation.substr(0, 4) == "DEL ") {
                char ch = operation[4];
                ensuref('0' <= ch && ch <= '9',
                        "DEL argument on card %d must be a digit from 0 to 9, found '%c'", cardIndex, ch);
            } else {
                // CHECK: The prose shows lowercase operation names, but official samples use uppercase.
                ensuref(false, "operation on card %d must be formatted as ADD c or DEL x", cardIndex);
            }
        }
    }
    ensuref(1 <= totalOperations && totalOperations <= 10,
            "total operation count must be between 1 and 10, found %d", totalOperations);

    inf.readEof();
}
