#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string statements = inf.readToken("[fe]{1,5000}", "statements");
    inf.readEoln();

    ensuref(statements.back() == 'e',
            "at least one valid indentation requires the final statement to be executable");

    inf.readEof();
}
