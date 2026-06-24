#include "testlib.h"

using namespace std;

const long long MAX_M = 9000000000000000000LL;

struct LogEntry {
    long long delta;
    long long balance;
};

vector<LogEntry> logs;

struct Claim {
    bool impossible;
    long long m;
    bool valid;
};

bool matchesLog(long long m) {
    __int128 cur = 0;

    for (int i = 0; i < (int)logs.size(); ++i) {
        long long a = logs[i].delta;
        long long b = logs[i].balance;

        if (a > 0) {
            cur += a;
            if (cur != (__int128)b) {
                return false;
            }
        } else {
            __int128 withdraw = -(__int128)a;
            if (cur < withdraw) {
                __int128 need = withdraw - cur;
                __int128 count = (need + m - 1) / m;
                cur += count * (__int128)m;
            }
            cur -= withdraw;
            if (cur != (__int128)b) {
                return false;
            }
        }
    }

    return true;
}

Claim readClaim(InStream& stream) {
    long long value = stream.readLong(-1LL, MAX_M, "M");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after M");
    }

    if (value == -1) {
        return {true, -1, false};
    }
    if (value == 0) {
        return {false, 0, false};
    }
    return {false, value, matchesLog(value)};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    logs.resize(n);
    for (int i = 0; i < n; ++i) {
        logs[i].delta = inf.readLong();
        logs[i].balance = inf.readLong();
    }

    Claim jury = readClaim(ans);
    if (!jury.impossible && !jury.valid) {
        quitf(_fail, "jury output M=%lld does not match the log", jury.m);
    }

    Claim participant = readClaim(ouf);
    if (participant.impossible) {
        if (jury.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_wa, "participant reports impossible, but jury has valid M=%lld", jury.m);
    }

    if (!participant.valid) {
        quitf(_wa, "participant output M=%lld does not match the log", participant.m);
    }
    if (jury.impossible) {
        quitf(_fail, "participant found valid M=%lld while jury reports impossible", participant.m);
    }

    quitf(_ok, "valid M=%lld", participant.m);
}
