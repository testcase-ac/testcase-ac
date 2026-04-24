#include <stdio.h>
#include <iostream>
#include <stack>
#include <string>
#define LIM 100
using namespace std;
stack <char> st;
stack <char> st2;
stack <char> st3;
int main()
{
    int t;
    scanf("%d",&t);
    for(int j=1;j<=t;j++)
    {
        string s;
        cin >> s;
        for(int i=0;i<s.size();i++)
        {
            if (s[i]=='-')
            {
                if (!st.empty())
                {
                    st.pop();
                }
            }
            else if (s[i]=='<')
            {
                if (!st.empty())
                {
                    st2.push(st.top());
                    st.pop();
                }
            }
            else if (s[i]=='>')
            {
                if (!st2.empty())
                {
                    st.push(st2.top());
                    st2.pop();
                }
            }
            else
            {
                st.push(s[i]);
            }
        }
        if (!st2.empty())
        {
            while(!st2.empty())
            {
                st.push(st2.top());
                st2.pop();
            }
        }
        while(!st.empty())
        {
            st3.push(st.top());
            st.pop();
        }
        while(!st3.empty())
        {
            printf("%c",st3.top());
            st3.pop();
        }
      printf("\n");
    }
    return 0;
}