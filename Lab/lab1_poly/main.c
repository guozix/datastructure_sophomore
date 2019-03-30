#include <stdio.h>
#include <stdlib.h>

typedef struct num
{
    int a;
    int b;  //b*x^a
    struct num *next;
}num;

struct num* findnum(num* head,int num_tofind);
struct num* insertnum(struct num* head,int num_toadd);
struct num* deletenum(num* head,int num_todelete);
int list_length(num* head);
void print_list(num* head);
struct num* reverse(num* head);
struct num* insertpoly(num* head, int* poly_toadd);
void print_poly(num *head);



int main()
{
    num* p=NULL,*head=NULL;
    int fnum,nums[20][2]={0},n_cal=0,i=0,temp;
    /*for (int j=0;j<4;j++)
    {
        head[j]=NULL;
    }*/
    FILE *fp;
    if((fp = fopen("poly.txt","a+"))==NULL)
    {
        printf("fail to open the file");
        exit(0);
    }
    fscanf(fp," %d",&n_cal);//多少个相加操作

    while(n_cal)
    {
        for (i=0;i<20;i++)//归零
        {
            for (int j=0;j<2;j++)
            {
                nums[i][j]=0;
            }
        }

        i=0;
        while(fscanf(fp," %d ",&fnum)>0)
        {
            nums[i][0]=fnum;
            fscanf(fp," %d ",&nums[i][1]);
            if(nums[i][1]<0)
                break;
            i++;
        }

        //建立多项式链表
        for(i=0;nums[i][1]>=0;i++)
        {
            head=insertpoly(head, nums[i]);
        }

        i=0;
        while(fscanf(fp," %d ",&fnum)>0)
        {
            nums[i][0]=fnum;
            fscanf(fp," %d ",&nums[i][1]);
            if(nums[i][1]<0)
                break;
            i++;
        }
        for(i=0;nums[i][1]>=0;i++)
        {
            head=insertpoly(head, nums[i]);
        }


        print_poly(head);
        //printf("------------\n");

        n_cal--;//计算次数减一

        while(1)  //释放上一组head，准备下一组
        {
            if(head==NULL)
                break;
            p=head;
            head=head->next;
            free(p);
        }
    }

    fclose(fp);
    /*printf("%d\n",list_length(head));
    findnum(head,5);
    deletenum(head,5);
    print_list(head);
    head=reverse(head);
    print_list(head);*/

    return 0;
}
//返回一个数所在单元的的地址
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

struct num* insertpoly(num* head, int* poly_toadd)
{
    num *p=NULL, *pr=head,*pre=head; //new pre->pr

    p=(struct num*)malloc(sizeof(struct num));
    if (p==NULL)
    {
        printf("No enough memory to allocate!");
        exit(0);
    }

    p->a=*(poly_toadd+1);
    p->b=*poly_toadd;
    p->next=NULL;

    if (head==NULL)  //if empty
    {
        head=p;
        //p->next=NULL;
    }
    else if (p->a < head->a)//如果比第一个数还小
    {
        p->next=head;
        head=p;
    }
    else
    {
        if(p->a == head->a)
        {
            head->b = head->b + p->b;
        }
        else //p->a  > head
        {
            while (((p->a)>(pr->a))&&(pr->next != NULL))
            {
                pre=pr;
                pr=pr->next;
            }
            if (p->a == pr->a)
            {
                pr->b = pr->b + p->b;
                free(p);//直接合并，新申请的块无用
            }
            else if (p->a < pr->a)
            {
                pre->next=p;
                p->next=pr;
            }
            else
            {
                pr->next=p;
            }
        }
    }

    /*else
    {
        while(pr != NULL)
        {
            if(p->a == pr->a)
            {
                pr->b = pr->b + p->b;
                free(p);
                goto end;
            }
            pr=pr->next;
        }
        pr = head;
        while(p->a > pr ->a)
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
    }
    end:*/
    return head;
}

//insert
struct num* insertnum(num* head, int num_toadd) ///
{
    num *p=NULL, *pr=head,*pre=head;

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
    else if (p->a <= head->a)//如果比第一个数还小
    {
        p->next=head;
        head=p;
    }
    else
    {
        while(p->a > pr ->a)
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
    }
    return head;
}

struct num* deletenum(num* head,int num_todelete) ///
{
    num *p=head, *pos=NULL, *pr=NULL;
    if(p == NULL)
    {
        printf("empty list can not delete anything.\n");
    }
    else
    {
        if(head->a == num_todelete)
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

int list_length(num* head)
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
            printf("%d\n",p->a);
            p=p->next;
        }while(p != NULL);
    }
}

void print_poly(num *head) ///
{
    num *p=head;
    int pnums[30][2]={0},i=0;
    if (head == NULL)
    {
        printf("empty\n");
    }
    else
    {
        do
        {
            if(p->b != 0)
            {
                pnums[i][0]=p->b;
                pnums[i][1]=p->a;
                i++;
            }
                //printf("%d      %d\n",p->b,p->a);
            p=p->next;
        }while(p != NULL);
    }
    i--;
    for (;i>=0;i--)
    {
        printf("[%d %d] ",pnums[i][0],pnums[i][1]);
    }
    printf("\n");
}

struct num *reverse(num *head) ///
{
    num *head2=NULL,*p=head,*endp=NULL;
    int length=list_length(head),nums[length];

    for (int i=0;i<length;i++)
    {
        nums[i]=p->a;
        p=p->next;
    }
    for (int i=length-1;i>=0;i--)
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
    while(1)
    {
        if(head==NULL)
            break;
        p=head;
        head=head->next;
        free(p);
    }
    return head2;
}


