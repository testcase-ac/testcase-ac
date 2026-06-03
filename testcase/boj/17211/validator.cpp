#include "testlib.h"

#include <string>

using namespace std;

int readProbability(const char* name) {
    string token = inf.readToken("[0-1][.][0-9]{2}", name);
    ensuref(token[0] == '0' || token == "1.00", "%s is outside [0.00, 1.00]: %s",
            name, token.c_str());

    return (token[0] - '0') * 100 + (token[2] - '0') * 10 + (token[3] - '0');
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "N");
    inf.readSpace();
    inf.readInt(0, 1, "current_mood");
    inf.readEoln();

    int goodToGood = readProbability("good_to_good");
    inf.readSpace();
    int goodToBad = readProbability("good_to_bad");
    inf.readSpace();
    int badToGood = readProbability("bad_to_good");
    inf.readSpace();
    int badToBad = readProbability("bad_to_bad");
    inf.readEoln();

    ensuref(goodToGood + goodToBad == 100,
            "good-day transition probabilities must sum to 1.00, got %.2f",
            (goodToGood + goodToBad) / 100.0);
    ensuref(badToGood + badToBad == 100,
            "bad-day transition probabilities must sum to 1.00, got %.2f",
            (badToGood + badToBad) / 100.0);

    inf.readEof();
}
