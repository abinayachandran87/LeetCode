/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct stNode {
    struct TreeNode* tn;
    struct stNode *next;
};

void push(struct stNode** top, struct TreeNode* tree)
{
    struct stNode *stack = NULL;
    stack = (struct stNode *)malloc(sizeof(struct stNode));
    if (stack == NULL)
    {
        printf("Memory error\n"); 
        return;
    }       
       
    stack->tn = tree;
    stack->next = *top;
    *top = stack;

}

int isStackEmpty(struct stNode* top)
{
    if (top == NULL)
        return 1;
    else
        return 0;
}
struct TreeNode* pop(struct stNode** top)
{
    struct TreeNode *poppedNode = NULL;
    struct stNode *stk = NULL;

    stk = *top;
    poppedNode = stk->tn;
    *top = stk->next;
    free(stk);
    stk = NULL;

    return poppedNode;
}

int findNoOfLeaves(struct TreeNode* root)
{
    int count = 0;
    if (root)
    {
        count = 1 + findNoOfLeaves(root->left) + findNoOfLeaves(root->right);
    }
    else
        count = 0;
    return count;
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int *inordArr = NULL, *currPtr = NULL;
    struct TreeNode * current = NULL;
    struct stNode * stack = NULL;
    int done = 0, treeSize = 0, leafCount = 0;
    
    treeSize = findNoOfLeaves(root);
    inordArr = (int *)malloc(sizeof(int)*treeSize);
    if (!inordArr)
    {
        printf("Malloc error\n");
        return -1;
    }
    currPtr = inordArr;
    current = root;
    while(!done)
    {
        if (current!=NULL)
        {
            push(&stack, current);
            current = current->left;
        }
        else
        {
            if (!isStackEmpty(stack))
            {
                current = pop(&stack);
                if (leafCount < treeSize)
                    inordArr[leafCount] = current->val;
                leafCount++;
                current = current->right;
            }
            else
            {
                done = 1;
            }
        }
    }
    *returnSize = leafCount;
  
    return inordArr;
}
