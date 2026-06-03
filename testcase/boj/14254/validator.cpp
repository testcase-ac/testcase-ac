#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string password = inf.readToken("[a-z]{1,50}", "password");
    inf.readEoln();

    int k = inf.readInt(1, static_cast<int>(password.size()), "K");
    inf.readEoln();

    inf.readEof();
}
