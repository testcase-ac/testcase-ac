#include "testlib.h"

#include <cstdarg>
#include <cstdio>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct CaseData {
    int n;
    int t;
};

vector<CaseData> cases;
vector<int> primes;

void quitInvalid(InStream& stream, const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    stream.quitf(_wa, "%s", buffer);
}

int modulo(const string& value, int divisor) {
    int result = 0;
    for (char ch : value) {
        result = (result * 10 + (ch - '0')) % divisor;
    }
    return result;
}

string addTwo(const string& value) {
    string result = value;
    int carry = 2;
    for (int i = int(result.size()) - 1; i >= 0 && carry > 0; --i) {
        int digit = result[i] - '0' + carry;
        result[i] = char('0' + digit % 10);
        carry = digit / 10;
    }
    if (carry > 0) {
        result.insert(result.begin(), char('0' + carry));
    }
    return result;
}

void validateApparentPrime(InStream& stream, const string& value, int t, int caseNo, const char* name) {
    for (int divisor : primes) {
        if (divisor > t) {
            break;
        }
        if (modulo(value, divisor) == 0) {
            quitInvalid(stream, "case %d: %s is divisible by %d", caseNo, name, divisor);
        }
    }
}

vector<string> readAns(InStream& stream) {
    vector<string> answer;
    for (int caseNo = 1; caseNo <= int(cases.size()); ++caseNo) {
        const CaseData& cd = cases[caseNo - 1];
        string p = stream.readToken("[0-9]+", format("case %d p", caseNo).c_str());

        if (int(p.size()) != cd.n) {
            quitInvalid(stream, "case %d: p has %d digits instead of %d", caseNo, int(p.size()), cd.n);
        }
        if (p[0] == '0') {
            quitInvalid(stream, "case %d: p has a leading zero", caseNo);
        }

        string pPlusTwo = addTwo(p);
        if (int(pPlusTwo.size()) != cd.n) {
            quitInvalid(stream, "case %d: p + 2 has %d digits instead of %d", caseNo, int(pPlusTwo.size()), cd.n);
        }

        validateApparentPrime(stream, p, cd.t, caseNo, "p");
        validateApparentPrime(stream, pPlusTwo, cd.t, caseNo, "p + 2");
        answer.push_back(p);
    }

    if (!stream.seekEof()) {
        quitInvalid(stream, "extra output after the expected %d answer token(s)", int(cases.size()));
    }
    return answer;
}

vector<int> sievePrimes(int limit) {
    vector<int> result;
    vector<bool> composite(limit + 1, false);
    for (int i = 2; i <= limit; ++i) {
        if (!composite[i]) {
            result.push_back(i);
            if (1LL * i * i <= limit) {
                for (long long j = 1LL * i * i; j <= limit; j += i) {
                    composite[int(j)] = true;
                }
            }
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    while (true) {
        int n = inf.readInt();
        int t = inf.readInt();
        if (n == 0 && t == 0) {
            break;
        }
        cases.push_back({n, t});
    }
    primes = sievePrimes(8000);

    ans.maxTokenLength = 6000;
    ouf.maxTokenLength = 6000;

    readAns(ans);
    readAns(ouf);

    quitf(_ok, "all %d apparent twin prime witness(es) are valid", int(cases.size()));
}
