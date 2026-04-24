#include <stdio.h>
#include <stdlib.h>
struct STACK
{
	int stack[100005];
	int index;
	int top;
	int cur;
	int bottom;

	int bool_false;
	char str[2000100];
	int str_index;
}node = { {0,} , -1 , 1, 0, 0 , 0 , {0,} , 0};

int first = 0;

void push(int cur)
{
	node.stack[++node.index] = cur;
	node.top++;
	node.cur = node.stack[node.index];


	node.str[node.str_index++] =  '+';
	node.str[node.str_index++] =  '\n';
}


bool empty()
{
	
	return node.index == -1;
}

void pop(int cur)
{
	if (node.index <= 0)
	{
		node.cur = 0;
	}
	else
	{
		node.index--;
		node.cur = node.stack[node.index];
	}

	node.str[node.str_index++] =  '-';
	node.str[node.str_index++] =  '\n';
}


void cal(int num)
{

	int count = 1;
	if (first == 0) // 처음 함수가 실행되면 무조건 push를 함으로 first 사용 
	{
		while (count <= num)
		{
			push(count);
			count++;
		}
		if (node.index != 0) 
		{
			node.bottom = node.stack[node.index - 1];
		}
		else // 0일 경우에는 index가 -1이 돼서 범위를 벗어남으로 if-else사용
		{
			node.bottom = node.stack[0];
		}
		
		first++; // ++을 통해 처음 1번만 되도록 함
	}
	else // 두번 째 입력부터 cur값을 통해 push할지 pop할지 결정
	{
		if (node.cur < num) 
		{
			while (node.top < num || node.top == num)
			{
				push(node.top);//top변수를 통해 숫자 건너뛰기 ex) 5->4->6 이경우 push를 한번만해서 바로 6으로 이동
			}

			if (empty()) // index가 -1인 경우 
			{
				node.bottom = node.stack[0]; //예외처리를 위한 bottom변수 사용
			}
			else
			{
				node.bottom = node.stack[node.index - 1];
				
			}
		}
	}

	if (node.bottom > num) // 예제처럼 5->3으로 4를 거치지 않고 바로 가는 경우 예외처리 후 종료
	{
		node.bool_false++;
		return;
	}


	if (node.cur > num || node.cur == num)
	{
		if (node.cur == num) // ex) 4->3 처럼 바로 아래에 있는 수로 갈 경우 1번만 pop
		{

			pop(node.cur);
			if (node.index != -1)
			{
				node.bottom = node.stack[node.index]; //pop 했으니까 bottom값 교체
			}
			
		
			return;
		}
		while (node.cur != num)
		{

			pop(node.cur);
			if (node.index != -1)
			{
				node.bottom = node.stack[node.index];
			}
		
		}

	}

}


int main(void)
{
	int size = 0, num = 0;
	scanf("%d", &size);
	for (int i = 0; i < size;i++)
	{
		scanf("%d", &num);
		if (size < num)
		{
			printf("NO\n");
			return 0;
		}

		cal(num);
		if (node.bool_false != 0)
		{
			printf("NO\n");
			return 0;
		}
	}
	node.str[node.str_index] = '\0';
	printf("%s", node.str);
}