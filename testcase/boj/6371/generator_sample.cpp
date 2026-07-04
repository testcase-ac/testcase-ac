#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static string randomState() {
    string state(26, '0');
    for (char& bit : state) {
        bit = char('0' + rnd.next(0, 1));
    }
    return state;
}

static vector<string> makeDirectCircuit(char label) {
    int dashes = rnd.next(1, 8);
    return {string(1, label) + string(dashes, '-') + "?"};
}

static vector<string> makeTwoInputGate(char a, char b) {
    bool isAnd = rnd.next(0, 1) == 0;
    bool invertTop = rnd.next(0, 3) == 0;
    bool invertBottom = rnd.next(0, 3) == 0;
    bool invertOut = rnd.next(0, 3) == 0;

    string top = string(1, a) + (invertTop ? "-o:\\" : "---:\\");
    string middle = "    : ";
    middle += isAnd ? ')' : '>';
    middle += invertOut ? "o---?" : "---?";
    string bottom = string(1, b) + (invertBottom ? "-o:/" : "---:/");

    return {top, middle, bottom};
}

static vector<string> makeForkCircuit(char a, char b, char c) {
    bool outerAnd = rnd.next(0, 1) == 0;
    bool innerAnd = rnd.next(0, 1) == 0;
    bool invertInner = rnd.next(0, 1) == 0;
    bool invertC = rnd.next(0, 1) == 0;

    string row3 = "    +---:/     : ";
    row3 += outerAnd ? ')' : '>';
    row3 += "---?";
    string row4 = "    |      ";
    row4 += c;
    row4 += invertC ? "--o:/" : "---:/";

    return {
        string(1, a) + "---+",
        "    |",
        "    +---:\\",
        string("        : ") + (innerAnd ? ")" : ">") + (invertInner ? "o---:\\" : "----:\\"),
        row3,
        row4,
        string(1, b) + "---+",
    };
}

static vector<string> makeCircuit() {
    vector<char> labels = {'A', 'B', 'C', 'D', 'E'};
    shuffle(labels.begin(), labels.end());

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return makeDirectCircuit(labels[0]);
    }
    if (mode <= 2) {
        return makeTwoInputGate(labels[0], labels[1]);
    }
    return makeForkCircuit(labels[0], labels[1], labels[2]);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int circuits = rnd.next(1, 3);
    for (int circuit = 0; circuit < circuits; ++circuit) {
        vector<string> diagram = makeCircuit();
        for (const string& line : diagram) {
            println(line);
        }
        println("*");

        int states = rnd.next(1, 4);
        vector<string> inputStates;
        inputStates.push_back(string(26, '0'));
        if (states >= 2) {
            inputStates.push_back(string(26, '1'));
        }
        while ((int)inputStates.size() < states) {
            inputStates.push_back(randomState());
        }
        shuffle(inputStates.begin(), inputStates.end());

        for (const string& state : inputStates) {
            println(state);
        }
        println("*");
    }

    return 0;
}
