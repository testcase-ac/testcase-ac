#include "testlib.h"

#include <string>

using namespace std;

string a;
string b;

struct Claim {
    int length;
    string value;
};

bool isSubstringOfBoth(const string& value) {
    return a.find(value) != string::npos && b.find(value) != string::npos;
}

Claim readClaim(InStream& stream) {
    int maxLength = min(a.size(), b.size());
    int length = stream.readInt(0, maxLength, "length");
    stream.readEoln();

    string value = stream.readLine("[a-z]*", "substring");
    stream.readEof();

    if ((int)value.size() != length) {
        stream.quitf(_wa, "substring length is %d, but claimed length is %d",
                     (int)value.size(), length);
    }
    if (!isSubstringOfBoth(value)) {
        stream.quitf(_wa, "substring '%s' does not occur in both input strings",
                     value.c_str());
    }

    return {length, value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    a = inf.readLine("[a-z]*", "A");
    b = inf.readLine("[a-z]*", "B");
    inf.readEof();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.length < jury.length) {
        quitf(_wa, "participant answer is shorter than jury answer: %d < %d",
              participant.length, jury.length);
    }
    if (participant.length > jury.length) {
        quitf(_fail, "participant found a longer valid substring: %d > %d",
              participant.length, jury.length);
    }

    quitf(_ok, "answer length %d", participant.length);
}
