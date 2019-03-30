#include <bits/stdc++.h>

using namespace std;

int main()
{//得到next数组

    char* s="abababca";
    int next[8]={0};
    int i=1,j=0;

    while (i<8)
    {

        if (s[i] == s[j])
        {
            j++;
            next[i]=j;
            i++;
        }
        else if (j==0)
        {
            next[i]=0;
            i++;
        }
        else
        {
            while ((s[i] != s[j])&&(j!=0))
            {
                j=next[j-1];
            }
        }
    }

    for (i=0;i<8;i++)
    {
        printf("%d ",next[i]);
    }
    return 0;
}
