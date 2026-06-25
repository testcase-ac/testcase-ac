#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct Fraction {
    long long num;
    long long den;
};

struct Term {
    bool positive;
    Fraction coef;
    int exp;
};

static Fraction reduced(long long num, long long den) {
    long long g = gcd(num, den);
    return {num / g, den / g};
}

static string coefficientString(const Fraction& coef, int exp) {
    if (exp > 0 && coef.num == 1 && coef.den == 1) {
        return "";
    }
    if (coef.den == 1) {
        return to_string(coef.num);
    }
    return to_string(coef.num) + "/" + to_string(coef.den);
}

static string termString(const Term& term, bool first) {
    string result;
    if (term.positive) {
        if (!first) {
            result += "+";
        }
    } else {
        result += "-";
    }

    result += coefficientString(term.coef, term.exp);
    if (term.exp > 0) {
        result += "x";
        if (term.exp > 1) {
            result += "^" + to_string(term.exp);
        }
    }
    return result;
}

static string polynomialString(const vector<Term>& terms) {
    string result;
    for (int i = 0; i < (int)terms.size(); ++i) {
        result += termString(terms[i], i == 0);
    }
    return result;
}

static vector<int> chooseIntegratedExponents() {
    vector<int> pool;
    int mode = rnd.next(0, 3);

    if (mode == 0) {
        pool = {2, 3, 4, 5, 6, 7};
    } else if (mode == 1) {
        pool = {2, 3, 10, 50, 250, 499, 500};
    } else {
        int high = rnd.next(6, 500);
        for (int e = max(2, high - 8); e <= high; ++e) {
            pool.push_back(e);
        }
        pool.push_back(2);
        pool.push_back(500);
    }

    sort(pool.begin(), pool.end());
    pool.erase(unique(pool.begin(), pool.end()), pool.end());
    shuffle(pool.begin(), pool.end());

    int count = rnd.next(1, min(5, (int)pool.size()));
    pool.resize(count);
    sort(pool.begin(), pool.end(), greater<int>());
    return pool;
}

static Fraction randomIntegratedCoefficient() {
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return {1, 1};
    }
    if (mode == 1) {
        return {rnd.next(2, 12), 1};
    }

    int den = rnd.next(2, 20);
    int num = rnd.next(1, min(500, den * 4));
    Fraction f = reduced(num, den);
    if (f.den == 1) {
        f.den = 2;
        f = reduced(f.num, f.den);
    }
    return f;
}

static vector<Term> makeIntegratedTerms() {
    vector<Term> terms;
    for (int exp : chooseIntegratedExponents()) {
        terms.push_back({rnd.next(0, 1) == 1, randomIntegratedCoefficient(), exp});
    }
    return terms;
}

static vector<Term> differentiateTwice(const vector<Term>& integratedTerms) {
    vector<Term> candidate;
    for (const Term& term : integratedTerms) {
        long long multiplier = 1LL * term.exp * (term.exp - 1);
        Fraction coef = reduced(term.coef.num * multiplier, term.coef.den);
        candidate.push_back({term.positive, coef, term.exp - 2});
    }
    return candidate;
}

static void mutateCandidate(vector<Term>& candidate) {
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        int at = rnd.next(0, (int)candidate.size() - 1);
        candidate[at].positive = !candidate[at].positive;
    } else if (mode == 1) {
        int at = rnd.next(0, (int)candidate.size() - 1);
        long long nextNum = candidate[at].coef.num + rnd.next(1, 5);
        candidate[at].coef = reduced(nextNum, candidate[at].coef.den);
    } else if (candidate.size() >= 2) {
        candidate.pop_back();
    } else {
        candidate[0].coef = {1, 1};
        candidate[0].exp = min(500, candidate[0].exp + 1);
    }
}

static string integratedString(vector<Term> terms) {
    string result = polynomialString(terms);
    result += "+Cx+D";
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        vector<Term> integratedTerms = makeIntegratedTerms();
        vector<Term> candidate = differentiateTwice(integratedTerms);

        if (tc % 3 == 2) {
            mutateCandidate(candidate);
        }

        println(integratedString(integratedTerms), polynomialString(candidate));
    }

    return 0;
}
