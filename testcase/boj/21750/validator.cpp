#include "testlib.h"

#include <string>

using namespace std;

struct Square {
    char file;
    char rank;
};

Square readSquare(const char* name) {
    string token = inf.readToken("[a-h][1-8]", name);
    return {token[0], token[1]};
}

bool sameSquare(Square a, Square b) {
    return a.file == b.file && a.rank == b.rank;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    Square whiteStart = readSquare("whiteStart");
    inf.readSpace();
    Square blackStart = readSquare("blackStart");
    inf.readSpace();
    Square whiteTarget = readSquare("whiteTarget");
    inf.readSpace();
    Square blackTarget = readSquare("blackTarget");
    inf.readEoln();

    ensuref(!sameSquare(whiteStart, blackStart),
            "white and black knights must start on different squares");
    ensuref(!sameSquare(whiteTarget, blackTarget),
            "white and black knights must target different squares");

    inf.readEof();
}
