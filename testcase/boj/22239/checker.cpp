#include "testlib.h"

#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

struct Instance {
    int n;
    int c;
    vector<long long> target;
    vector<vector<int>> constraints;
    vector<long long> cardValue;
};

struct Claim {
    bool impossible;
};

bool parseIntegerToken(const string& token, long long& value) {
    if (token.empty()) {
        return false;
    }
    int pos = 0;
    int sign = 1;
    if (token[0] == '-') {
        sign = -1;
        pos = 1;
    }
    if (pos == (int)token.size()) {
        return false;
    }
    long long parsed = 0;
    for (; pos < (int)token.size(); ++pos) {
        if (!isdigit((unsigned char)token[pos])) {
            return false;
        }
        parsed = parsed * 10 + (token[pos] - '0');
        if (parsed > 1000000000000000000LL) {
            return false;
        }
    }
    value = sign * parsed;
    return true;
}

void quitInvalid(InStream& stream, TResult verdict, const char* streamName, const char* format, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    stream.quitf(verdict, "%s output is invalid: %s", streamName, buffer);
}

Claim readClaim(InStream& stream, const Instance& instance, TResult invalidVerdict, const char* streamName) {
    string first = stream.readToken("[^\\s]+", "first output token");
    long long firstValue = 0;
    if (!parseIntegerToken(first, firstValue)) {
        quitInvalid(stream, invalidVerdict, streamName, "first output token '%s' is not an integer", first.c_str());
    }

    if (firstValue == -1) {
        if (!stream.seekEof()) {
            quitInvalid(stream, invalidVerdict, streamName, "extra output after -1");
        }
        return {true};
    }

    vector<int> answer(instance.c);
    if (firstValue < 1 || firstValue > instance.n) {
        quitInvalid(stream, invalidVerdict, streamName,
                    "turn 1 has player %lld outside [1, %d]", firstValue, instance.n);
    }
    answer[0] = (int)firstValue;

    for (int i = 1; i < instance.c; ++i) {
        answer[i] = stream.readInt(1, instance.n, format("turn[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        quitInvalid(stream, invalidVerdict, streamName, "extra output after %d turns", instance.c);
    }

    vector<int> nextCardIndex(instance.n + 1, 0);
    for (int turn = 0; turn < instance.c; ++turn) {
        int person = answer[turn];
        int pos = nextCardIndex[person];
        if (pos >= (int)instance.constraints[person].size()) {
            quitInvalid(stream, invalidVerdict, streamName,
                        "turn %d uses player %d after all of their cards were played",
                        turn + 1, person);
        }

        int card = instance.constraints[person][pos];
        long long produced = instance.cardValue[card];
        if (produced != instance.target[turn]) {
            quitInvalid(stream, invalidVerdict, streamName,
                        "turn %d uses player %d card %d with value %lld, expected %lld",
                        turn + 1, person, card, produced, instance.target[turn]);
        }
        ++nextCardIndex[person];
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Instance instance;
    instance.n = inf.readInt();
    instance.c = inf.readInt();
    instance.target.resize(instance.c);
    for (int i = 0; i < instance.c; ++i) {
        instance.target[i] = inf.readLong();
    }

    instance.constraints.assign(instance.n + 1, {});
    for (int person = 1; person <= instance.n; ++person) {
        int k = inf.readInt();
        instance.constraints[person].resize(k);
        for (int j = 0; j < k; ++j) {
            instance.constraints[person][j] = inf.readInt();
        }
    }

    instance.cardValue.assign(instance.c + 1, 0);
    for (int card = 1; card <= instance.c; ++card) {
        string operation = inf.readToken();
        if (operation != "ADD") {
            quitf(_fail, "input operation for card %d is '%s', expected ADD", card, operation.c_str());
        }
        instance.cardValue[card] = inf.readLong();
    }

    Claim jury = readClaim(ans, instance, _fail, "jury");
    Claim participant = readClaim(ouf, instance, _wa, "participant");

    if (jury.impossible && participant.impossible) {
        quitf(_ok, "both outputs claim impossible");
    }
    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant produced a valid witness while jury output is -1");
    }
    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "jury has a valid witness but participant output is -1");
    }

    quitf(_ok, "participant witness is valid");
}
