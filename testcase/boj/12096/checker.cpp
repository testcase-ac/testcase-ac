#include "testlib.h"

#include <string>

using namespace std;

string readSingleToken(InStream& stream) {
    string token = stream.readWord();
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }
    return token;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string jury = readSingleToken(ans);
    string participant = readSingleToken(ouf);

    if (participant != jury) {
        quitf(_wa, "expected '%s', found '%s'", jury.c_str(), participant.c_str());
    }

    quitf(_ok, "answer matches jury output");
}
