#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <array>
#include <bitset>

struct Point
{
    size_t y;
    size_t x;
    
    bool operator==(const Point& p) const { return y == p.y && x == p.x; }
};

struct Entry
{
    Point p1, p2;
};

using Grid = std::vector<std::vector<char>>;

int main()
{
    size_t N, M, K;
    Point school, house;
    
    std::cin >> N >> M >> K;
    
    Grid grid(N + 2, std::vector<char>(M + 2));
    std::vector<std::vector<std::array<size_t, 4>>> memo(N + 2, std::vector<std::array<size_t, 4>>(M + 2, std::array<size_t, 4>{0xFF, 0xFF, 0xFF, 0xFF}));
    
    grid[0].assign(M + 2, 'X'), grid[N + 1].assign(M + 2, 'X');
    grid[0][0] = '0';
    
    for (size_t i = 1; i <= N; i++)
    {
        std::string str;
        
        std::cin >> str;
        
        grid[i][0] = 'X';
        std::copy(str.begin(), str.end(), grid[i].begin() + 1);
        grid[i][M + 1] = 'X';
        
        for (size_t j = 1; j <= M; j++)
        {
            if (grid[i][j] == 'S')
            {
                school = Point{i, j};
            }
            else if (grid[i][j] == 'H')
            {
                house = Point{i, j};
            }
        }
    }
    
    std::queue<Entry> que;
    memo[school.y][school.x] = {0, 0, 0, 0};
    grid[school.y][school.x] = '0';
    que.push(Entry{school, school});
    size_t dist = 0;
    bool find = false;
    
    while (!que.empty())
    {
        const size_t que_size = que.size();
        
        for (size_t i = 0; i < que_size; i++)
        {
            Entry e = que.front();
            que.pop();
            
            Point p = e.p1;
            
            std::array<Point, 4> nps = 
                {Point{p.y - 1, p.x}, Point{p.y + 1, p.x}, 
                 Point{p.y, p.x - 1}, Point{p.y, p.x + 1}};
            
            for (size_t j = 0; j < 4; j++)
            {
                const Point np = nps[j];
                
                if (np == e.p2 || grid[np.y][np.x] == 'X') continue;
                if (np == house) { find = true; break; }
                
                size_t v1 = grid[e.p1.y][e.p1.x] - '0';
                size_t v2 = grid[e.p2.y][e.p2.x] - '0';
                size_t vn = grid[np.y][np.x] - '0';
                
                if (vn + v1 + v2 <= K && vn + v1 < memo[np.y][np.x][j])
                {
                    memo[np.y][np.x][j] = vn + v1;
                    que.push(Entry{np, p});
                }
            }
        }
        
        dist++;
        
        if (find)
        {
            break;
        }
    }
    
    if (!find)
    {
        std::cout << -1 << std::endl;
    }
    else
    {
        std::cout << dist << std::endl;
    }
}
