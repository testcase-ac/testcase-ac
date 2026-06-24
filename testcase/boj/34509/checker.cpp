#include "testlib.h"

using namespace std;

int readAnswer(InStream& stream) {
    int value = stream.readInt(10, 99, "N");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after N");
    }

    int tens = value / 10;
    int ones = value % 10;
    int reversed = ones * 10 + tens;

    if (reversed % 4 != 0) {
        stream.quitf(_wa, "reversed number %d is not divisible by 4", reversed);
    }
    if ((tens + ones) % 6 != 0) {
        stream.quitf(_wa, "digit sum %d is not divisible by 6", tens + ones);
    }
    if (tens == 8 || ones == 8) {
        stream.quitf(_wa, "N contains digit 8");
    }

    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int jury = readAnswer(ans);
    int participant = readAnswer(ouf);

    quitf(_ok, "jury=%d participant=%d", jury, participant);
}
