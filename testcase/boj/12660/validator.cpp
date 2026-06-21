#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);

        string line = inf.readLine("[a-z\\ ]{1,500}", "text");
        ensuref(line.front() != ' ', "text line %d starts with a space", i);
        ensuref(line.back() != ' ', "text line %d ends with a space", i);
    }

    inf.readEof();
}
