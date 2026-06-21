#include "testlib.h"
#include <map>
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(7, 3500, "N");
    inf.readEoln();

    map<string, int> occurrences;
    map<string, set<int>> values;
    for (int i = 0; i < n; ++i) {
        string variable = inf.readToken("B|E|S|I|G|O|M", "variable");
        inf.readSpace();
        int value = inf.readInt(-100000, 100000, "value");
        inf.readEoln();

        ++occurrences[variable];
        ensuref(values[variable].insert(value).second,
                "duplicate value for variable %s at row %d: %d",
                variable.c_str(), i + 2, value);
    }

    const string variables[] = {"B", "E", "S", "I", "G", "O", "M"};
    for (const string& variable : variables) {
        ensuref(occurrences[variable] >= 1,
                "variable %s does not appear", variable.c_str());
        ensuref(occurrences[variable] <= 500,
                "variable %s appears %d times", variable.c_str(), occurrences[variable]);
    }

    inf.readEof();
    return 0;
}
