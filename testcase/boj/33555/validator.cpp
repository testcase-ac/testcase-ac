#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int questionMarks = 0;
    int values[3] = {-1, -1, -1};

    for (int i = 0; i < 3; ++i) {
        string name = string("part_") + char('a' + i);
        string token = inf.readToken("[?]|[1-9][0-9]{0,4}", name.c_str());
        if (token == "?") {
            ++questionMarks;
        } else {
            int value = stoi(token);
            ensuref(value <= 23000, "%s must be at most 23000, got %d", name.c_str(), value);
            values[i] = value;
        }

        if (i == 2) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    ensuref(questionMarks == 1, "input must contain exactly one question mark, got %d", questionMarks);
    if (values[2] != -1) {
        ensuref(values[0] == -1 || values[0] < values[2],
                "known side a must be shorter than hypotenuse c");
        ensuref(values[1] == -1 || values[1] < values[2],
                "known side b must be shorter than hypotenuse c");
    }

    inf.readEof();
}
