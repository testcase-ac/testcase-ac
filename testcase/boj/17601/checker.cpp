#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n;
vector<int> valueOf;

struct Answer {
    bool impossible;
};

int parseSoldierToken(InStream& stream, const string& token, TResult verdict, const char* name) {
    int parsed = 0;
    if (token.empty()) {
        stream.quitf(verdict, "%s is empty", name);
    }
    for (char ch : token) {
        if (ch < '0' || ch > '9') {
            stream.quitf(verdict, "%s is not an integer: %s", name, token.c_str());
        }
        parsed = parsed * 10 + (ch - '0');
        if (parsed > n) {
            stream.quitf(verdict, "%s=%d is outside [1, %d]", name, parsed, n);
        }
    }
    if (parsed < 1) {
        stream.quitf(verdict, "%s=%d is outside [1, %d]", name, parsed, n);
    }
    return parsed;
}

void requireEof(InStream& stream, TResult verdict) {
    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after expected answer");
    }
}

Answer readAnswer(InStream& stream, TResult verdict) {
    string first = stream.readToken();
    if (first == "-1") {
        requireEof(stream, verdict);
        return {true};
    }

    vector<int> alive(n);
    for (int i = 0; i < n; ++i) {
        alive[i] = i + 1;
    }

    for (int step = 0; step < n / 2; ++step) {
        int p;
        if (step == 0) {
            p = parseSoldierToken(stream, first, verdict, "p[1]");
        } else {
            p = stream.readInt(1, n, format("p[%d]", step + 1).c_str());
        }
        int q = stream.readInt(1, n, format("q[%d]", step + 1).c_str());

        if (p == q) {
            stream.quitf(verdict, "attack %d uses the same soldier %d twice", step + 1, p);
        }

        auto itP = find(alive.begin(), alive.end(), p);
        auto itQ = find(alive.begin(), alive.end(), q);
        if (itP == alive.end()) {
            stream.quitf(verdict, "attack %d uses already removed soldier %d", step + 1, p);
        }
        if (itQ == alive.end()) {
            stream.quitf(verdict, "attack %d uses already removed soldier %d", step + 1, q);
        }

        int posP = int(itP - alive.begin());
        int posQ = int(itQ - alive.begin());
        int current = int(alive.size());
        int distance = abs(posP - posQ);
        if (distance != 1 && distance != current - 1) {
            stream.quitf(verdict,
                         "attack %d uses non-adjacent soldiers %d and %d",
                         step + 1,
                         p,
                         q);
        }
        if (valueOf[p] == valueOf[q]) {
            stream.quitf(verdict,
                         "attack %d uses soldiers %d and %d with equal value %d",
                         step + 1,
                         p,
                         q,
                         valueOf[p]);
        }

        if (posP < posQ) {
            swap(posP, posQ);
        }
        alive.erase(alive.begin() + posP);
        alive.erase(alive.begin() + posQ);
    }

    requireEof(stream, verdict);
    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    inf.readInt();
    valueOf.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        valueOf[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both jury and participant report impossible");
        }
        quitf(_fail, "participant found a valid attack sequence while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury provides a valid attack sequence");
    }

    quitf(_ok, "valid attack sequence");
}
