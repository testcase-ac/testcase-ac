#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read exactly 6 integers: counts of King, Queen, Rook, Bishop, Knight, Pawn
    // Each must satisfy 0 <= count <= 10
    inf.readInts(6, 0, 10, "piece_count");

    // Ensure end of the single line
    inf.readEoln();
    // No further content
    inf.readEof();

    return 0;
}
