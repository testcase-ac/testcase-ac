//
// Official Solution
// Author: Jongseo Lee (@leejseo)
//
#include <cstring>
#include <iostream>
#include <string>

const int UNDEF = -1;

std::string ANS[] = {
    "Second",
    "First",
};

int N, M, K, Q;
int D[301][301];
char blocked[301][301];

inline bool valid(int i, int j)
{
    return 0 <= i && i < N && 0 <= j && j < M && blocked[i][j] == '.';
}

int solve(int i, int j)
{
    if (D[i][j] != UNDEF)
    {
        return D[i][j];
    }
    if (valid(i + 1, j) && !solve(i + 1, j))
    {
        return D[i][j] = 1;
    }
    if (valid(i, j + 1) && !solve(i, j + 1))
    {
        return D[i][j] = 1;
    }
    for (int k = 1; k <= K; k++)
    {
        if (valid(i + k, j + k) && !solve(i + k, j + k))
        {
            return D[i][j] = 1;
        }
    }
    return D[i][j] = 0;
}

int main(void)
{
    memset(D, UNDEF, sizeof(D));
    std::cin >> N >> M >> K;
    for (int i = 0; i < N; i++)
    {
        std::cin >> blocked[i];
    }
    std::cin >> Q;
    while (Q--)
    {
        int x, y;
        std::cin >> x >> y;
        std::cout << ANS[solve(--x, --y)] << std::endl;
    }
    return 0;
}
