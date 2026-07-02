#include "testlib.h"

#include <set>
#include <string>

using namespace std;

set<string> readClaim(InStream& stream, TResult verdict, const char* who) {
    set<string> squares;

    while (!stream.seekEof()) {
        string square = stream.readWord("[a-h][1-8]", format("%s square", who).c_str());
        if (!squares.insert(square).second) {
            stream.quitf(verdict, "%s repeats square %s", who, square.c_str());
        }
    }

    return squares;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    inf.readWord("[a-h][1-8]", "initial square");
    if (!inf.seekEof()) {
        quitf(_fail, "extra input after initial square");
    }

    set<string> jury = readClaim(ans, _fail, "jury");
    set<string> participant = readClaim(ouf, _wa, "participant");

    if (participant != jury) {
        for (const string& square : jury) {
            if (!participant.count(square)) {
                quitf(_wa, "participant is missing square %s", square.c_str());
            }
        }
        for (const string& square : participant) {
            if (!jury.count(square)) {
                quitf(_wa, "participant has extra square %s", square.c_str());
            }
        }
        quitf(_wa, "participant square set differs from jury");
    }

    quitf(_ok, "%d squares match jury set", int(participant.size()));
}
