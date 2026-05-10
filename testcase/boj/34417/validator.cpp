#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single line of uppercase letters, length L where 0 <= L <= 1_000_000
    string s = inf.readLine("[A-Z]*", "s");
    ensuref(s.size() <= 1000000u, "String length %zu exceeds 1_000_000", s.size());

    // No extra lines / characters allowed
    inf.readEof();
}
