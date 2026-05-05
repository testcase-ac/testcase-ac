#include <stdio.h>
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
int main()
{
	for(int t=1;;t++)
	{
		char line[2004];
		int c=0, i, r=0;
		scanf("%s", line);
		if(line[0]=='-') break;
		for(i=0;line[i];i++)
		{
			if(line[i]=='{') c++;
			else { c--; if(c<0) c+=2, r++; }
		}
		printf("%d. %d\n", t, r+c/2);
	}
}
