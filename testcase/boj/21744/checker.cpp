#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using namespace std;
using boost::multiprecision::cpp_int;

struct Rational {
    cpp_int num;
    cpp_int den;
};

struct Claim {
    int terms;
};

int n;
int k;

cpp_int gcdInt(cpp_int a, cpp_int b) {
    while (b != 0) {
        cpp_int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

Rational normalize(Rational value) {
    cpp_int g = gcdInt(value.num, value.den);
    value.num /= g;
    value.den /= g;
    return value;
}

cpp_int pow10(int exponent) {
    cpp_int result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= 10;
    }
    return result;
}

cpp_int parseDigits(const string& s) {
    cpp_int result = 0;
    for (char c : s) {
        result *= 10;
        result += c - '0';
    }
    return result;
}

string toString(cpp_int value) {
    return value.convert_to<string>();
}

string canonicalDecimal(const Rational& value) {
    cpp_int integerPart = value.num / value.den;
    cpp_int rem = value.num % value.den;
    string result = toString(integerPart);
    if (rem == 0) {
        return result;
    }

    map<cpp_int, int> seen;
    vector<int> digits;
    int repeatStart = -1;
    while (rem != 0) {
        auto it = seen.find(rem);
        if (it != seen.end()) {
            repeatStart = it->second;
            break;
        }
        seen[rem] = (int)digits.size();
        rem *= 10;
        digits.push_back((rem / value.den).convert_to<int>());
        rem %= value.den;
    }

    result += ".";
    if (repeatStart == -1) {
        for (int digit : digits) {
            result += char('0' + digit);
        }
    } else {
        for (int i = 0; i < repeatStart; ++i) {
            result += char('0' + digits[i]);
        }
        result += "(";
        for (int i = repeatStart; i < (int)digits.size(); ++i) {
            result += char('0' + digits[i]);
        }
        result += ")";
    }
    return result;
}

bool allBeautifulDigits(const string& digits) {
    for (char c : digits) {
        if (c != '0' && c != char('0' + k)) {
            return false;
        }
    }
    return true;
}

Rational parseTerm(InStream& stream, const string& token, int index) {
    string field = format("term %d", index).c_str();
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", field.c_str());
    }

    size_t pos = 0;
    while (pos < token.size() && isdigit(token[pos])) {
        ++pos;
    }
    string integerPart = token.substr(0, pos);
    if (integerPart.empty()) {
        stream.quitf(_wa, "%s has no integer part", field.c_str());
    }
    if (integerPart.size() > 1 && integerPart[0] == '0') {
        stream.quitf(_wa, "%s has leading zeroes", field.c_str());
    }

    string preperiod;
    string period;
    bool hasFraction = false;
    bool hasPeriod = false;

    if (pos < token.size() && token[pos] == '.') {
        hasFraction = true;
        ++pos;
        while (pos < token.size() && isdigit(token[pos])) {
            preperiod += token[pos++];
        }
        if (pos < token.size() && token[pos] == '(') {
            hasPeriod = true;
            ++pos;
            while (pos < token.size() && isdigit(token[pos])) {
                period += token[pos++];
            }
            if (pos >= token.size() || token[pos] != ')') {
                stream.quitf(_wa, "%s has an unclosed period", field.c_str());
            }
            ++pos;
            if (period.empty()) {
                stream.quitf(_wa, "%s has an empty period", field.c_str());
            }
        } else if (preperiod.empty()) {
            stream.quitf(_wa, "%s has an empty fractional part", field.c_str());
        }
        if (preperiod.size() > 100 || period.size() > 100) {
            stream.quitf(_wa, "%s fractional preperiod or period is longer than 100 digits", field.c_str());
        }
    }
    if (pos != token.size()) {
        stream.quitf(_wa, "%s has invalid trailing characters", field.c_str());
    }

    if (!allBeautifulDigits(integerPart + preperiod + period)) {
        stream.quitf(_wa, "%s contains a digit other than 0 or %d", field.c_str(), k);
    }

    cpp_int numerator = parseDigits(integerPart);
    cpp_int denominator = 1;
    if (hasFraction) {
        cpp_int scale = pow10((int)preperiod.size());
        numerator *= scale;
        numerator += preperiod.empty() ? 0 : parseDigits(preperiod);
        denominator = scale;
        if (hasPeriod) {
            cpp_int periodBase = pow10((int)period.size()) - 1;
            numerator = numerator * periodBase + parseDigits(period);
            denominator *= periodBase;
        }
    }

    Rational value = normalize({numerator, denominator});
    if (value.num == 0) {
        stream.quitf(_wa, "%s is not positive", field.c_str());
    }

    string canonical = canonicalDecimal(value);
    if (canonical != token) {
        stream.quitf(_wa, "%s is not in minimal form: expected %s, found %s",
                     field.c_str(), canonical.c_str(), token.c_str());
    }
    return value;
}

string readCompactOutput(InStream& stream) {
    string compact;
    while (!stream.seekEof()) {
        compact += stream.readToken();
    }
    return compact;
}

Claim readClaim(InStream& stream) {
    string text = readCompactOutput(stream);
    string prefix = to_string(n) + "=";
    if (text.rfind(prefix, 0) != 0) {
        stream.quitf(_wa, "decomposition must start with '%s'", prefix.c_str());
    }

    string rest = text.substr(prefix.size());
    if (rest.empty()) {
        stream.quitf(_wa, "decomposition has no terms");
    }

    Rational sum{0, 1};
    int terms = 0;
    size_t start = 0;
    while (start <= rest.size()) {
        size_t plus = rest.find('+', start);
        string token = rest.substr(start, plus == string::npos ? string::npos : plus - start);
        if (token.empty()) {
            stream.quitf(_wa, "empty term in decomposition");
        }
        Rational value = parseTerm(stream, token, terms + 1);
        sum.num = sum.num * value.den + value.num * sum.den;
        sum.den *= value.den;
        sum = normalize(sum);
        ++terms;
        if (plus == string::npos) {
            break;
        }
        start = plus + 1;
    }

    if (sum.num != cpp_int(n) * sum.den) {
        stream.quitf(_wa, "terms do not sum to %d", n);
    }
    return {terms};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000000000, "n");
    k = inf.readInt(1, 9, "k");

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.terms > jury.terms) {
        quitf(_wa, "participant uses %d terms, jury uses %d", participant.terms, jury.terms);
    }
    if (participant.terms < jury.terms) {
        quitf(_fail, "participant uses %d terms, better than jury's %d", participant.terms, jury.terms);
    }
    quitf(_ok, "valid decomposition with %d term(s)", participant.terms);
}
