#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 1;
    int commandCount = 1;
    int maxPacket = rnd.next(20, 1000);

    if (mode == 0) {
        n = 1;
        commandCount = rnd.next(1, 18);
    } else if (mode == 1) {
        n = rnd.next(2, 6);
        commandCount = rnd.next(n + 1, n + 12);
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        commandCount = rnd.next(8, 28);
        maxPacket = rnd.next(100, 1000000000);
    } else if (mode == 3) {
        n = rnd.next(1, 12);
        commandCount = rnd.next(1, min(30, n));
    } else {
        n = rnd.next(3, 15);
        commandCount = rnd.next(12, 40);
    }

    vector<int> commands;
    int buffered = 0;
    int nextSmallPacket = rnd.next(1, 20);

    for (int i = 0; i < commandCount; ++i) {
        bool canPop = buffered > 0;
        bool shouldPop = false;

        if (canPop) {
            if (mode == 0) {
                shouldPop = rnd.next(0, 4) == 0;
            } else if (mode == 2) {
                shouldPop = rnd.next(0, 1) == 0;
            } else if (mode == 4) {
                shouldPop = buffered == n || rnd.next(0, 99) < 35;
            } else {
                shouldPop = rnd.next(0, 99) < 25;
            }
        }

        if (shouldPop) {
            commands.push_back(0);
            --buffered;
            continue;
        }

        int packet;
        if (mode == 1 && rnd.next(0, 99) < 70) {
            packet = nextSmallPacket++;
        } else if (mode == 2 && rnd.next(0, 99) < 35) {
            packet = rnd.next(maxPacket - 50, maxPacket);
        } else {
            packet = rnd.next(1, maxPacket);
        }

        commands.push_back(packet);
        if (buffered < n) {
            ++buffered;
        }
    }

    println(n);
    for (int command : commands) {
        println(command);
    }
    println(-1);

    return 0;
}
