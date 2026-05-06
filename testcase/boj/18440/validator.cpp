#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First string: uppercase letters only, length 0..50000 (since "최대 50000글자")
    string s1 = inf.readLine("[A-Z]{0,50000}", "s1");
    // Second string: same constraints
    string s2 = inf.readLine("[A-Z]{0,50000}", "s2");

    // No extra lines or spaces allowed
    inf.readEof();
}
