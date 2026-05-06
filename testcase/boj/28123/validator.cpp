#include "testlib.h"
#include <cmath>
#include <string>
#include <cassert>

using namespace std;

// Helper: check if a string is a valid integer with no leading zeros (except "0")
bool is_valid_number(const string& s) {
    if (s.empty()) return false;
    if (s.size() > 1 && s[0] == '0') return false;
    for (char c : s) if (!isdigit(c)) return false;
    return true;
}

// Compute log10(x) for x in [1, 10]
long double log10_digit(int x) {
    static const long double vals[11] = {
        0.0L, // dummy
        0.0L, // log10(1)
        0.301029995663981195213738894724493026768189881462108541310427L, // log10(2)
        0.477121254719662437295027903255115309200128864190872767357684L, // log10(3)
        0.602059991327962390427477789448986053536379762924217082620854L, // log10(4)
        0.698970004336018804786261105275506973268189881462108541310427L, // log10(5)
        0.778151250383643559726699620316379747899159687292827189973003L, // log10(6)
        0.845098040014256830560016993653055200710002481846766940165124L, // log10(7)
        0.903089986991943585210163072773972181274902295346746223931281L, // log10(8)
        0.954242509439324874590055806510230618400257728381745534715368L, // log10(9)
        1.0L // log10(10)
    };
    assert(1 <= x && x <= 10);
    return vals[x];
}

// Compute log10(2) with high precision
long double LOG10_2() {
    // 0.301029995663981195213738894724...
    return 0.301029995663981195213738894724493026768189881462108541310427L;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the line as a string, then parse tokens to check for leading zeros
    string line = inf.readLine("[^]+", "input line");
    // Split line into tokens
    vector<string> tokens;
    size_t pos = 0, npos;
    while (pos < line.size()) {
        while (pos < line.size() && isspace(line[pos])) ++pos;
        if (pos >= line.size()) break;
        npos = pos;
        while (npos < line.size() && !isspace(line[npos])) ++npos;
        tokens.push_back(line.substr(pos, npos - pos));
        pos = npos;
    }
    ensuref(tokens.size() == 3, "Expected 3 space-separated integers, got %zu", tokens.size());

    // Check for valid numbers and no leading zeros
    for (int i = 0; i < 3; ++i) {
        ensuref(is_valid_number(tokens[i]), "Token %d ('%s') is not a valid integer or has leading zeros", i+1, tokens[i].c_str());
    }

    // Parse values
    long long n = -1, k = -1;
    int x = -1;
    try {
        n = stoll(tokens[0]);
        k = stoll(tokens[1]);
        x = stoi(tokens[2]);
    } catch (...) {
        ensuref(false, "Failed to parse input as integers");
    }

    // Range checks
    ensuref(1LL <= n && n <= 1000000000000000000LL, "n=%lld is out of range [1, 10^18]", n);
    ensuref(1LL <= k && k <= 1000000000000000000LL, "k=%lld is out of range [1, 10^18]", k);
    ensuref(1 <= x && x <= 9, "x=%d is out of range [1, 9]", x);

    // Check x * 10^{k-1} <= 2^n < (x+1) * 10^{k-1}
    // Use logarithms to avoid overflow
    // log10(2^n) = n * log10(2)
    // log10(x * 10^{k-1}) = log10(x) + (k-1)
    // log10((x+1) * 10^{k-1}) = log10(x+1) + (k-1)
    long double log10_2 = LOG10_2();
    long double log10_2n = n * log10_2;
    long double log10_lo = log10_digit(x) + (long double)(k-1);
    long double log10_hi = log10_digit(x+1) + (long double)(k-1);

    // 2^n >= x * 10^{k-1}  <=>  n*log10(2) >= log10(x) + (k-1)
    // 2^n < (x+1) * 10^{k-1} <=> n*log10(2) < log10(x+1) + (k-1)
    // Allow small epsilon for floating point error
    long double eps = 1e-9L;
    ensuref(log10_2n + eps >= log10_lo - eps, "2^n < x*10^{k-1}: n=%lld, k=%lld, x=%d", n, k, x);
    ensuref(log10_2n < log10_hi + eps, "2^n >= (x+1)*10^{k-1}: n=%lld, k=%lld, x=%d", n, k, x);

    // Check the floating point constraint:
    // |2^n/10^{k-1} - x - 0.5| < 0.5 - 10^{-6}
    // 2^n/10^{k-1} = 10^{n*log10(2) - (k-1)}
    long double log10_ratio = n * log10_2 - (k-1);
    long double ratio = pow(10.0L, log10_ratio);
    long double diff = fabsl(ratio - x - 0.5L);
    ensuref(diff < 0.5L - 1e-6L + eps, "|2^n/10^{k-1} - x - 0.5| = %.12Lf >= 0.5 - 1e-6", diff);

    inf.readEof();
}
