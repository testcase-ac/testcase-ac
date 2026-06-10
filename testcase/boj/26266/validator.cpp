#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string plaintext = inf.readToken("[A-Z]{1,200000}", "plaintext");
    inf.readEoln();

    string ciphertext = inf.readToken("[A-Z]{1,200000}", "ciphertext");
    ensuref(ciphertext.size() == plaintext.size(),
            "ciphertext length must match plaintext length: %d != %d",
            static_cast<int>(ciphertext.size()),
            static_cast<int>(plaintext.size()));
    inf.readEoln();

    inf.readEof();
}
