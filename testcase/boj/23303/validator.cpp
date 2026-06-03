#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[A-Za-z0-9\\ ]{1,10000}", "s");
    ensuref(s.front() != ' ', "s must not start with a space");
    ensuref(s.back() != ' ', "s must not end with a space");

    inf.readEof();
}
