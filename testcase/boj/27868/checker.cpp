#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
int dorm;
vector<int> acceleration;

long long simulateCommand(const string& command,
                          long long startFloor,
                          const char* streamName,
                          TResult invalidResult) {
    long long floor = startFloor;
    long long speed = 0;

    for (int i = 0; i < (int)command.size(); ++i) {
        int currentFloor = (int)floor;
        if (command[i] == '+') {
            speed += acceleration[currentFloor - 1];
        } else if (command[i] == '-') {
            speed -= acceleration[currentFloor - 1];
        }

        floor += speed;
        if (floor < 1 || n < floor) {
            quitf(invalidResult,
                  "%s command leaves building after character %d: floor=%lld speed=%lld",
                  streamName,
                  i + 1,
                  floor,
                  speed);
        }
    }

    if (speed != 0) {
        quitf(invalidResult,
              "%s command must finish with speed 0, got %lld",
              streamName,
              speed);
    }

    return floor;
}

string readCommand(InStream& stream, const char* streamName, TResult invalidResult) {
    string command = stream.readToken("[+\\-0]{1,200000}", format("%s command", streamName).c_str());
    if (!stream.seekEof()) {
        quitf(invalidResult, "extra output after %s command", streamName);
    }
    return command;
}

void validateReturnCommand(InStream& stream,
                           const char* streamName,
                           TResult invalidResult,
                           long long office) {
    string command = readCommand(stream, streamName, invalidResult);
    long long finalFloor = simulateCommand(command, office, streamName, invalidResult);
    if (finalFloor != dorm) {
        quitf(invalidResult,
              "%s command finishes at floor %lld instead of dorm floor %d",
              streamName,
              finalFloor,
              dorm);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    dorm = inf.readInt();
    acceleration.resize(n);
    for (int i = 0; i < n; ++i) {
        acceleration[i] = inf.readInt();
    }
    string commuteCommand = inf.readToken();

    long long office = simulateCommand(commuteCommand, dorm, "input commute", _fail);
    if (office == dorm) {
        quitf(_fail, "input commute command finishes at dorm floor %d", dorm);
    }

    validateReturnCommand(ans, "jury", _fail, office);
    validateReturnCommand(ouf, "participant", _wa, office);

    quitf(_ok, "valid return command");
}
