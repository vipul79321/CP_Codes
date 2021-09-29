## Obtain mirror of Binary tree
[Link](https://www.geeksforgeeks.org/write-an-efficient-c-function-to-convert-a-tree-into-its-mirror-tree/)

**Solution Approach** - 
* Obtain mirror of root->left and root->right then swap both childs.
```c++
void mirror(node* Node)
{
    if (Node == NULL)
        return;
    else {
        node* temp;
 
        /* do the subtrees */
        mirror(Node->left);
        mirror(Node->right);
 
        /* swap the pointers in this node */
        temp = Node->left;
        Node->left = Node->right;
        Node->right = temp;
    }
}
```
---

## Check given two trees are Mirror of each other or not
[Link](https://www.geeksforgeeks.org/symmetric-tree-tree-which-is-mirror-image-of-itself/)

* For two trees to be mirror images, the following three conditions must be true
  1. Their root node's key must be same 
  2. left subtree of left tree and right subtree of right tree have to be mirror images
  3. right subtree of left tree and left subtree of right tree have to be mirror images


```c++
bool isMirror(struct Node* root1, struct Node* root2)
{
    // If both trees are empty
    // then they are mirror images
    if (root1 == NULL && root2 == NULL)
        return true;
    if (root1 && root2 && root1->key == root2->key)
        return isMirror(root1->left, root2->right)
               && isMirror(root1->right, root2->left);
 
    // if none of above conditions is true then root1
    // and root2 are not mirror images
    return false;
}
```

**Iterative Approach**-
[link](https://leetcode.com/problems/symmetric-tree/) 
* Do level order of both trees simultaneously, and for one tree insert right node before left node.
* And everytime make sure that values inserted are equal and finally make sure that both trees have been fully traversed.

---

## Check if two trees are structurally same
[Link](https://www.geeksforgeeks.org/foldable-binary-trees/)

```c++
bool isStructSame(node* root1, node* root2)
{
    if (root1 == NULL && root2 == NULL) {
        return true;
    }
    if (root1 != NULL && root2 != NULL && isStructSame(root1->left, root2->left) && isStructSame(root1->right, root2->right)) {
        return true;
    }
 
    return false;
}
```

---

## Inorder Traversal

**Recursive Inorder Traversal** | [Link](https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/)

```c++
void printInorder(Node *node)
{
  if(node == NULL)return;
  
  inorder(node->left);
  cout<<node->val<<" ";
  inorder(node->right);
}
```

**Iterative Inorder Traversal using stack** | [Link](https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/)

**Solution Approach** - 
* Intialize curr = root;
* While stack is not empty or curr != NULL
  * while curr != null, push curr into stack and update curr = curr->left
  * Now print stack.top(); then curr = stack.top(); then stack.pop();
  * Now if curr != NULL, curr = curr->right

```c++
void inOrder(struct Node *root)
{
    stack<Node *> s;
    Node *curr = root;
 
    while (curr != NULL || s.empty() == false)
    {
        /* Reach the left most Node of the
           curr Node */
        while (curr !=  NULL)
        {
            /* place pointer to a tree node on
               the stack before traversing
              the node's left subtree */
            s.push(curr);
            curr = curr->left;
        }
 
        /* Current must be NULL at this point */
        curr = s.top();
        s.pop();
 
        cout << curr->data << " ";
 
        /* we have visited the node and its
           left subtree.  Now, it's right
           subtree's turn */
        curr = curr->right;
 
    } /* end of while */
}
```

**Morris Inorder Traversal** | [Link]()

---

## Preorder Traversal

**Recursive Preorder Traversal** | [Link](https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/)

```c++
void preorder(TreeNode * node)
{
    if(node == NULL)return;
    
    cout<<node->data<<" ";
    preorder(node->left);
    preorder(node->right);
}
```

**Iterative Preorder Traversal** | [Link](https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/)

**Solution Approach** - 
* Create an empty stack nodeStack and push root node to stack. 
* Do the following while nodeStack is not empty. 
  * Pop an item from the stack and print it. 
  * Push right child of a popped item to stack 
  * Push left child of a popped item to stack

```c++
void iterativePreorder(node* root)
{
    // Base Case
    if (root == NULL)
        return;
    stack<TreeNode*> nodeStack;
    nodeStack.push(root);
  
    while (nodeStack.empty() == false) {
        // Pop the top item from stack and print it
        TreeNode* node = nodeStack.top();
        nodeStack.pop();
        cout<<node->data<<" ";
 
        // Push right and left children of the popped node to stack
        if (node->right)
            nodeStack.push(node->right);
        if (node->left)
            nodeStack.push(node->left);
    }
}
```

**Morris Preorder Traversal** | [Link]()


---

## Postorder Traversal 

**Recursive Postorder Traversal** | [Link](https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/)

```c++
void postorder(TreeNode * node)
{
    if(node == NULL)return;
    
    postorder(node->left);
    postorder(node->right);
    cout<<node->data<<" ";
}
```

**Iterative Postorder Traversal** | [using-two-stack](https://www.geeksforgeeks.org/iterative-postorder-traversal/) | [using-one-stack](https://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/)

**Using two-stacks** - 
* Completely similar to Iterative Preorder traversal with following changes - 
  * Push left child first then right child into the stack.
  * While popping instead of printing push that node into second stack
* Finally pop and print all the elements of second stack

**Using one-stack** - 
* 1 - Create an empty stack
* 2 - Do following while root is not NULL
  * Push root's right child and then root to stack.
  * Set root as root's left child.
* 3 - Pop an item from stack and set it as root.
  * If the popped item has a right child and the right child is at top of stack, then remove the right child from stack, push the root back and set root as root's right child
  * Else print root's data and set root as NULL.
* Repeat steps 2 and 3 while stack is not empty.

```c++
void postOrderIterative(struct Node* root)
{
    // Check for empty tree
    if (root == NULL) return;
    
    stack<TreeNode*>st;

    do
    {
        // Move to leftmost node
        while (root)
        {
            // Push root's right child and then root to stack.
            if (root->right)
              st.push(root->right);

            st.push(root);
 
            // Set root as root's left child
            root = root->left;
        }
 
        // Pop an item from stack and set it as root    
        root = pop(stack);
 
        // If the popped item has a right child and the right child is not
        // processed yet, then make sure right child is processed before root
        if (!st.empty() && root->right && st.top() == root->right)
        {
            st.pop(); // remove right child from stack
            st.push(root); // push root back to stack
            root = root->right; // change root so that the right
                                // child is processed next
        }
        else // Else print root's data and set root as NULL
        {
            cout<<root->data<<" ";
            root = NULL;
        }
    } while (!st.empty());
}
```

**Morris Postorder Traversal** 

---









