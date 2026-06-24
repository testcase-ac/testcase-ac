#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct Answer {
    bool exists;
    long long gcdValue;
    long long removedValue;
};

vector<long long> values;
vector<long long> prefixGcd;
vector<long long> suffixGcd;

long long gcdWithoutIndex(int index) {
    if (index == 0) {
        return suffixGcd[1];
    }
    if (index + 1 == (int)values.size()) {
        return prefixGcd[index - 1];
    }
    return gcd(prefixGcd[index - 1], suffixGcd[index + 1]);
}

Answer readAnswer(InStream& stream) {
    long long first = stream.readLong(-1, 2000000000LL, "gcd");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {false, -1, -1};
    }
    if (first == 0) {
        stream.quitf(_wa, "gcd must be positive or -1");
    }

    long long removed = stream.readLong(1, 2000000000LL, "removed value");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    bool found = false;
    for (int i = 0; i < (int)values.size(); ++i) {
        if (values[i] != removed) {
            continue;
        }
        long long actualGcd = gcdWithoutIndex(i);
        if (actualGcd == first) {
            found = true;
            break;
        }
    }
    if (!found) {
        stream.quitf(_wa,
                     "removing value %lld does not produce gcd %lld",
                     removed,
                     first);
    }
    if (removed % first == 0) {
        stream.quitf(_wa,
                     "gcd %lld must not be a divisor of removed value %lld",
                     first,
                     removed);
    }

    return {true, first, removed};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    values.resize(n);
    prefixGcd.resize(n);
    suffixGcd.resize(n);
    for (int i = 0; i < n; ++i) {
        values[i] = inf.readLong();
    }

    prefixGcd[0] = values[0];
    for (int i = 1; i < n; ++i) {
        prefixGcd[i] = gcd(prefixGcd[i - 1], values[i]);
    }
    suffixGcd[n - 1] = values[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        suffixGcd[i] = gcd(suffixGcd[i + 1], values[i]);
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.exists) {
        if (!participant.exists) {
            quitf(_ok, "no answer");
        }
        quitf(_fail,
              "participant found valid answer %lld %lld but jury says -1",
              participant.gcdValue,
              participant.removedValue);
    }

    if (!participant.exists) {
        quitf(_wa,
              "jury has answer %lld %lld but participant says -1",
              jury.gcdValue,
              jury.removedValue);
    }
    if (participant.gcdValue < jury.gcdValue) {
        quitf(_wa,
              "jury has better gcd: jury=%lld participant=%lld",
              jury.gcdValue,
              participant.gcdValue);
    }
    if (participant.gcdValue > jury.gcdValue) {
        quitf(_fail,
              "participant found better gcd: jury=%lld participant=%lld",
              jury.gcdValue,
              participant.gcdValue);
    }

    quitf(_ok, "answer %lld %lld", participant.gcdValue, participant.removedValue);
}
