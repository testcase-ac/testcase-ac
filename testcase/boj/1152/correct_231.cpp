#include <cstdio>

int main() {
    char input[1000002];
    if (std::fgets(input, sizeof(input), stdin) == nullptr) {
        return 0;
    }

    int count = 0;
    for (int i = 0; input[i] != '\0' && input[i] != '\n'; ++i) {
        if (input[i] != ' ' && (i == 0 || input[i - 1] == ' ')) {
            ++count;
        }
    }

    std::printf("%d\n", count);
}
