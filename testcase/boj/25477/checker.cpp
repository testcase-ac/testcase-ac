#include "testlib.h"

#include <deque>
#include <string>
#include <vector>

using namespace std;

struct Operation {
    bool insert;
    int value;
};

vector<Operation> operations;
int insertCount;

struct Claim {
    long long value;
};

void quitInvalid(InStream& stream, TResult result, const char* format, ...) {
    FMT_TO_RESULT(format, format, message);
    stream.quitf(result, "%s", message.c_str());
}

Claim readClaim(InStream& stream, TResult invalidResult, const char* owner) {
    long long printedSum = stream.readLong(-20000000000000LL, 20000000000000LL,
                                           format("%s sum", owner).c_str());
    string decisions = stream.readToken(format("[PK]{%d}", insertCount),
                                        format("%s decisions", owner).c_str());
    if (!stream.seekEof()) {
        quitInvalid(stream, invalidResult, "%s output has extra tokens", owner);
    }

    deque<int> values;
    int decisionIndex = 0;
    long long computedSum = 0;

    for (int i = 0; i < (int)operations.size(); ++i) {
        const Operation& op = operations[i];
        if (op.insert) {
            char decision = decisions[decisionIndex++];
            if (decision == 'P') {
                values.push_front(op.value);
            } else {
                values.push_back(op.value);
            }
        } else {
            if (values.empty()) {
                quitInvalid(stream, invalidResult,
                            "%s certificate pops from an empty sequence at operation %d",
                            owner, i + 1);
            }
            computedSum += values.front();
            values.pop_front();
        }
    }

    if (decisionIndex != insertCount) {
        quitInvalid(stream, invalidResult,
                    "%s decision count mismatch: expected %d, found %d",
                    owner, insertCount, decisionIndex);
    }
    if (printedSum != computedSum) {
        quitInvalid(stream, invalidResult,
                    "%s printed sum %lld does not match certificate sum %lld",
                    owner, printedSum, computedSum);
    }

    return {computedSum};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    operations.reserve(n);
    insertCount = 0;

    int currentSize = 0;
    for (int i = 0; i < n; ++i) {
        string op = inf.readToken();
        if (op == "UBACI") {
            int x = inf.readInt(1, 100000, format("X[%d]", i + 1).c_str());
            operations.push_back({true, x});
            ++insertCount;
            ++currentSize;
        } else if (op == "IZBACI") {
            if (currentSize == 0) {
                quitf(_fail, "input pops from an empty sequence at operation %d", i + 1);
            }
            operations.push_back({false, 0});
            --currentSize;
        } else {
            quitf(_fail, "unknown input operation '%s' at operation %d", op.c_str(), i + 1);
        }
    }

    Claim jury = readClaim(ans, _fail, "jury");
    Claim participant = readClaim(ouf, _wa, "participant");

    if (participant.value < jury.value) {
        quitf(_wa, "participant sum %lld is less than jury sum %lld",
              participant.value, jury.value);
    }
    if (participant.value > jury.value) {
        quitf(_fail, "participant found better sum: participant=%lld jury=%lld",
              participant.value, jury.value);
    }
    quitf(_ok, "sum=%lld", participant.value);
}
