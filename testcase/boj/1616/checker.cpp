#include "testlib.h"

#include <vector>

using namespace std;

long long kValue;
int mValue;
int totalMessages;

struct Claim {
    bool impossible;
};

Claim readClaim(InStream& stream) {
    long long first = stream.readLong(-1, kValue - 1, "drum[1] or -1");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<int> drum(totalMessages);
    drum[0] = static_cast<int>(first);
    for (int i = 1; i < totalMessages; ++i) {
        drum[i] = stream.readInt(0, static_cast<int>(kValue - 1),
                                 format("drum[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after drum sequence");
    }

    vector<unsigned char> seen(totalMessages, 0);
    long long code = 0;
    for (int i = 0; i < mValue; ++i) {
        code = code * kValue + drum[i % totalMessages];
    }

    for (int start = 0; start < totalMessages; ++start) {
        int id = static_cast<int>(code);
        if (seen[id]) {
            stream.quitf(_wa, "message window starting at position %d is repeated", start + 1);
        }
        seen[id] = 1;

        if (start + 1 < totalMessages) {
            long long highPlace = totalMessages / kValue;
            code = (code % highPlace) * kValue + drum[(start + mValue) % totalMessages];
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    kValue = inf.readLong();
    mValue = inf.readInt();

    long long combinations = 1;
    for (int i = 0; i < mValue; ++i) {
        combinations *= kValue;
    }
    totalMessages = static_cast<int>(combinations);

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant supplied a valid drum while jury claimed impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury supplied a valid drum but participant claimed impossible");
    }

    quitf(_ok, "valid drum with %d messages", totalMessages);
}
