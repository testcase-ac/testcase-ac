#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int start = inf.readInt(1, n, "s");
    inf.readEoln();

    vector<int> acceleration = inf.readInts(n, 1, 200000, "a_i");
    inf.readEoln();

    string command = inf.readToken("[+\\-0]{1,200000}", "command");
    inf.readEoln();
    inf.readEof();

    long long floor = start;
    long long speed = 0;
    for (int i = 0; i < (int)command.size(); ++i) {
        int current_floor = (int)floor;
        if (command[i] == '+') {
            speed += acceleration[current_floor - 1];
        } else if (command[i] == '-') {
            speed -= acceleration[current_floor - 1];
        }

        floor += speed;
        ensuref(1 <= floor && floor <= n,
                "command leaves building after character %d: floor=%lld speed=%lld",
                i + 1,
                floor,
                speed);
    }

    ensuref(speed == 0, "command must finish with speed 0, got %lld", speed);
    ensuref(floor != start,
            "command must finish at a floor different from S, got %lld",
            floor);
}
