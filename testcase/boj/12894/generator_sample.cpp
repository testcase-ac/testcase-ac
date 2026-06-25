#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>

using namespace std;

string randomString(int n, int alphabetSize) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(char('a' + rnd.next(alphabetSize)));
    }
    return s;
}

string equivalentVariant(const string& s) {
    int n = int(s.size());
    if (n % 2 == 1 || n == 1) {
        return s;
    }

    string left = equivalentVariant(s.substr(0, n / 2));
    string right = equivalentVariant(s.substr(n / 2));
    if (rnd.next(2) == 0) {
        return left + right;
    }
    return right + left;
}

string canonicalForm(const string& s) {
    int n = int(s.size());
    if (n % 2 == 1) {
        return s;
    }

    string left = canonicalForm(s.substr(0, n / 2));
    string right = canonicalForm(s.substr(n / 2));
    if (right < left) {
        swap(left, right);
    }
    return left + right;
}

pair<string, string> makeDifferentPair(int n, int alphabetSize) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        string a = randomString(n, alphabetSize);
        string b = a;
        int pos = rnd.next(n);
        char old = b[pos];
        char replacement = old;
        while (replacement == old) {
            replacement = char('a' + rnd.next(alphabetSize));
        }
        b[pos] = replacement;

        if (canonicalForm(a) != canonicalForm(b)) {
            return {a, b};
        }
    }

    string a(n, 'a');
    string b = a;
    b[n - 1] = 'b';
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int alphabetSize = rnd.next(2, 5);
    int n;
    string a, b;

    if (mode == 0) {
        n = rnd.next(1, 24);
        a = randomString(n, alphabetSize);
        b = a;
    } else if (mode == 1) {
        int exponent = rnd.next(0, 5);
        n = 1 << exponent;
        a = randomString(n, alphabetSize);
        b = equivalentVariant(a);
    } else if (mode == 2) {
        n = rnd.next(1, 24);
        auto pair = makeDifferentPair(n, alphabetSize);
        a = pair.first;
        b = pair.second;
    } else if (mode == 3) {
        n = rnd.next(1, 12) * 2 + 1;
        auto pair = makeDifferentPair(n, alphabetSize);
        a = pair.first;
        b = pair.second;
    } else {
        int lengths[] = {1, 2, 4, 8, 16, 32};
        n = lengths[rnd.next(6)];
        a = randomString(n, alphabetSize);
        if (rnd.next(2) == 0) {
            b = equivalentVariant(a);
        } else {
            auto pair = makeDifferentPair(n, alphabetSize);
            a = pair.first;
            b = pair.second;
        }
    }

    println(a);
    println(b);
    return 0;
}
