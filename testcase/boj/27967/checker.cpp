#include "testlib.h"

#include <string>

using namespace std;

int n;
string s;

string readAnswer(InStream& stream) {
    string restored = stream.readToken("[()]+", "restored string");
    if ((int)restored.size() != n) {
        stream.quitf(_wa, "restored string length is %d, expected %d", (int)restored.size(), n);
    }

    int balance = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] != 'G' && restored[i] != s[i]) {
            stream.quitf(_wa,
                         "character %d is '%c', expected fixed character '%c'",
                         i + 1,
                         restored[i],
                         s[i]);
        }

        if (restored[i] == '(') {
            ++balance;
        } else {
            --balance;
        }
        if (balance < 0) {
            stream.quitf(_wa, "prefix ending at character %d has negative balance", i + 1);
        }
    }
    if (balance != 0) {
        stream.quitf(_wa, "final balance is %d, expected 0", balance);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after restored string");
    }
    return restored;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    s = inf.readToken();

    string jury = readAnswer(ans);
    string participant = readAnswer(ouf);
    (void)jury;

    quitf(_ok, "valid restoration: %s", participant.c_str());
}
