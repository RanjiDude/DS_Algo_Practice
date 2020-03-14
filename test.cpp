#include <iostream>
#include <vector>
#include <queue>
#include <stack>

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void printvec(std::vector<int> vec)
{
    for (std::vector<int>::iterator it = vec.begin(); it!=vec.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void BFS(TreeNode *root)
{
    std::queue<TreeNode> q;
    q.push(*root);

    std::vector<int> t;

    while(!q.empty())
    {
        TreeNode node = q.front();
        q.pop();
        
        t.push_back(node.val);
        if (node.left != NULL)
        {
            q.push(*node.left);
        }
        if (node.right != NULL)
        {
            q.push(*node.right);
        }
    }
    printvec(t);
}

std::vector<int> helper(TreeNode *root, std::vector<int> t)
{
    if (root != NULL)
    {
        t.push_back(root->val);
    }
    // if (root.left != NULL)
    // {
    //     helper(root.left, t);
    // }
    // if (root.right != NULL)
    // {
    //     helper(root.right, t);
    // }
    std::vector<int> ve;
    return ve;
}

void DFS_Recursive_Preorder(TreeNode *root)
{
    std::vector<int> t = helper(root, t);
    printvec(t);
}

void DFS_Iterative_Preorder(TreeNode *root)
{
    std::vector<int> t;
    std::stack<TreeNode> s;
    if (root != NULL)
    {
        s.push(*root);
    }
    
    while(!s.empty())
    {
        TreeNode node = s.top();
        s.pop();
        
        t.push_back(node.val);

        if (node.right != NULL)
        {
            s.push(*node.right);
        }
        if (node.left != NULL)
        {
            s.push(*node.left);
        }
    }
    printvec(t);
}

bool uniValue(TreeNode *root)
{
    int v = root->val;
    std::queue<TreeNode> q;
    q.push(*root);

    while(!q.empty())
    {
        TreeNode node = q.front();
        q.pop();
        
        if (node.val != v)
        {
            return false;
        }

        if (node.left != NULL)
        {
            q.push(*node.left);
        }
        if (node.right != NULL)
        {
            q.push(*node.right);
        }
    }
    return true;
}

int main()
{
    TreeNode a(1), b(2), c(3), d(4), e(5), f(6), g(7);

    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = &f;
    c.right = &g;

    // BFS(&a);
    // DFS_Iterative_Preorder(&a);
    DFS_Recursive_Preorder(&a);

    // std::cout << std::boolalpha << uniValue(&a) << std::endl;

}
