#include <utility>
#include <vector>
#include <string>
#include "testlib.h"

using namespace std;

/*
14
push 1
push 2
top
size
empty
pop
pop
pop
size
empty
pop
push 3
empty
top
*/
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 10);
    vector<string> commands = {"push", "pop", "size", "empty", "top"};
    vector<string> output;
    bool allPush = true;
    for (int i = 0; i < N; i++) {
        int c = rnd.next(0, 4);
        if(c == 0) {
            output.push_back(commands[c] + " " + to_string(rnd.next(1, 10)));
        } else {
            allPush = false;
            output.push_back(commands[c]);
        }
    }
    if(allPush) {
        int c = rnd.next(1, 4);
        output.push_back(commands[c]);
    }
    println(output.size());
    for (int i = 0; i < output.size(); i++) {
        println(output[i]);
    }
}
