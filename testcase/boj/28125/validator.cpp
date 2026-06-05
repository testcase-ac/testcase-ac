#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string s = inf.readLine("[^]{1,300}", "word");
        int decodedLength = 0;

        for (int j = 0; j < (int)s.size();) {
            char c = s[j];

            if ('a' <= c && c <= 'z') {
                ++decodedLength;
                ++j;
            } else if (c == '@' || c == '[' || c == '!' || c == ';' ||
                       c == '^' || c == '0' || c == '7') {
                ++decodedLength;
                ++j;
            } else if (c == '\\') {
                if (j + 1 < (int)s.size() && s[j + 1] == '\'') {
                    ++decodedLength;
                    j += 2;
                } else if (j + 2 < (int)s.size() && s[j + 1] == '\\' &&
                           s[j + 2] == '\'') {
                    ++decodedLength;
                    j += 3;
                } else {
                    ensuref(false, "invalid escape sequence in word %d at byte %d", i, j + 1);
                }
            } else {
                ensuref(false, "invalid character in word %d at byte %d", i, j + 1);
            }

            ensuref(decodedLength <= 100, "decoded word %d is longer than 100", i);
        }

        ensuref(decodedLength >= 1, "decoded word %d is empty", i);
    }

    inf.readEof();
}
