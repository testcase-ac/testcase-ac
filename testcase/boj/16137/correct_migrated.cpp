#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <array>

using Row = std::vector<uint32_t>;
using Grid = std::vector<Row>;

struct Point
{
    size_t y;
    size_t x;
};

struct Entry
{
    Point p;
    size_t t;
    
    bool operator>(const Entry& _e) const { return t > _e.t; }
};

int main()
{
    constexpr uint32_t kWall = 0x0100;
    size_t N, M;
    
    std::cin >> N >> M;
    
    Grid raw_grid(N, Row(N));
    std::vector<std::vector<bool>> used_grid(N, std::vector<bool>(N, false)), non_used_grid(N, std::vector<bool>(N, false));
    
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            std::cin >> raw_grid[i][j];
        }
    }
    
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (raw_grid[i][j] == 0)
            {
                bool is_ver = (i + 1 < N && raw_grid[i + 1][j] == 0) || (i - 1 < N && raw_grid[i - 1][j] == 0);
                bool is_hor = (j + 1 < N && raw_grid[i][j + 1] == 0) || (j - 1 < N && raw_grid[i][j - 1] == 0);
                
                used_grid[i][j] = non_used_grid[i][j] = is_ver && is_hor;
            }
        }
    }
    
    size_t total_t = 0;
    bool find = false;
    std::queue<Point> non_used_que, used_que;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> non_used_nque, used_nque;
    non_used_grid[0][0] = true;
    non_used_que.push(Point{0, 0});
    
    while (!find && (!non_used_que.empty() || !non_used_nque.empty() || !used_que.empty() || !used_nque.empty()))
    {
        while (!non_used_nque.empty() && non_used_nque.top().t == total_t)
        {
            non_used_que.push(non_used_nque.top().p);
            non_used_nque.pop();
        }
        
        while (!used_nque.empty() && used_nque.top().t == total_t)
        {
            used_que.push(used_nque.top().p);
            used_nque.pop();
        }
        
        const size_t non_used_que_size = non_used_que.size();
        const size_t used_que_size = used_que.size();
        
        for (size_t i = 0; i < non_used_que_size; i++)
        {
            Point p = non_used_que.front();
            non_used_que.pop();
            
            std::array<Point, 4> nps =
            {
                Point{p.y - 1, p.x}, 
                Point{p.y, p.x - 1}, 
                Point{p.y + 1, p.x}, 
                Point{p.y, p.x + 1}
            };
            
            for (Point np : nps)
            {
                if (np.y >= N || np.x >= N || non_used_grid[np.y][np.x]) continue;
                
                if (np.y == N - 1 && np.x == N - 1)
                {
                    find = true;
                    break;
                }
                
                if (raw_grid[np.y][np.x] == 1)
                {
                    non_used_grid[np.y][np.x] = true;
                    non_used_que.push(np);
                }
                else if (raw_grid[p.y][p.x] == 1 && raw_grid[np.y][np.x] == 0)
                {
                    size_t nt = total_t + 1 + (M - (total_t + 1) % M) % M;
                    non_used_grid[np.y][np.x] = true, used_grid[np.y][np.x] = true;
                    used_nque.push(Entry{np, nt});
                }
                else if (raw_grid[p.y][p.x] == 1)
                {
                    size_t mod_m = raw_grid[np.y][np.x];
                    size_t nt = total_t + 1 + (mod_m - (total_t + 1) % mod_m) % mod_m;
                    
                    non_used_grid[np.y][np.x] = true;
                    non_used_nque.push(Entry{np, nt});
                }
            }
        }
        
        for (size_t i = 0; i < used_que_size; i++)
        {
            Point p = used_que.front();
            used_que.pop();
            
            std::array<Point, 4> nps =
            {
                Point{p.y - 1, p.x}, 
                Point{p.y, p.x - 1}, 
                Point{p.y + 1, p.x}, 
                Point{p.y, p.x + 1}
            };
            
            for (Point np : nps)
            {
                if (np.y >= N || np.x >= N || non_used_grid[np.y][np.x] || used_grid[np.y][np.x]) continue;
                
                if (np.y == N - 1 && np.x == N - 1)
                {
                    find = true;
                    break;
                }
                
                if (raw_grid[np.y][np.x] == 1)
                {
                    used_grid[np.y][np.x] = true;
                    used_que.push(np);
                }
                else if (raw_grid[p.y][p.x] == 1 && raw_grid[np.y][np.x] != 0)
                {
                    size_t mod_m = raw_grid[np.y][np.x];
                    size_t nt = total_t + 1 + (mod_m - (total_t + 1) % mod_m) % mod_m;
                    
                    used_grid[np.y][np.x] = true;
                    used_nque.push(Entry{np, nt});
                }
            }
        }
        
        total_t++;
    }
    
    std::cout << total_t << std::endl;
}
