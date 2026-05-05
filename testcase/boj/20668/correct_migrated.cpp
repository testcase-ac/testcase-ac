#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <limits>
#include <algorithm>

struct Edge
{
    uint16_t v;
    uint32_t length;
    uint16_t limit;
};

struct Entry
{
    uint16_t v;
    uint16_t speed;
    uint64_t time;
    
    bool operator>(const Entry& _e) const { return time > _e.time; }
};

template <typename T>
constexpr T Gcd(T _a, T _b)
{
    while (_b != 0)
    {
        T r = _a % _b;
        _a = _b, _b = r;
    }
    
    return _a;
}

template <typename T>
constexpr T Lcm(T _a, T _b)
{
    return _a * _b / Gcd(_a, _b);
}

template <typename T>
constexpr T Lcm(const std::initializer_list<T>& _list)
{
    T lcm = 1;
    
    for (T element : _list)
    {
        lcm = Lcm(lcm, element);
    }
    
    return lcm;
}

using Graph = std::vector<std::vector<Edge>>;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    size_t N, M;
    constexpr uint64_t kDev = Lcm({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    constexpr uint64_t kMaxT = std::numeric_limits<uint64_t>::max() / 2;
    Graph graph;
    
    std::cin >> N >> M;
    
    graph.resize(N + 1);
    
    for (size_t i = 0; i < M; i++)
    {
        size_t A, B, L, K;
        
        std::cin >> A >> B >> L >> K;
        
        graph[A].push_back(Edge{B, L, K});
        graph[B].push_back(Edge{A, L, K});
    }
    
    std::vector<std::array<uint64_t, 11>> dists(N + 1, std::array<uint64_t, 11>{ kMaxT, kMaxT, kMaxT, kMaxT, kMaxT, kMaxT, kMaxT, kMaxT, kMaxT, kMaxT, kMaxT });
    std::vector<std::array<bool, 11>> visit(N + 1, std::array<bool, 11>{ false });
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> que;
    
    dists[1][1] = 0;
    que.push(Entry{1, 1, 0});
    
    while (!que.empty())
    {
        auto [v, s, t] = que.top();
        que.pop();
        
        if (visit[v][s] == true) continue;
        visit[v][s] = true;
        
        std::array<uint16_t, 3> nss = { s - 1, s, s + 1};
        
        for (auto [nv, nl, nlimit] : graph[v])
        {
            for (uint16_t ns : nss)
            {
                if (ns == 0 || ns > nlimit) continue;
                
                uint64_t nt = t + nl * kDev / ns;
                
                if (nt < dists[nv][ns])
                {
                    dists[nv][ns] = nt;
                    que.push(Entry{nv, ns, nt});
                }
            }
        }
    }
    
    std::cout.precision(9);
	std::cout << std::fixed;
    
    std::cout << static_cast<long double>(*std::min_element(dists[N].begin(), dists[N].end())) / static_cast<long double>(kDev) << std::endl;
}
