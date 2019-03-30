#include <bits/stdc++.h>

using namespace std;

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}node;

int num[1024];
int num_ordered[1024];
int idx=0;
int search_cnt=0;


node* create_bstree(node* root);
void free_bst(node* root);
void order_output(node* root);
node* search_bst(node* root,int num_tofind);
void del_node(node* root,int num_todel);
int bin_ser(int* num,int num_tosearch);

int main()
{
    node* root=NULL;
    node* root_rand=NULL;
    float average_order_cnt;
    float average_rand_cnt;

    int i=0,temp=1;

    //create ordered list
    for (i=0;temp<2048;i++)
    {
        num[i]=temp;
        num_ordered[i]=temp;
        temp += 2;
    }
    ///顺序建树
    for (idx=0;idx<1024;idx++)
    {
        root=create_bstree(root);
    }
    order_output(root);
    printf("\n");

    random_shuffle(num,num+1024);

    ///乱序建树
    for (idx=0;idx<1024;idx++)
    {
        root_rand=create_bstree(root_rand);
    }
    //ordering
    order_output(root_rand);
    printf("\n");

    ///查找长度计数
    average_order_cnt=0;
    average_rand_cnt=0;

    for(temp=0;temp<1024;temp++)
    {
        search_bst(root,2*temp+1);
        average_order_cnt = average_order_cnt+search_cnt;
    }
    average_order_cnt=average_order_cnt/1024.0;

    for(temp=0;temp<1024;temp++)
    {
        search_bst(root_rand,2*temp+1);
        average_rand_cnt = average_rand_cnt+search_cnt;
    }
    average_rand_cnt=average_rand_cnt/1024.0;

    printf("average length of ordered_list BST:%.1f\n",average_order_cnt);
    printf("average length of random_list BST:%.1f\n",average_rand_cnt);

    ///查找失败
    average_order_cnt=0;
    average_rand_cnt=0;

    for(temp=0;temp<1024;temp++)
    {
        search_bst(root,2*temp);
        average_order_cnt = average_order_cnt+search_cnt;
    }
    average_order_cnt=average_order_cnt/1024.0;

    for(temp=0;temp<1024;temp++)
    {
        search_bst(root_rand,2*temp);
        average_rand_cnt = average_rand_cnt+search_cnt;
    }
    average_rand_cnt=average_rand_cnt/1024.0;

    printf("average length of find failure ordered_list BST:%.1f\n",average_order_cnt);
    printf("average length of find failure random_list BST:%.1f\n",average_rand_cnt);


    ///二分查找
    average_order_cnt=0;

    for(temp=0;temp<1024;temp++)
    {
        bin_ser(num_ordered,2*temp+1);
        average_order_cnt = average_order_cnt+search_cnt;
    }
    average_order_cnt=average_order_cnt/1024.0;

    printf("average length of ordered_list BS:%.1f\n",average_order_cnt);

    average_order_cnt=0;

    for(temp=0;temp<1024;temp++)
    {
        bin_ser(num_ordered,2*temp);
        average_order_cnt = average_order_cnt+search_cnt;
    }
    average_order_cnt=average_order_cnt/1024.0;

    printf("average length of find failure ordered_list BS:%.1f\n",average_order_cnt);



    //test find
    int k;
    scanf(" %d",&k);
    printf("finding %d, have found:%d\n",k,search_bst(root,k)->data);

    //test delete
    del_node(root,k);
    order_output(root);
    printf("\n");



    //free
    free_bst(root);
    free_bst(root_rand);

    return 0;
}

int bin_ser(int* num,int num_tosearch)
{///二分查找，返回数组index

    int idx_l=0;
    int idx_h=1023;
    int mid;
    search_cnt=0;
    while (idx_l<=idx_h)
    {
        mid = (idx_h+idx_l)/2;
        search_cnt++;
        if (num[mid] == num_tosearch)
            return mid;
        else if (num[mid]>num_tosearch)
        {
            idx_h=mid-1;
        }
        else
            idx_l=mid+1;
    }
    return -1;
}

void del_node(node* root,int num_todel)
{
    node* before_del;
    node* replace_node;
    node* before_rplc;
    int lr_flag;
    while(1)
    {
        if (root == NULL)
        {
            printf("fail to find the number to delete!\n");
            return;
        }
        if (root->data == num_todel)
        {
            break;
        }
        else if (root->data > num_todel)
        {
            before_del=root;
            root=root->left;
            lr_flag=0;//左右标志，待删除节点为左结点
        }
        else
        {
            before_del=root;
            root=root->right;
            lr_flag=1;
        }
    }//找到了需要删的节点和前节点

    if ((root->left == NULL)&&(root->right == NULL))
    {//如果为叶，则直接删
        if (lr_flag)
            before_del->right=NULL;
        else
            before_del->left=NULL;
    }
    //只有一边的，直接接上
    else if((root->left == NULL)&&(root->right != NULL))
    {
        if (lr_flag)
            before_del->right=root->right;
        else
            before_del->left=root->right;
    }
    else if((root->left != NULL)&&(root->right == NULL))
    {
        if (lr_flag)
            before_del->right=root->left;
        else
            before_del->left=root->left;
    }
    //两边都有，找右边最小替代被删的节点
    else
    {
        before_rplc=root;
        replace_node=root->right;
        while(replace_node->left != NULL)
        {//找到左下角
            before_rplc=replace_node;
            replace_node=replace_node->left;
        }
        if (lr_flag)
            before_del->right=replace_node;
        else
            before_del->left=replace_node;
        if (before_rplc == root)
        {
            replace_node->left=root->left;
        }
        else
        {
        replace_node->left=root->left;
        replace_node->right=root->right;
        before_rplc->left=replace_node->right;
        }
    }
    free(root);
}

node* search_bst(node* root,int num_tofind)
{
    search_cnt=0;
    while(1)
    {
        if (root == NULL)
        {
            //printf("fail to find the number!\n");
            return NULL;
        }
        search_cnt++;
        if (root->data == num_tofind)
            return root;
        else if (root->data > num_tofind)
            root=root->left;
        else
            root=root->right;
    }
}


void order_output(node* root)
{
    if (root == NULL) return;
    else
    {
        //recur_inorder
        if(root->left != NULL)
        {
            order_output(root->left);
        }
        printf("%d ",root->data);
        if(root->right != NULL)
        {
            order_output(root->right);
        }
    }
}


node* create_bstree(node* root)
{
    node* p=root;
    node* pr;
    int lr_flag=0;
    if (root == NULL)
    {
        root=(node*)malloc(sizeof(node));
        root->data=num[idx];
        root->left=NULL;
        root->right=NULL;
    }
    else
    {
        while(p!=NULL)
        {
            if (p->data < num[idx])
            {
                pr=p;
                p=p->right;
                lr_flag=0;
            }
            else
            {
                pr=p;
                p=p->left;
                lr_flag=1;
            }
        }
        p=(node*)malloc(sizeof(node));
        p->data=num[idx];
        p->left=NULL;
        p->right=NULL;
        if (lr_flag)
            pr->left=p;
        else
            pr->right=p;
    }
    return root;
}

void free_bst(node* root)
{
    node* cur=root;
    node* que_p[1026];
    int _front=0,_rear=0;
    if (root == NULL) return;
    que_p[++_rear]=root;
    while (_front != _rear)
    {
        cur=que_p[++_front];
        if(cur->left != NULL)
            que_p[++_rear]=cur->left;
        if(cur->right != NULL)
            que_p[++_rear]=cur->right;
        free(cur);
    }
}









