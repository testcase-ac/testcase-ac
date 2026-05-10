#include "testlib.h"
#include <set>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Allowed symbols and their mapping
    set<char> allowed = {'-', '\\', '(', '@', '?', '>', '&', '%', '/'};
    // For fast lookup
    map<char, int> symbol_to_value = {
        {'-', 0},
        {'\\', 1},
        {'(', 2},
        {'@', 3},
        {'?', 4},
        {'>', 5},
        {'&', 6},
        {'%', 7},
        {'/', -1}
    };

    // To check for duplicate lines after '#'
    bool found_hash = false;

    // For global formatting: no extra lines after '#'
    while (true) {
        string line = inf.readLine("[^]*", "octopus_number_or_hash");
        // No need to call readEoln() after readLine()

        // Check for end marker
        if (line == "#") {
            found_hash = true;
            break;
        }

        // Validate length
        ensuref(1 <= (int)line.size() && (int)line.size() <= 8,
            "Each octopus number must have between 1 and 8 symbols, got %d", (int)line.size());

        // Validate each character
        for (int i = 0; i < (int)line.size(); ++i) {
            char c = line[i];
            ensuref(allowed.count(c),
                "Invalid symbol '%c' at position %d in line: '%s'", c, i + 1, line.c_str());
        }
    }

    // After '#' there must be nothing (EOF)
    inf.readEof();
}
