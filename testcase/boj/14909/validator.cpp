#include "testlib.h"
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single line of input containing up to 1,000,000 integers
    // We read the entire line (at least one character)
    string line = inf.readLine("[^]+", "line");
    
    // Split by whitespace into tokens
    istringstream iss(line);
    vector<string> tokens;
    string tok;
    while (iss >> tok) {
        tokens.push_back(tok);
    }
    
    // Must have at least one integer, at most 1e6
    int n = tokens.size();
    ensuref(n >= 1, "There must be at least one integer on the line");
    ensuref(n <= 1000000, "Number of integers (%d) exceeds limit 1e6", n);
    
    // Validate each token is a valid integer in [-1e6, 1e6] without '+' sign
    for (int i = 0; i < n; i++) {
        const string &s = tokens[i];
        // Disallow a leading '+' sign
        ensuref(s.empty() == false, "Empty token at position %d", i);
        ensuref(s[0] != '+', "Leading '+' not allowed in token %d: '%s'", i, s.c_str());
        
        // Parse with strtol to ensure full match and range
        char *endptr = nullptr;
        errno = 0;
        long val = strtol(s.c_str(), &endptr, 10);
        // Check that entire string was consumed and no overflow/underflow
        ensuref(endptr != s.c_str() && *endptr == '\0',
                "Invalid integer format at token %d: '%s'", i, s.c_str());
        ensuref(errno == 0,
                "Integer overflow/underflow at token %d: '%s'", i, s.c_str());
        // Check bounds
        ensuref(val >= -1000000 && val <= 1000000,
                "Integer out of range [-1e6,1e6] at token %d: %ld", i, val);
    }

    // After the single line, there must be EOF immediately
    inf.readEof();
    return 0;
}
