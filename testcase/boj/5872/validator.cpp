#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[()]{1,100000}", "s");
    ensuref(s.size() % 2 == 0, "s length must be even, found %d", int(s.size()));

    inf.readEof();
}
