#include "testlib.h"

#include <cctype>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int n;
unordered_set<long long> hasDescriptor;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int size) : parent(size + 1) {
        for (int i = 1; i <= size; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        parent[b] = a;
        return true;
    }
};

struct Answer {
    bool impossible;
};

long long descriptorKey(int person, long long descriptor) {
    return descriptor * (static_cast<long long>(n) + 1) + person;
}

int parseIntToken(InStream& stream, const string& token, int minValue, int maxValue,
                  const char* fieldName) {
    long long value = 0;
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", fieldName);
    }
    for (char c : token) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            stream.quitf(_wa, "%s is not an integer: %s", fieldName, token.c_str());
        }
        value = value * 10 + (c - '0');
        if (value > maxValue) {
            stream.quitf(_wa, "%s=%lld is outside [%d, %d]", fieldName, value,
                         minValue, maxValue);
        }
    }
    if (value < minValue) {
        stream.quitf(_wa, "%s=%lld is outside [%d, %d]", fieldName, value,
                     minValue, maxValue);
    }
    return static_cast<int>(value);
}

long long parseLongToken(InStream& stream, const string& token, long long minValue,
                         long long maxValue, const char* fieldName) {
    long long value = 0;
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", fieldName);
    }
    for (char c : token) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            stream.quitf(_wa, "%s is not an integer: %s", fieldName, token.c_str());
        }
        value = value * 10 + (c - '0');
        if (value > maxValue) {
            stream.quitf(_wa, "%s=%lld is outside [%lld, %lld]", fieldName, value,
                         minValue, maxValue);
        }
    }
    if (value < minValue) {
        stream.quitf(_wa, "%s=%lld is outside [%lld, %lld]", fieldName, value,
                     minValue, maxValue);
    }
    return value;
}

Answer readAnswer(InStream& stream) {
    string first = stream.readToken();
    if (first == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {true};
    }

    Dsu dsu(n);
    int p = parseIntToken(stream, first, 1, n, "p[1]");
    for (int i = 1; i <= n - 1; ++i) {
        int q;
        long long r;
        if (i == 1) {
            q = stream.readInt(1, n, "q[1]");
            r = stream.readLong(1LL, 1000000000LL, "r[1]");
        } else {
            p = stream.readInt(1, n, format("p[%d]", i).c_str());
            q = stream.readInt(1, n, format("q[%d]", i).c_str());
            r = stream.readLong(1LL, 1000000000LL, format("r[%d]", i).c_str());
        }

        if (p == q) {
            stream.quitf(_wa, "edge %d uses the same individual %d twice", i, p);
        }
        if (!hasDescriptor.count(descriptorKey(p, r))) {
            stream.quitf(_wa, "individual %d is not described by %lld in edge %d", p,
                         r, i);
        }
        if (!hasDescriptor.count(descriptorKey(q, r))) {
            stream.quitf(_wa, "individual %d is not described by %lld in edge %d", q,
                         r, i);
        }
        if (!dsu.unite(p, q)) {
            stream.quitf(_wa, "edge %d creates a cycle between %d and %d", i, p, q);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after proof");
    }
    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    hasDescriptor.reserve(400000);
    for (int person = 1; person <= n; ++person) {
        int m = inf.readInt();
        for (int j = 0; j < m; ++j) {
            long long descriptor = inf.readLong();
            hasDescriptor.insert(descriptorKey(person, descriptor));
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant provided a valid proof while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury provides a proof, but participant says impossible");
    }
    quitf(_ok, "valid proof");
}
