#include <iostream>
#include <vector>
#include <algorithm>
typedef std::vector<int > vi;
typedef std::vector<vi> vvi;
//재귀, DP 하향식
int FillDP(const int now, const int prev, const vvi& edges, const vi& cost, vi& DP, vvi& childrenbox)
{
	if (DP[now] != 0)				   	  //한 번 계산한 것이라면 그대로 반환
		return DP[now];
	DP[now] = cost[now];
	for (auto& a : edges[now])			  //거리 1인 자녀들(더할 수 없음)
	{
		if (a != prev)
		{
			for (auto& b : edges[a])            //거리 2 ,Max(b, b의 자녀(c)들의 합)을 DP[now]에 더해주기
			{
				if (b != now)
				{
					int tmp3 = 0;
					vi vtemp;    //거리 3이 답일 경우 now의 자녀로 편입시킬 임시 벡터(b의 거리1인 자녀들)
					for (auto& c : edges[b])    //거리 3 (2와 비교)
					{
						if (c != a)
						{
							vtemp.push_back(c);  
							tmp3 += FillDP(c, b, edges, cost, DP, childrenbox);  //(거리3) b의 자녀들인 DP[c]합치기
						}
					}
					int tmp2 = FillDP(b, a, edges, cost, DP, childrenbox); //DP[b]구해오기
					if (tmp2 > tmp3)
					{
						childrenbox[now].push_back(b);      //b 편입
						DP[now] += tmp2;
					}
					else
					{
						childrenbox[now].insert(childrenbox[now].end(), vtemp.begin(), vtemp.end()); // b의 자녀들 편입
						DP[now] += tmp3;
					}
				}
			}
		}
	}
	return DP[now];
}
void Tracing(int now, const vvi& childrenbox, vi& ansbox)
{
	for (auto& c : childrenbox[now])
	{
		ansbox.push_back(c);
		Tracing(c, childrenbox, ansbox);     //자녀들 그대로 따라가서 ansbox에 추가, 재귀
	}
}
int main()
{
	std::ios::sync_with_stdio(false); std::cin.tie(NULL); std::cout.tie(NULL);
	int N;
	std::cin >> N;
	vi cost(N + 2);
	for (int i = 1;i <= N;i++)
		std::cin >> cost[i];
	vvi edges(N + 2);
	for (int i = 1;i < N;i++)
	{
		int a, b;
		std::cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	edges[0].push_back(1);          //1번으로 이어지는 가상의 0번 정점 추가
	edges[N + 1].push_back(0);      //0번으로 이어지는 가상의 N + 1번 정점 추가, N+1 -> 0 -> 1 -> edges[1]...
	vi DP(N + 2);
	vvi childrenbox(N + 2);
	int ans1 = FillDP(N + 1, -1, edges, cost, DP, childrenbox);  // DP채우기(N + 1 시작)
	int ans0 = FillDP(0, -1, edges, cost, DP, childrenbox);      // DP채우기(0 시작)
	int start = 0;
	vi ansbox;
	ansbox.reserve(N);
	if (ans1 > ans0)                 //0과 N+1중 어디서 시작한 것이 답인지 체크
	{
		start = N + 1;
		ans0 = ans1;
	}
	std::cout << ans0 << "\n";
	Tracing(start, childrenbox, ansbox);         //정답인 독립집합 ansbox에 채워넣기
	std::sort(ansbox.begin(), ansbox.end());
	for (auto& a : ansbox)
		std::cout << a << " ";

}
