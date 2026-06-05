#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string first = inf.readToken("[A-Z]{1,18}", "first");
    inf.readSpace();
    string second = inf.readToken("[A-Z]{1,18}", "second");
    inf.readSpace();
    string result = inf.readToken("[A-Z]{1,18}", "result");
    inf.readEoln();

    inf.readEof();
}
