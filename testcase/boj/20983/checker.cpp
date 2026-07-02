#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

struct Statement {
    int a;
    int b;
    int c;
};

struct Answer {
    bool impossible;
    vector<int> role;
};

int n, m;
vector<int> fixedRole;
vector<Statement> statements;

[[noreturn]] void invalid(InStream& stream, TResult result, const char* fmt, ...) {
    char message[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(message, sizeof(message), fmt, args);
    va_end(args);
    stream.quitf(result, "%s", message);
    exit(1);
}

void validateAssignment(InStream& stream, TResult result, const vector<int>& role) {
    for (int i = 1; i <= n; ++i) {
        if (fixedRole[i] != 3 && role[i] != fixedRole[i]) {
            invalid(stream, result, "person %d is %d, expected fixed value %d", i, role[i], fixedRole[i]);
        }
    }

    for (int j = 0; j < m; ++j) {
        const Statement& s = statements[j];
        if (role[s.a] == 1 && role[s.b] == 1 && role[s.c] == 2) {
            invalid(stream, result,
                    "statement %d is true although speaker %d is a spy", j + 1, s.a);
        }
    }
}

Answer readAnswer(InStream& stream, TResult result) {
    int first = stream.readInt(-1, 2, "first output value");
    if (first == -1) {
        if (!stream.seekEof()) {
            invalid(stream, result, "extra output after -1");
        }
        return {true, {}};
    }
    if (first == 0) {
        invalid(stream, result, "first output value must be -1, 1, or 2");
    }

    vector<int> role(n + 1);
    role[1] = first;
    for (int i = 2; i <= n; ++i) {
        role[i] = stream.readInt(1, 2, format("role[%d]", i).c_str());
    }
    if (!stream.seekEof()) {
        invalid(stream, result, "extra output after assignment");
    }

    validateAssignment(stream, result, role);
    return {false, role};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    fixedRole.assign(n + 1, 3);
    for (int i = 1; i <= n; ++i) {
        fixedRole[i] = inf.readInt();
    }
    statements.resize(m);
    for (int i = 0; i < m; ++i) {
        statements[i].a = inf.readInt();
        statements[i].b = inf.readInt();
        statements[i].c = inf.readInt();
    }

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossibility");
        }
        quitf(_fail, "participant provided a valid assignment while jury reports impossibility");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossibility but jury has a valid assignment");
    }

    quitf(_ok, "valid assignment");
}
