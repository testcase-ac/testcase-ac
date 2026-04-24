#include<iostream>
#include<map>
#include<cmath>
using namespace std;

struct Vector2
{
	int x;
	int y;
};

int N = 0, M = 0, B = 0;
int height[500][500] = {};


int Can(int iHeight)
{
	// 평균보다 높은/낮은 높이 합 구하기
	int overSum = 0;
	int underSum = 0;
	int time = 0;
	for (int n = 0; n < N; ++n)
	{
		for (int m = 0; m < M; ++m)
		{
			// 기준 높이보다 크면 큰 값만 더해줌
			if (height[n][m] > iHeight)
			{
				overSum += height[n][m] - iHeight;
			}

			// 기준 높이보다 작으면
			else if (height[n][m] < iHeight)
			{
				underSum += iHeight - height[n][m];
			}
		}
	}

	time = overSum * 2 + underSum;

	if (underSum <= B + overSum)
		return time;
	else
		return -1;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);



	int time = 0;
	int minHeight = 256;
	cin >> N >> M >> B;

	for (int n = 0; n < N; ++n)
	{
		for (int m = 0; m < M; ++m)
		{
			cin >> height[n][m];

			// 최소 높이를 구한다
			if (minHeight > height[n][m])
				minHeight = height[n][m];
		}
	}



	while (true)
	{
		// 최소 높이부터 한 층 씩 올리면서 가능한 최대 높이를 구함
		
		// 채워야 할 블럭 수보다 인벤토리가 더 많으면 진행
		if (Can(minHeight) > 0)
		{
			// 같은 시간이거나 더 작은 시간이면 높이 높이기
			int prevTime = 0, curTime = 0;
			prevTime = Can(minHeight);

			while (true)
			{
				curTime = Can(minHeight + 1);

				// 불가능한 경우 종료
				if (curTime == -1)
				{
					break;
				}

				// 높이 높였을 경우 시간이 줄어들거나 같으면 높이 높이기
				else if (curTime <= prevTime)
				{
					minHeight++;
				}

				// time이 더 증가할 경우 종료
				else
				{
					break;
				}

				prevTime = curTime;
			}
			break;
		}

		
		// 적으면 높이를 낮춤
		minHeight--;
	}


	for (int n = 0; n < N; ++n)
	{
		for (int m = 0; m < M; ++m)
		{
			if (height[n][m] > minHeight)
			{
				time += (height[n][m] - minHeight) * 2;
				B++;
			}
			else if (height[n][m] < minHeight)
			{
				time += (minHeight - height[n][m]);
			}
		}
	}

	cout << time << " " << minHeight;


	return 0;
}