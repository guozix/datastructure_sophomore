#include <bits/stdc++.h>

using namespace std;

/*typedef struct node
{
    int num;
    int toone;
    int key;
}node;*/

int main()
{
    int nodenum=0;
    char st[30];
    int i=0,j=0,temp;

    FILE *fp=NULL;
    if((fp = fopen("ex3_Graph1.txt","a+"))==NULL)
    {
        printf("fail to open the file");
        exit(0);
    }
    fgets(st,30,fp);
    nodenum=st[8]-48;
    //printf("%d\n",nodenum);
    int edgew[nodenum][nodenum];
    fgets(st,30,fp);
    fgets(st,30,fp);
    for(i=0;i<nodenum;i++)
    {
        for(j=0;j<nodenum;j++)
        {
            if(j==0)
            {
                fgets(st,2,fp);
                fgets(st,3,fp);
            }
            else
                fgets(st,2,fp);
            fscanf(fp," %d",&temp);
            if (temp == -1)
                temp=1000000;
            edgew[i][j]=temp;
        }
    }
    fclose(fp);

    int dist[5];
    int tag[5]={1,0,0,0,0};
    int shortest_node;//本次最短节点
    int shortest_dist;
    int ahead[5]={0};//记录每个节点到S0最短路的前一个节点索引
    int trace[5];//记录每个节点最短路径
    int k=0;
    for(i=0;i<5;i++)
    {
        dist[i]=1000000;
        if (edgew[0][i] != 1000000)
            dist[i]=edgew[0][i];
    }
    int sum=accumulate(tag,tag+nodenum,0);
    while(sum<5)
    {
        shortest_dist=1000000;
        for (i=0;i<5;i++)//找到最小距离和对应的节点
        {
            if(tag[i]==1)   continue;
            if(shortest_dist>dist[i])
            {
                shortest_dist=dist[i];
                shortest_node=i;
            }
        }
        tag[shortest_node]=1;
        for(i=1;i<5;i++)
        {
            if(tag[i] == 0)
            {
                if(dist[i]>(dist[shortest_node]+edgew[shortest_node][i]))
                {
                    dist[i]=dist[shortest_node]+edgew[shortest_node][i];
                    ahead[i]=shortest_node;
                }
            }
        }
        sum=accumulate(tag,tag+nodenum,0);
    }
    /*for (i=0;i<5;i++)//找到了最短路权重
    {
        printf("%d\n",dist[i]);
    }*/
    printf("graph1:\n");
    for (i=1;i<5;i++)
    {//print trace
        j=i;
        k=0;
        while(j != 0)
        {
            trace[k++]=j;
            j=ahead[j];
        }
        trace[k]=0;
        printf("s0->s%d path: ",i);
        while (k>0)
        {
            printf("s%d,",trace[k]);
            k--;
        }
        printf("s%d\tvalue=%d\n",i,dist[i]);
    }

    //printf("**********************************************\n");
/********************************************************************/
    //graph2
    fp=NULL;
    if((fp = fopen("ex3_Graph2.txt","a+"))==NULL)
    {
        printf("fail to open the file");
        exit(0);
    }
    fgets(st,30,fp);
    nodenum=st[8]-48;
    //printf("%d\n",nodenum);///
    int edgew2[nodenum][nodenum];
    char allnodes[8];
    fgets(st,30,fp);
    fgets(st,30,fp);
    for(i=0;i<nodenum;i++)
    {
        allnodes[i]=st[i+i+1];
        //printf("%c ",allnodes[i]);
    }
    //printf("\n");
    for(i=0;i<nodenum;i++)
    {
        for(j=0;j<nodenum;j++)
        {
            if(j==0)
            {
                fgets(st,2,fp);
                fgets(st,2,fp);
            }
            else
                fgets(st,2,fp);
            fscanf(fp," %d",&temp);
            if (temp == -1)
                temp=1000000;
            edgew2[i][j]=temp;
            //printf("%d ",edgew2[i][j]);
        }
        //printf("\n");
    }
    fclose(fp);

    int dist2[8];
    int tag2[8]={1,0,0,0,0,0,0,0};
    //int shortest_node;
    //int shortest_dist;
    int ahead2[8]={0};//记录每个节点到S0最短路的前一个节点
    char trace2[8];//记录节点最短路径

    for(i=0;i<8;i++)
    {
        dist2[i]=1000000;
        if (edgew2[0][i] != 1000000)
            dist2[i]=edgew2[0][i];
    }
    sum=accumulate(tag2,tag2+nodenum,0);
    while(sum<8)
    {
        shortest_dist=1000000;
        for (i=0;i<8;i++)//找到最小距离和对应的节点
        {
            if(tag2[i]==1)   continue;
            if(shortest_dist>dist2[i])
            {
                shortest_dist=dist2[i];
                shortest_node=i;
            }
        }
        tag2[shortest_node]=1;
        for(i=1;i<8;i++)
        {
            if(tag2[i] == 0)
            {
                if(dist2[i]>(dist2[shortest_node]+edgew2[shortest_node][i]))
                {
                    dist2[i]=dist2[shortest_node]+edgew2[shortest_node][i];
                    ahead2[i]=shortest_node;
                }
            }
        }
        sum=accumulate(tag2,tag2+nodenum,0);
    }
    /*for (i=0;i<7;i++)//找到了最短路权重
    {
        printf("%d\n",dist2[i]);
    }*/


    printf("graph2:\n");

    //print trace2
    j=7;
    k=0;
    while(j != 0)
    {
        trace2[k++]=allnodes[j];
        j=ahead2[j];
    }
    trace2[k]='a';
    printf("a->h path: ");
    while (k>0)
    {
        printf("%c,",trace2[k]);
        k--;
    }
    printf("h\tvalue=%d\n",dist2[7]);

    return 0;
}




