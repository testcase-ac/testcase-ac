#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[A-Z]{1,2000000}", "S");
    ensuref(!s.empty(), "S must contain at least one character");

    inf.readEof();
}
