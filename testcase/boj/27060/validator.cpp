#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 1; i <= 4; ++i) {
        string line = inf.readLine("[^]*", format("line_%d", i).c_str());

        ensuref(!line.empty(), "line %d must not be empty", i);
        ensuref(line.front() != ' ' && line.back() != ' ',
                "line %d must not have leading or trailing spaces", i);
        ensuref(line.size() <= 72, "line %d has length %d, expected at most 72", i, int(line.size()));

        for (int j = 0; j < int(line.size()); ++j) {
            unsigned char ch = static_cast<unsigned char>(line[j]);
            // CHECK: The statement says uppercase text and mentions blanks, digits,
            // and punctuation; treat that as printable ASCII without lowercase letters.
            ensuref(32 <= ch && ch <= 126,
                    "line %d character %d is not printable ASCII: %d",
                    i,
                    j + 1,
                    int(ch));
            ensuref(!(line[j] >= 'a' && line[j] <= 'z'),
                    "line %d character %d is lowercase: %c",
                    i,
                    j + 1,
                    line[j]);
        }
    }

    inf.readEof();
}
