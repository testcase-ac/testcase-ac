#include "testlib.h"

#include <cctype>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lineCount = 0;
    while (!inf.eof()) {
        string line = inf.readLine("[^]{1,120}", "line");
        ++lineCount;

        ensuref(line.front() != ' ', "line %d has a leading space", lineCount);
        ensuref(line.back() != ' ', "line %d has a trailing space", lineCount);

        for (int i = 0; i < int(line.size()); ++i) {
            unsigned char ch = static_cast<unsigned char>(line[i]);
            ensuref(('A' <= ch && ch <= 'Z') ||
                        ('a' <= ch && ch <= 'z') ||
                        ch == ' ' || ch == ',' || ch == '.',
                    "invalid character with code %d at line %d column %d",
                    int(ch), lineCount, i + 1);
        }
    }

    ensuref(1 <= lineCount && lineCount <= 1000,
            "line count must be between 1 and 1000, got %d", lineCount);
    inf.readEof();
}
