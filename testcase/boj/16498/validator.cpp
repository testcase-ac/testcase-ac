#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 1000, "A");
    inf.readSpace();
    int b = inf.readInt(1, 1000, "B");
    inf.readSpace();
    int c = inf.readInt(1, 1000, "C");
    inf.readEoln();

    inf.readInts(a, -100000000, 100000000, "first_player_cards");
    inf.readEoln();
    inf.readInts(b, -100000000, 100000000, "second_player_cards");
    inf.readEoln();
    inf.readInts(c, -100000000, 100000000, "third_player_cards");
    inf.readEoln();

    inf.readEof();
}
