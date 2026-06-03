#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

namespace {

constexpr int kMaxCommands = 100000;
constexpr int kMaxStackSize = 999;
constexpr int kMaxRuns = 10000;
constexpr long long kMaxValue = 1000000000LL;

bool isCanonicalNonNegativeInteger(const string& s) {
    if (s.empty()) {
        return false;
    }
    if (s.size() > 1 && s[0] == '0') {
        return false;
    }
    for (char c : s) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

long long parseNonNegativeInteger(const string& s) {
    long long value = 0;
    for (char c : s) {
        value = value * 10 + (c - '0');
        ensuref(value <= kMaxValue, "integer value is too large: %s", s.c_str());
    }
    return value;
}

bool isPlainCommand(const string& line) {
    static const vector<string> commands = {
        "POP", "INV", "DUP", "SWP", "ADD", "SUB", "MUL", "DIV", "MOD"};
    for (const string& command : commands) {
        if (line == command) {
            return true;
        }
    }
    return false;
}

void updateStackDepth(const string& command, int& depth, int machineIndex,
                      int commandIndex) {
    if (command == "NUM" || command == "DUP") {
        ++depth;
    } else if (command == "POP" || command == "ADD" || command == "SUB" ||
               command == "MUL" || command == "DIV" || command == "MOD") {
        --depth;
    }

    ensuref(depth < kMaxStackSize + 1,
            "machine %d command %d can require stack size %d",
            machineIndex, commandIndex, depth);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int machineIndex = 0;
    while (true) {
        string line = inf.readLine("[^]*", "program_or_quit");
        if (line == "QUIT") {
            break;
        }

        ++machineIndex;
        // CHECK: The statement gives no machine-count limit; keep the
        // validator bounded while allowing a very large number of machines.
        ensuref(machineIndex <= 100000, "too many machines: %d", machineIndex);

        int commandCount = 0;
        int stackDepth = 1;
        while (line != "END") {
            ++commandCount;
            ensuref(commandCount <= kMaxCommands,
                    "machine %d has more than %d commands",
                    machineIndex, kMaxCommands);

            string command;
            if (line.rfind("NUM ", 0) == 0) {
                command = "NUM";
                string valueToken = line.substr(4);
                ensuref(isCanonicalNonNegativeInteger(valueToken),
                        "invalid NUM argument in machine %d command %d: %s",
                        machineIndex, commandCount, valueToken.c_str());
                parseNonNegativeInteger(valueToken);
            } else {
                command = line;
                ensuref(isPlainCommand(line),
                        "invalid command in machine %d command %d: %s",
                        machineIndex, commandCount, line.c_str());
            }

            updateStackDepth(command, stackDepth, machineIndex, commandCount);
            line = inf.readLine("[^]*", "program_line");
        }

        int n = inf.readInt(0, kMaxRuns, "N");
        inf.readEoln();
        for (int i = 0; i < n; ++i) {
            inf.readLong(0LL, kMaxValue, "V_i");
            inf.readEoln();
        }

        string blank = inf.readLine("[^]*", "machine_separator");
        ensuref(blank.empty(), "machine %d must end with an empty line",
                machineIndex);
    }

    inf.readEof();
    return 0;
}
