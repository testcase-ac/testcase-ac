#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the DNA sequence: must consist only of 'a', 'c', 'g', 't', length 1 to 500.
    inf.readLine("[acgt]{1,500}", "s");

    // No extra lines or spaces: immediately EOF.
    inf.readEof();
    return 0;
}
