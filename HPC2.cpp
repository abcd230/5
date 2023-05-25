#include<iostream>
#include<omp.h>
#include<stack>
#include<queue>

using namespace std;

struct Treenode
{
    int val;
    Treenode* left;
    Treenode* right;
    Treenode(int x): val(x),left(NULL),right(NULL){}
};

void bfs(Treenode* root)
{
    queue<Treenode*> q;
    q.push(root);
    while(!q.empty())
    {
        int qs=q.size();
        #pragma omp parallel for
        for(int i=0;i<qs;i++)
        {
            Treenode* node;
            #pragma omp critical
            {
                node=q.front();
                cout<<node->val;
                q.pop();
                if(node->left)q.push(node->left);
                if(node->right)q.push(node->right);

            }
        }
    }
}

void dfs(Treenode* root)
{
    stack<Treenode*> s;
    s.push(root);
    while(!s.empty())
    {
        int qs=s.size();
        #pragma omp parallel for 
        for(int i=0;i<qs;i++)
        {
            Treenode* node;
            #pragma omp critical
            {
                node=s.top();
                cout<<node->val;
                s.pop();
                if(node->right)s.push(node->right);
                if(node->left)s.push(node->left);
            }
        }
    }

}



int main()
{
    Treenode* tree=new Treenode(1);
    tree->left=new Treenode(2);
    tree->right=new Treenode(3);
    tree->left->left=new Treenode(4);
    tree->left->right=new Treenode(5);
    tree->right->left=new Treenode(6);
    tree->right->right=new Treenode(7);
    

    cout<<"Parallel BFS";
    pbfs(tree);
    cout<<endl<<"Parallel DFS";
    pdfs(tree);
    return 0;


}
