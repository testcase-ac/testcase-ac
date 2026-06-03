#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

namespace {

constexpr int kMaxValue = 1000000000;

struct Machine {
    vector<string> program;
    vector<int> inputs;
};

string num(int value) {
    return "NUM " + to_string(value);
}

int smallValue() {
    return rnd.next(0, 25);
}

int boundaryValue() {
    vector<int> values = {0, 1, 2, 3, 10, 999999999, kMaxValue};
    return rnd.any(values);
}

vector<int> makeInputs(int count) {
    vector<int> inputs;
    for (int i = 0; i < count; ++i) {
        if (rnd.next(100) < 45) {
            inputs.push_back(boundaryValue());
        } else if (rnd.next(100) < 70) {
            inputs.push_back(rnd.next(0, 100));
        } else {
            inputs.push_back(rnd.next(0, kMaxValue));
        }
    }
    return inputs;
}

Machine makeAffineMachine() {
    int add = rnd.next(0, 20);
    int mul = rnd.next(1, 9);
    vector<string> program = {
        num(add),
        "ADD",
        num(mul),
        "MUL",
    };
    if (rnd.next(2) == 0) {
        program.push_back("INV");
    }
    return {program, makeInputs(rnd.next(3, 7))};
}

Machine makeDivisionMachine() {
    int divisor = rnd.next(1, 17);
    vector<string> program = {
        rnd.next(2) == 0 ? "INV" : "DUP",
        num(divisor),
        rnd.next(2) == 0 ? "DIV" : "MOD",
    };
    if (program[0] == "DUP") {
        program.insert(program.begin() + 1, rnd.next(2) == 0 ? "ADD" : "SUB");
    }
    return {program, makeInputs(rnd.next(4, 8))};
}

Machine makeStackShapeMachine() {
    vector<string> program;
    int copies = rnd.next(2, 8);
    for (int i = 0; i < copies; ++i) {
        program.push_back("DUP");
        if (rnd.next(100) < 35) {
            program.push_back(num(smallValue()));
        }
    }
    int reductions = rnd.next(0, copies);
    vector<string> ops = {"ADD", "SUB", "MUL"};
    for (int i = 0; i < reductions; ++i) {
        program.push_back(rnd.any(ops));
    }
    return {program, makeInputs(rnd.next(2, 5))};
}

Machine makeRuntimeErrorMachine() {
    vector<vector<string>> programs = {
        {"POP", "POP"},
        {"SWP"},
        {num(0), "DIV"},
        {num(0), "MOD"},
        {num(kMaxValue), "ADD"},
        {num(kMaxValue), num(2), "MUL"},
    };
    vector<string> program = rnd.any(programs);
    if (rnd.next(2) == 0) {
        program.insert(program.begin(), num(smallValue()));
    }
    return {program, makeInputs(rnd.next(3, 6))};
}

Machine makeCommandMixMachine() {
    vector<string> program = {
        "DUP",
        num(rnd.next(1, 100)),
        "SWP",
        rnd.next(2) == 0 ? "SUB" : "ADD",
        "DUP",
        rnd.next(2) == 0 ? "INV" : num(rnd.next(1, 12)),
        rnd.next(2) == 0 ? "ADD" : "MUL",
    };
    if (rnd.next(2) == 0) {
        program.push_back(num(rnd.next(1, 9)));
        program.push_back(rnd.next(2) == 0 ? "DIV" : "MOD");
    }
    return {program, makeInputs(rnd.next(3, 7))};
}

Machine makeMachine() {
    int mode = rnd.next(5);
    if (mode == 0) {
        return makeAffineMachine();
    }
    if (mode == 1) {
        return makeDivisionMachine();
    }
    if (mode == 2) {
        return makeStackShapeMachine();
    }
    if (mode == 3) {
        return makeRuntimeErrorMachine();
    }
    return makeCommandMixMachine();
}

void printMachine(const Machine& machine) {
    for (const string& line : machine.program) {
        println(line);
    }
    println("END");
    println(static_cast<int>(machine.inputs.size()));
    for (int value : machine.inputs) {
        println(value);
    }
    println("");
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int machineCount = rnd.next(3, 7);
    for (int i = 0; i < machineCount; ++i) {
        printMachine(makeMachine());
    }
    println("QUIT");

    return 0;
}
