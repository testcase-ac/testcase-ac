#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string a = inf.readLine("[a-z]{1,200000}", "a");
    string b = inf.readLine("[a-z]{1,200000}", "b");

    ensuref(a.size() == b.size(), "a and b must have the same length: %zu != %zu",
            a.size(), b.size());

    inf.readEof();
}
