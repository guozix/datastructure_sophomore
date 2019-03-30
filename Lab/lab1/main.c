#include <stdio.h>
#include <stdlib.h>

typedef struct num
{
    int a;
    struct num *next;
}num;

struct num* findnum(num* head,int num_tofind);
struct num* insertnum(struct num* head,int num_toadd);
struct num* deletenum(num* head,int num_todelete);
int list_length(num* head);
void print_list(num* head);
struct num* reverse(num* head);

int main()
{
    num* head = NULL;
    int fnum,nums[20]={0},i=0,temp,list_lenth;
    FILE *fp;
    if((fp = fopen("input.txt","a+"))==NULL)
    {
        printf("fail to open the file");
        exit(0);
    }
    while(fscanf(fp," %d",&fnum)>0)
    {
        nums[i]=fnum;
        i++;
    }
    fclose(fp);//���ļ���������������nums
    list_lenth=i;

    for(i=0;i<list_lenth;i++)
    {
        //printf("%d ",nums[i]);
        head=insertnum(head,nums[i]);
    }

    print_list(head);
    printf("length of the linked list:%d\n",list_length(head));
    int find_num;
    printf("find number:");
    scanf(" %d",&find_num);
    findnum(head,find_num);
    deletenum(head,find_num);
    print_list(head);
    head=reverse(head);
    print_list(head);

    return 0;
}
//����һ�������ڵ�Ԫ��λ��
struct num* findnum(num* head,int num_tofind) ///
{
    num *p=head, *pos=NULL;
    int posnum=0;
    if(p==NULL)
    {
        printf("empty list nothing to be found.");
    }
    else
    {
        //p=p->next;
        do
        {
            posnum++;
            if(p->a == num_tofind)
            {
                pos=p;
                printf("the number is at No.%d position\n",posnum);
            }
            p=p->next;
        }while(p != NULL);
    }
    if (pos == NULL)
    {
        printf("can not find %d\n",num_tofind);
    }
    return pos;
}

//insert
struct num* insertnum(num* head, int num_toadd) ///
{
    num *p=NULL, *pr=head,*pre=head;//�����롢�ƶ��Ƚ�ָ�롢pr֮ǰ�Ľڵ��ָ��

    p=(struct num*)malloc(sizeof(struct num));
    if (p==NULL)
    {
        printf("No enough memory to allocate!");
        exit(0);
    }

    p->a=num_toadd;
    p->next=NULL;

    if (head==NULL)  //if empty
    {
        head=p;
        //p->next=NULL;
    }
    else if (p->a <= head->a)//����ȵ�һ������С
    {
        p->next=head;
        head=p;
    }
    else//�嵽��С���ʵ�λ��
    {
        while(((p->a) > (pr->a))&&(pr->next != NULL))
        {
            pre=pr;
            pr=pr->next;
        }
        if ((p->a) <= (pr->a))
        {
            pre->next=p;
            p->next=pr;
        }
        else
        {
            pr->next=p;
        }
    }
    /*else//�嵽��С���ʵ�λ��
    {
        while(p->a > pr->a)
        {
            if(pr->next == NULL)
            {
                pre=pr;
                pr=NULL;
                break;
            }
            pre=pr;
            pr=pr->next;
        }
        pre->next=p;
        p->next=pr;
    }*/
    return head;
}

struct num* deletenum(num* head,int num_todelete)
{
    num *p=head, *pos=NULL, *pr=NULL;
    if(p == NULL)//��������
    {
        printf("empty list can not delete anything.\n");
    }
    else
    {
        if(head->a == num_todelete)//����Ҫɾ���Ľڵ�
        {
            head=head->next;
            free(p);
        }
        else
        {
            while(1)
            {
                pr=p;
                p=p->next;
                if(p == NULL)
                {
                    break;
                }
                if(p->a == num_todelete)
                {
                    pos=p;
                    pr->next=p->next;
                    free(p);
                    p=pr;
                }
            }
        }
    }
    if (pos == NULL)
    {
        printf("no such thing to delete.\n");
    }
    return head;
}

int list_length(num* head) ///
{
    num *p=head;
    int length=0;
    if (head == NULL)
        length=0;
    else
    {
        do
        {
            length++;
            p=p->next;
        }while(p != NULL);
    }
    return length;
}

void print_list(num *head) ///
{
    num *p=head;
    if (head == NULL)
    {
        printf("empty\n");
    }
    else
    {
        do
        {
            printf("%d ",p->a);
            p=p->next;
        }while(p != NULL);
        printf("\n");
    }
}

struct num *reverse(num *head) ///
{
    num *head2=NULL,*p=head,*endp=NULL;
    int length=list_length(head),nums[length];

    for (int i=0;i<length;i++)//��������ȡ������
    {
        nums[i]=p->a;
        p=p->next;
    }
    for (int i=length-1;i>=0;i--)//�����µ�
    {
        p=(struct num*)malloc(sizeof(struct num));
        if (head2 == NULL)
        {
            head2=p;
            p->a=nums[i];
            p->next=NULL;
            endp=p;
        }
        else
        {
            endp->next=p;
            endp=p;
            p->a=nums[i];
            p->next=NULL;
        }
    }
    while(1)//free������
    {
        if(head==NULL)
            break;
        p=head;
        head=head->next;
        free(p);
    }
    return head2;
}


