#include<bits/stdc++.h>

using namespace std;

typedef struct node
{
    char a;
    struct node *parent,*lchild,*rchild;
}node;

char input[8][3];

node* build_tree(void);
node* create_preorder(node* opr_node);
node* recur_pre_trav(node* root);
node* recur_in_trav(node* root);
node* recur_pos_trav(node* root);
node* pre_trav(node* root);
node* in_trav(node* root);
node* pos_trav(node* root);


int main()
{
    node* root;
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
    //fscanf(fp," %c %c %c ",&a,&b,&c);
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
    recur_pre_trav(root);
    printf("\n");
    recur_in_trav(root);
    printf("\n");
    recur_pos_trav(root);
    return 0;
}

/*node* pre_trav(node* root)
{

}*/

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
    //int cur;//current node->a

    root=(node*)malloc(sizeof(node));
    if (root==NULL)
    {
        printf("No enough memory to allocate!");
        exit(0);
    }
    root->a=input[0][0];
    root->parent=NULL;
    root->lchild=NULL;
    root->rchild=NULL;
    //cur = root->a;
    create_preorder(root);

    return root;
}

node* create_preorder(node* opr_node)
{
    node* p=NULL;
    int deadend=1;
    //int nothing=;
    if(opr_node != NULL)
    {
        for(int i=1;i<8;i++)
        {
            if(input[i][1] == (opr_node->a))
            {
                deadend=0;
                p=(node*)malloc(sizeof(node));
                p->a=input[i][0];
                p->parent=opr_node;
                p->lchild=NULL;
                p->rchild=NULL;
                //printf(" %c ",input[i][0]);
                if (input[i][2]=='R')
                {
                    opr_node->rchild=p;
                    //printf(" R ");
                }
                else
                {
                    opr_node->lchild=p;
                    //printf(" L ");
                }
            }
        }
    }
    if (deadend)
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




