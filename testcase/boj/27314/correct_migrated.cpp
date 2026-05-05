#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstdint>
#include <algorithm>
#include <limits>
#include <array>
#include <cstring>

using Grid = std::vector<std::vector<char>>;

struct Point
{
    uint32_t y;
    uint32_t x;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    size_t N, M;
    
    std::cin >> N >> M;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    char (*grid)[M + 2] = static_cast<char (*)[M + 2]>(operator new(sizeof(char) * (N + 2) * (M + 2)));
    std::vector<Point> exits;
    std::fill(grid[0], grid[0] + M + 2, 'X');
    std::fill(grid[N + 1], grid[N + 1] + M + 2, 'X');
    
    for (size_t i = 1; i <= N; i++)
    {
        grid[i][0] = 'X';
        std::cin.getline(&grid[i][1], M + 1);
        grid[i][M + 1] = 'X';
        
        for (size_t j = 1; j <= M; j++)
        {
            if (grid[i][j] == '#') exits.push_back(Point{i, j});
        }
    }
    
    char (*origin_grid)[M + 2] = static_cast<char (*)[M + 2]>(operator new(sizeof(char) * (N + 2) * (M + 2)));
    memcpy(origin_grid, grid, sizeof(char) * (N + 2) * (M + 2));
    
    std::queue<Point> que;
    size_t max_count = 0;
    
    for (Point exit : exits)
    {
        std::queue<Point> que;
        grid[exit.y][exit.x] = 'X';
        que.push(exit);
        bool find = false;
        size_t count = 0;
        
        while (!que.empty() && !find)
        {
            size_t que_size = que.size();
            
            for (size_t i = 0; i < que_size; i++)
            {
                Point p = que.front();
                que.pop();
                
                constexpr std::array<int32_t, 4> dy = { -1, 1, 0, 0 };
                constexpr std::array<int32_t, 4> dx = { 0, 0, -1, 1 };
                
                for (size_t j = 0; j < 4; j++)
                {
                    uint32_t ny = p.y + dy[j], nx = p.x + dx[j];
                    
                    if (grid[ny][nx] == 'X') continue;
                    
                    if (grid[ny][nx] == 'H') find = true;
                    else if (grid[ny][nx] == 'P') count++;
                    
                    que.push(Point{ny, nx});
                    grid[ny][nx] = 'X';
                }
            }
        }
        
        if (find)
        {
            max_count = std::max(max_count, count);
        }
        
        memcpy(grid, origin_grid, sizeof(char) * (N + 2) * (M + 2));
    }
    
    operator delete(origin_grid);
    operator delete(grid);
    
    std::cout << max_count << std::endl;
}
