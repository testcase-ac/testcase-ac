#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[a-z]+", "S");
    ensuref(s.size() <= 10000000, "S length must not exceed 10000000, found %zu", s.size());

    inf.readEof();
}
