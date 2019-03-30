#include <bits/stdc++.h>
#include <time.h>

using namespace std;

void insert_sort(int* nums,int length);
void shell_sort(int nums[],int length);

int main()
{
    int length=2000;
    printf("输入数据量：");
    scanf("%d",&length);
    int nums[length];



    for (int i=0;i<length;i++)
    {
        nums[i]=i;
    }

    //reverse(nums,nums+length);
    /*for(int i=0;i<5;i++)
    {
        printf("%d",nums[i]);
    }
    printf("\n");*/

    random_shuffle(nums,nums+length);

    /*for(int i=0;i<length;i++)
    {
        printf("%d ",nums[i]);
    }
    printf("\n");*/

    insert_sort(nums,length);

    random_shuffle(nums,nums+length);

    shell_sort(nums,length);

    /*for(int i=0;i<length;i++)
    {
        printf("%d ",nums[i]);
    }
    printf("\n");*/

    return 0;
}

void insert_sort(int nums[],int length)
{
    long start,finish;
	double total_time;

    int temp;
    int i,j;
    //printf("%d\n",length);
    start=clock();
    for (i=1;i<length;i++)
    {
        temp=nums[i];
        j=i-1;
        while ((j>=0)&&(temp<nums[j]))
        {
            nums[j+1]=nums[j];
            j--;
        }
        nums[j+1]=temp;
    }
    finish=clock();
    total_time=(double)(finish-start)/CLOCKS_PER_SEC;
    printf("\n排序耗时：%.3f\n",total_time);
}

void shell_sort(int nums[],int length)
{
    long start,finish;
	double total_time;

    int i,j=0,jmp_len;
    for (i=1;(pow(2,i)-1)<length;i++)
    {
        ;
    }
    i--;
    jmp_len=i;
    int jmps[jmp_len];
    for (;i>0;i--)
    {
        jmps[j]=(int)pow(2,i)-1;
        j++;
    }
    printf("shell增量序列：");
    for (i=0;i<j;i++)
    {
        printf("%d ",jmps[i]);
    }

    int h,temp;
    start=clock();
    for (i=0;i<jmp_len;i++)
    {//循环每一趟shell排序
        for (j=0;j<jmps[i];j++)
        {//循环简单插入排序每个分组
            for (int k=j+jmps[i];k<length;k+=jmps[i])
            {
                temp=nums[k];
                h=k-jmps[i];
                while ((h>=j)&&(temp<nums[h]))
                {
                    nums[h+jmps[i]]=nums[h];
                    h-=jmps[i];
                }
                nums[h+jmps[i]]=temp;
            }
        }
    }
    finish=clock();
    total_time=(double)(finish-start)/CLOCKS_PER_SEC;
    printf("\n排序耗时：%.3f\n",total_time);
}




