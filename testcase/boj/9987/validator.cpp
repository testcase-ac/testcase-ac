#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the Pokémon number: a natural number between 1 and 718 inclusive.
    int p = inf.readInt(1, 718, "pokemon_number");
    // After the number, there must be exactly one end-of-line.
    inf.readEoln();
    // And then the file must end immediately.
    inf.readEof();

    return 0;
}
