#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string seats = inf.readToken("[ABC]{1,1000000}", "seats");
    inf.readEoln();
    ensuref(!seats.empty(), "seats must contain at least one person");

    inf.readEof();
}
