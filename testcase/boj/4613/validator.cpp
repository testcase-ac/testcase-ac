#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_PACKETS = 100000;
    const int MAX_LEN = 255;
    int packet_count = 0;
    while (true) {
        // Read one line (packet or sentinel)
        // "[^]+" matches any characters except newline, at least one char
        string s = inf.readLine("[^]+", "line");
        // Check for sentinel
        if (s == "#") {
            break;
        }
        packet_count++;
        ensuref(packet_count <= MAX_PACKETS,
                "Number of packets exceeds limit %d (line %d)", MAX_PACKETS, packet_count);
        int len = (int)s.length();
        ensuref(len >= 1 && len <= MAX_LEN,
                "Packet length must be between 1 and %d, got %d at line %d", 
                MAX_LEN, len, packet_count);
        // First and last character must be uppercase letter
        char c0 = s[0];
        ensuref(c0 >= 'A' && c0 <= 'Z',
                "Packet line %d must start with uppercase letter, got '%c'", 
                packet_count, c0);
        char c1 = s[len-1];
        ensuref(c1 >= 'A' && c1 <= 'Z',
                "Packet line %d must end with uppercase letter, got '%c'", 
                packet_count, c1);
        // All characters must be either uppercase letter or space
        for (int i = 0; i < len; i++) {
            char c = s[i];
            bool ok = (c >= 'A' && c <= 'Z') || (c == ' ');
            ensuref(ok,
                    "Invalid character in packet line %d at position %d: '%c'",
                    packet_count, i+1, c);
        }
    }
    // After sentinel line, require EOF immediately
    inf.readEof();
    return 0;
}
