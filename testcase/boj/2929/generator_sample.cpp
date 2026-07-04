#include "testlib.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int opcodeCount;
    int instructionCount;
    int maxParamCount;

    if (mode == 0) {
        opcodeCount = rnd.next(1, 3);
        instructionCount = rnd.next(1, 8);
        maxParamCount = rnd.next(0, 3);
    } else if (mode == 1) {
        opcodeCount = rnd.next(1, 5);
        instructionCount = rnd.next(8, 25);
        maxParamCount = rnd.next(0, 7);
    } else if (mode == 2) {
        opcodeCount = 26;
        instructionCount = rnd.next(10, 45);
        maxParamCount = rnd.next(0, 5);
    } else if (mode == 3) {
        opcodeCount = rnd.next(1, 8);
        instructionCount = rnd.next(20, 70);
        maxParamCount = rnd.next(0, 2);
    } else if (mode == 4) {
        opcodeCount = rnd.next(1, 10);
        instructionCount = rnd.next(1, 30);
        maxParamCount = rnd.next(8, 20);
    } else {
        opcodeCount = rnd.next(1, 26);
        instructionCount = rnd.next(1, 90);
        maxParamCount = rnd.next(0, 7);
    }

    vector<char> opcodes;
    for (int i = 0; i < opcodeCount; ++i) {
        opcodes.push_back(char('A' + i));
    }
    shuffle(opcodes.begin(), opcodes.end());

    map<char, int> paramCount;
    for (char opcode : opcodes) {
        paramCount[opcode] = rnd.next(0, maxParamCount);
    }

    string program;
    for (int i = 0; i < instructionCount; ++i) {
        char opcode = rnd.any(opcodes);
        int needed = 1 + paramCount[opcode];
        if (int(program.size()) + needed > 200) {
            break;
        }

        program += opcode;
        for (int j = 0; j < paramCount[opcode]; ++j) {
            char param = char('a' + rnd.next(0, mode <= 1 ? 5 : 25));
            program += param;
        }
    }

    if (program.empty()) {
        char opcode = opcodes[0];
        program += opcode;
        for (int j = 0; j < paramCount[opcode] && int(program.size()) < 200; ++j) {
            program += char('a' + rnd.next(0, 25));
        }
    }

    println(program);
    return 0;
}
