#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char a;
    struct node *parent,*lchild,*rchild;
    int rcin;
}node;

char input[8][3];

node* build_tree(void);
node* create_preorder(node* opr_node);
node* recur_pre_trav(node* root);
node* recur_in_trav(node* root);
node* recur_pos_trav(node* root);
void pre_trav(node* root);
void in_trav(node* root);
void pos_trav(node* root);
void level_trav(node* root);
void disp(node* root);
void is_comlete(node* root);

int main()
{
    node* root=NULL;
    char a,b,c;//three input
    int nouse1,nouse2,i=0;//scan input array
    FILE *fp=NULL;
    if((fp = fopen("ex2_tree1.txt","a+"))==NULL)
    {
        printf("fail to open the file");
        exit(0);
    }
    fscanf(fp," %c ",&a);
    fscanf(fp," %d ",&nouse1);
    fscanf(fp," %d ",&nouse2);
    //printf("%c %d %d ",a,b,c);
    input[0][0]=a;
    input[0][1]=-1;
    input[0][2]=-1;
    i++;

    while(fscanf(fp," %c %c %c ",&a,&b,&c)>2)
    {
        //printf("%c %c %c ",a,b,c);
        input[i][0]=a;
        input[i][1]=b;
        input[i][2]=c;
        i++;
    }

    //test input
    /*for (int j=0;j<8;j++)
    {
        for (int k=0;k<3;k++)
        {
            printf("%c",input[j][k]);
        }
    }*/
    fclose(fp);

    root=build_tree();
    printf("display of the btree:\n");
    disp(root);
    printf("recursive preorder:\n");
    recur_pre_trav(root);
    printf("\nrecursive inorder:\n");
    recur_in_trav(root);
    printf("\nrecursive posorder:\n");
    recur_pos_trav(root);
    printf("\nnon recursive preorder:\n");
    pre_trav(root);
    printf("\nnon recursive inorder:\n");
    in_trav(root);
    printf("\nnon recursive posorder:\n");
    pos_trav(root);
    printf("\nnon recursive levelorder:\n");
    level_trav(root);
    printf("\nis_comlete?: ");
    is_comlete(root);
    return 0;
}

void is_comlete(node* root)
{
    node* cur;
    node* q[10];
    int front=0,rear=0;
    int noo=0;
    if (root == NULL) return;
    q[++rear]=root;
    while(front != rear)
    {
        cur=q[++front];
        cur->rcin=front;
        if (cur->parent != NULL)
        {
            if((cur->rcin)/2 != cur->parent->rcin)
            {
                noo=1;
                printf("not complete!\n");
                break;
            }
        }
        //printf("%d",front);
        if(cur->lchild != NULL)
            q[++rear]=cur->lchild;
        if(cur->rchild != NULL)
            q[++rear]=cur->rchild;
    }
    if (!noo)
        printf("complete!");
}

void disp(node* root)
{
    node* cur;
    node* q[10];
    int front=0,rear=0;
    if (root == NULL) return;
    q[++rear]=root;
    while(front != rear)
    {
        cur=q[++front];
        printf("%c",cur->a);
        if(cur->lchild != NULL)
        {
            printf("    L:%c",cur->lchild->a);
        }
        if(cur->rchild != NULL)
        {
            printf("    R:%c",cur->rchild->a);
        }
        printf("\n");
        if(cur->lchild != NULL)
            q[++rear]=cur->lchild;
        if(cur->rchild != NULL)
            q[++rear]=cur->rchild;
    }
}

void level_trav(node* root)
{
    node* cur;
    node* q[10];
    int front=0,rear=0;
    if (root == NULL) return;
    q[++rear]=root;
    while(front != rear)
    {
        cur=q[++front];
        printf("%c ",cur->a);
        if(cur->lchild != NULL)
            q[++rear]=cur->lchild;
        if(cur->rchild != NULL)
            q[++rear]=cur->rchild;
    }
}
void pos_trav(node* root)
{
    node* s[8];
    int top=-1;
    if(root == NULL)
        return;
    else
        s[++top]=root;
    while((root != NULL)||(top != -1))
    {
        while(root != NULL)
        {
            if(root != s[top])//防止父节点重复入栈
                s[++top]=root;
            s[++top]=root->rchild;
            s[++top]=root->lchild;
            root->rcin=1;
            root=root->lchild;
        }
        if(top != -1)
        {
            if(s[top]==NULL)
            {
                top--;
            }
            else if((s[top]->rchild == NULL)&&(s[top]->lchild == NULL))
            {
                printf("%c ",s[top]->a);
                top--;
            }
            else if(s[top]->rcin == 1)
            {
                printf("%c ",s[top]->a);
                top--;
            }
            else
            {
                root=s[top];
            }
        }
    }
}

void in_trav(node* root)
{
    node *s[8];
    int top = -1;
    while((root != NULL) || (top != -1))
    {
        while (root != NULL)
        {
            s[++top]=root;
            root=root->lchild;
        }
        if(top != -1)
        {
            root = s[top--];
            printf("%c ",root->a);
            root = root->rchild;
        }
    }
}

void pre_trav(node* root)
{
    node* s[8];//stack
    int top=-1;

    while ((root != NULL) || (top != -1) )
    {
        while(root != NULL)
        {
            printf("%c ",root->a);
            s[++top]=root;
            root = root->lchild;
        }
        if (top != -1)
        {
            root = s[top--];
            root = root->rchild;
        }
    }
}

node* recur_pos_trav(node* root)
{
    if(root->lchild != NULL)
    {
        recur_pos_trav(root->lchild);
    }
    if(root->rchild != NULL)
    {
        recur_pos_trav(root->rchild);
    }
    printf("%c ",root->a);
    return root;
}

node* recur_in_trav(node* root)
{
    if(root->lchild != NULL)
    {
        recur_in_trav(root->lchild);
    }
    printf("%c ",root->a);
    if(root->rchild != NULL)
    {
        recur_in_trav(root->rchild);
    }
    return root;
}

node* recur_pre_trav(node* root)
{
    printf("%c ",root->a);
    if(root->lchild != NULL)
    {
        recur_pre_trav(root->lchild);
    }
    if(root->rchild != NULL)
    {
        recur_pre_trav(root->rchild);
    }
    return root;
}

node* build_tree(void)
{
    node *root=NULL;
    root=(node*)malloc(sizeof(node));
    if (root==NULL)
    {
        printf("No enough memory to allocate!");
        exit(0);
    }
    root->a=input[0][0];//初始化根
    root->parent=NULL;
    root->lchild=NULL;
    root->rchild=NULL;

    create_preorder(root);
    return root;
}

node* create_preorder(node* opr_node)
{
    node* p=NULL;
    int deadend=1;//匹配标志位
    if(opr_node != NULL)
    {
        for(int i=1;i<8;i++)
        {
            if(input[i][1] == (opr_node->a))
            {
                deadend=0;//匹配到
                p=(node*)malloc(sizeof(node));
                p->a=input[i][0];
                p->parent=opr_node;
                p->lchild=NULL;
                p->rchild=NULL;
                p->rcin=0;
                if (input[i][2]=='R')
                {
                    opr_node->rchild=p;
                }
                else
                {
                    opr_node->lchild=p;
                }
            }
        }
    }
    if(deadend)//已经是叶节点
        return opr_node->parent;
    if(opr_node->lchild != NULL)
    {
        p=opr_node->lchild;
        p=create_preorder(p);
    }
    if(opr_node->rchild != NULL)
    {
        p=opr_node->rchild;
        p=create_preorder(p);
    }
    return opr_node->parent;
}




