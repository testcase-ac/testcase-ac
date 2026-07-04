#include "testlib.h"

#include <string>

using namespace std;

string expectedSuffix(int index, int total) {
    return "(" + to_string(index) + "/" + to_string(total) + ")";
}

bool isAllowedTwintChar(char ch) {
    unsigned char c = static_cast<unsigned char>(ch);
    return ch == ' ' || ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') ||
           ('0' <= ch && ch <= '9') || (33 <= c && c <= 63);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string line = inf.readLine();
        ensuref(!line.empty(), "twint %d is empty", i);
        ensuref((int)line.size() <= 140,
                "twint %d has length %d, expected at most 140",
                i,
                (int)line.size());
        ensuref(line[0] != ' ', "twint %d starts with a space", i);

        for (int j = 0; j < (int)line.size(); ++j) {
            ensuref(isAllowedTwintChar(line[j]),
                    "twint %d contains invalid character code %d at position %d",
                    i,
                    (int)(unsigned char)line[j],
                    j + 1);
            ensuref(j == 0 || line[j - 1] != ' ' || line[j] != ' ',
                    "twint %d contains two sequential spaces ending at position %d",
                    i,
                    j + 1);
        }

        string suffix = expectedSuffix(i, n);
        ensuref(line.size() >= suffix.size() &&
                    line.compare(line.size() - suffix.size(), suffix.size(), suffix) == 0,
                "twint %d must end with suffix %s",
                i,
                suffix.c_str());

        // CHECK: The statement says each twint ends with the numbering string. The samples
        // and the twint format use a separating space before that suffix when content exists.
        if (line.size() > suffix.size()) {
            ensuref(line[line.size() - suffix.size() - 1] == ' ',
                    "twint %d must have a space before suffix %s",
                    i,
                    suffix.c_str());
        }
    }

    inf.readEof();
}
