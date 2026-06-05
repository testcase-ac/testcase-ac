#include "testlib.h"

#include <cctype>
#include <set>
#include <string>
#include <vector>

using namespace std;

char nextNonBlank() {
    while (!inf.eof()) {
        char c = inf.readChar();
        if (!isspace(static_cast<unsigned char>(c))) {
            return c;
        }
    }
    return 0;
}

void expectChar(char expected, const char* name) {
    char c = nextNonBlank();
    ensuref(c == expected, "expected %s '%c', found '%c'", name, expected, c);
}

int readNonnegativeInt(int maxValue, const char* name) {
    char c = nextNonBlank();
    ensuref(isdigit(static_cast<unsigned char>(c)), "expected %s as a nonnegative integer", name);

    string token;
    token.push_back(c);
    while (!inf.eof()) {
        c = inf.readChar();
        if (!isdigit(static_cast<unsigned char>(c))) {
            inf.unreadChar(c);
            break;
        }
        token.push_back(c);
    }

    ensuref(token == "0" || token[0] != '0', "%s has leading zero: %s", name, token.c_str());

    long long value = 0;
    for (char digit : token) {
        value = value * 10 + (digit - '0');
        ensuref(value <= maxValue, "%s exceeds %d", name, maxValue);
    }
    return static_cast<int>(value);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int dataset = 0;
    while (true) {
        inf.skipBlanks();
        if (inf.eof()) {
            break;
        }

        ++dataset;
        setTestCase(dataset);

        // CHECK: The statement only gives n <= 10000, but a dataset of zero jobs
        // would make the described job/server sets absent.
        int n = readNonnegativeInt(10000, "n");
        ensuref(n >= 1, "n must be positive");

        vector<bool> seenJob(n, false);
        for (int i = 0; i < n; ++i) {
            int job = readNonnegativeInt(n - 1, "job_number");
            ensuref(!seenJob[job], "duplicate job number %d", job);
            seenJob[job] = true;

            expectChar(':', "colon");
            expectChar('(', "opening parenthesis");
            int serverCount = readNonnegativeInt(n, "nr_servers");
            expectChar(')', "closing parenthesis");

            set<int> servers;
            for (int j = 0; j < serverCount; ++j) {
                int server = readNonnegativeInt(2 * n - 1, "server");
                ensuref(server >= n, "server %d is outside [%d, %d]", server, n, 2 * n - 1);
                ensuref(servers.insert(server).second,
                        "duplicate server %d in job %d requirement list", server, job);
            }
        }

        for (int job = 0; job < n; ++job) {
            ensuref(seenJob[job], "missing job number %d", job);
        }
    }

    inf.readEof();
}
