#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <iostream>
#include <cassert>
#include <utility>
using namespace std;

template<typename T>
class RBTree
{
  public:
    RBTree() : data(nullptr), count(0) { }
    ~RBTree();

    bool contains (const T& item) const { return contains (data, item); }
    void add (const T& item);
    bool remove (const T& item);
    int size() const { return count; }

    bool isValidRBTree() const;  // should always be true! If not, error

  private:
    struct TreeNode
    {
      bool red;
      T datum;
      TreeNode* left;
      TreeNode* right;
      TreeNode* parent;

      TreeNode (T d, TreeNode* p, bool r)
        : red(r), datum(d), left(nullptr), right(nullptr), parent(p) { }
      TreeNode (T d, TreeNode* p)
        : TreeNode(d, p, true) { }

      bool isTwoNode() const;
      bool isFourNode() const;
      /** Returns num black edges from here to leaf, or -1 if not valid RB*/
      int validateAndCountBlack() const;
    };


    TreeNode* data;
    int count;


    static void deleteWithSubtrees(TreeNode* data);

    static bool contains (const TreeNode* root, const T& item);
    static void addToBranch (TreeNode* parent,
                        TreeNode*& child, const T& item);
    static void addBelow (TreeNode* root, const T& item);
    static void splitFour (TreeNode* node);
    static void maybeRotate (TreeNode* node);

    static bool remove (TreeNode* root, const T& item);
    static void removeItemIn (TreeNode* root);
    static void replaceParentsChild (TreeNode* node, TreeNode* child);
    static void replaceNodesParent (TreeNode* node, TreeNode* child);
    static void rotateThreeNodeLeft (TreeNode* node);
    static void rotateThreeNodeRight (TreeNode* node);
    static void guaranteeRedLeaf (TreeNode* root, bool seekRight);
    static TreeNode* successor(TreeNode* node);


    //for debugging
    friend class TreeDump;
    friend class Unci_TreeDump_test;
    RBTree(TreeNode* root, int ct) : data(root), count(ct) { }
};


// This include is here intentionally; explained in README
#include "TreeDump.h"



//These need to be in the .h file because they are templated:

// public RBTree methods

template<typename T>
RBTree<T>::~RBTree()
{
  deleteWithSubtrees(data);
}

template<typename T>
void RBTree<T>::add(const T& item)
{
  addToBranch (nullptr, data, item);
  ++count;
//  if (data->parent != nullptr)  // why is this if statement here? what
  //  data = data->parent;       // happens if it is commented out?
  data->red = false;  // special case for root
}

template<typename T>
bool RBTree<T>::remove(const T& item)
{
  if (count == 1 && data->datum == item)  // special case: rm only item
  {
    delete data;
    data = nullptr;
    count = 0;
    return true;
  }
  else
  {
    if (count >= 3 and data->isTwoNode()
          and data->left->isTwoNode() and data->right->isTwoNode())
    {
      // special root "fusion" case
      data->left->red = true;
      data->right->red = true;
    }

    bool removed = remove (data, item);
    if (removed)
      --count;
    return removed;
  }
}


// private RBTree methods

template<typename T>
void RBTree<T>::deleteWithSubtrees(TreeNode* root)
{
  if (root == nullptr)
    return;

  deleteWithSubtrees(root->left);
  deleteWithSubtrees(root->right);
  delete root;
}

template<typename T>
bool RBTree<T>::contains (const TreeNode* root, const T& item)
{
  if (root == nullptr)
    return false;
  else if (root->datum == item)
    return true;
  else if (item < root->datum)
    return contains(root->left, item);
  else // root->datum < item
    return contains(root->right, item);
}

template<typename T>
void RBTree<T>::addToBranch (TreeNode* parent,
                        TreeNode*& branch, const T& item)
{
  if (branch == nullptr)
  {
    branch = new TreeNode(item, parent);
    maybeRotate(branch);
  }
  else
  {
    if (branch->isFourNode())
      splitFour(branch);

    addBelow (branch, item);
  }
}

template<typename T>
void RBTree<T>::addBelow (TreeNode* root, const T& item)
{
  assert (root != nullptr);

  if (item < root->datum)
    addToBranch (root, root->left, item);
  else // root->datum <= item
    addToBranch (root, root->right, item);
}

template<typename T>
void RBTree<T>::splitFour (TreeNode* node)
{
  assert (node->isFourNode());

  node->left->red = false;
  node->right->red = false;
  node->red = true;
  maybeRotate(node);
}

template<typename T>
void RBTree<T>::maybeRotate (TreeNode* node)
{
  assert (node != nullptr);
  if (node->red and node->parent != nullptr and node->parent->red)
  {
    // cerr << "About to rotate:\n";
    // TreeDump::toStream<T>(node->parent->parent, cerr);

    // inside an unbalanced 4-node, so rotate.  
    // First, get a handle on existing nodes that may move:
    TreeNode* parent = node->parent;
    TreeNode* grandparent = parent->parent;

    TreeNode *B, *D, *F; // will point to node, parent, grandparent
    TreeNode *c, *e; // will point to middle children;

    if (node == parent->left and parent == grandparent->left)
    { // Case 1
      B = node;
      D = parent;
      F = grandparent;
      c = B->right;
      e = D->right;
    }
    else if (node == parent->right and parent == grandparent->right)
    { // Case 2
      B = grandparent;
      D = parent;
      F = node;
      c = D->left;
      e = F->left;
    }
    else if (node == parent->right and parent == grandparent->left)
    { // Case 3
      B = parent;
      D = node;
      F = grandparent;
      c = D->left;
      e = D->right;
    }
    else //(node == parent->left and parent == grandparent->right)
    { // Case 4
      
      B = grandparent;
      F = parent;
      D = node;
      c = D->left;
      e = D->right;
    }

    // Then, perform rotation:
    replaceParentsChild(grandparent, D); // root special, handled later
    D->parent = grandparent->parent;
    D->left = B;
    D->right = F;
    D->red = false;

    B->parent = D;
    B->right = c;
    B->red = true;

    F->parent = D;
    F->left = e;
    F->red = true;

    if (c != nullptr)
      c->parent = B;
    if (e != nullptr)
      e->parent = F;
  }
}


template<typename T>
bool RBTree<T>::remove (TreeNode* root, const T& item)
{
  if (root == nullptr)
    return false;

  //cerr << "remove item " << item << " from" << endl;
  //TreeDump::toStream<T> (root, cerr);

  guaranteeRedLeaf(root, (root->datum <= item));

  if (root->datum == item)
  {
    removeItemIn(root);
    return true;
  }
  else if (item < root->datum)
    return remove(root->left, item);
  else // (root->datum < item)
    return remove(root->right, item);
}

template<typename T>
void RBTree<T>::removeItemIn (TreeNode* node)
{
  assert (node != nullptr);
  //cerr << "remove item in" << endl;
  //TreeDump::toStream<T> (node, cerr);

  if (node->left != nullptr and node->right != nullptr)
  {
    TreeNode* next = successor(node);  // guaranteed to have null on left
    swap (node->datum, next->datum);
    removeItemIn(next);
  }
  else  // red leaf
  {
    assert (node->parent != nullptr); // already handled as special case
    assert (node->red);
    assert (node->left == nullptr);
    assert (node->right == nullptr);

    if (node->left == nullptr) // leaf or has right child
    {
      replaceParentsChild(node, node->right);
      replaceNodesParent(node->right, node->parent);
      delete node;
    }
    else // node->right == nullptr
    {
      replaceParentsChild(node, node->left);
      replaceNodesParent(node->left, node->parent);
      delete node;
    }
  }
}

template<typename T>
void RBTree<T>::replaceParentsChild (TreeNode* node, TreeNode* child)
{
  if (node->parent == nullptr)
    return;

  if (node->parent->left == node)
    node->parent->left = child;
  else 
  {
    assert (node->parent->right == node);
    node->parent->right = child;
  }
}

template<typename T>
void RBTree<T>::replaceNodesParent (TreeNode* node, TreeNode* parent)
{
  if (node != nullptr)
    node->parent = parent;
}

template<typename T>
void RBTree<T>::rotateThreeNodeLeft (TreeNode* node)
{
  TreeNode* child = node->right;
  assert(not node->red);
  assert(child->red);

  TreeNode* B = node;
  TreeNode* D = child;
  TreeNode* c = D->left;

  replaceParentsChild(B, D);
  D->parent = B->parent;
  D->left = B;
  D->red = false;

  B->parent = D;
  B->right = c;
  B->red = true;

  if (c != nullptr)
    c->parent = B;
}

template<typename T>
void RBTree<T>::rotateThreeNodeRight (TreeNode* node)
{
  // XXX: currently buggy!
  TreeNode* child = node->left;
  assert (not node->red);
  assert (child->red);

  TreeNode* B = child;
  TreeNode* D = node;
  //changed B->left to right
  TreeNode* c = B->right;

  replaceParentsChild(D, B);
  B->parent = D->parent;
  //changed left = c to right = D
  B->right = D;
  B->red = false;


  D->parent = B;
  
  D->left = c;
  D->red = true;


  if (c != nullptr)
    c->parent = D;
}

template<typename T>
void RBTree<T>::guaranteeRedLeaf (TreeNode* node, bool seekRight)
{
  assert (node != nullptr);
  if (node->red)
    return;
  if (node->isFourNode())
    return;

  if (node->right != nullptr and node->right->red)
  {
    if (seekRight)
      return;
    else
      rotateThreeNodeLeft (node);
  }
  else if (node->left != nullptr and node->left->red)
  {
    if (seekRight)
      rotateThreeNodeRight(node);
    else
      return;
  }
  else
  {
    assert (node->isTwoNode());
    if (node->parent == nullptr)            // 2-node root is special
      return;

    assert (node->parent->parent == nullptr or node->parent->red);

    if (node->parent->left->isTwoNode()
        and node->parent->right->isTwoNode())
    { // Case 1
      //borrow from parent to make 4-node
      assert (node->parent->red); // root fusion case handled elsewhere
      node->parent->red = false;
      node->parent->left->red = true;
      node->parent->right->red = true;
    }
    else if (node == node->parent->left
             and node->parent->right->left != nullptr
             and node->parent->right->left->red)
    { // Case 2
      TreeNode* B = node;
      TreeNode* D = node->parent;
      TreeNode* F = node->parent->right->left;
      TreeNode* H = node->parent->right;
      TreeNode* e = F->left;

      replaceParentsChild(D, F);
      F->parent = D->parent;
      F->left = D;
      H->left = F->right;
      F->right = H;
      F->red = D->red;
      H->parent = F;
      H->red = false;

      D->parent = F;
      assert (D->left == B);
      D->right = e;
      D->red = false;
      B->red = true;
      if (e != nullptr)
	e->parent = D;

    }
    else if (node == node->parent->left
             and node->parent->right->right != nullptr
             and node->parent->right->right->red)
    { // Case 3
      // move sibling up, parent down
      TreeNode* B = node;
      TreeNode* D = node->parent;
      TreeNode* F = node->parent->right;
      TreeNode* H = node->parent->right->right;
      TreeNode* e = F->left;

      replaceParentsChild(D, F);
      F->parent = D->parent;
      F->left = D;
      assert (F->right == H);
      F->red = D->red; // true unless D was root

      H->red = false;

      D->parent = F;
      assert (D->left == B);
      D->right = e;
      D->red = false;

      B->red = true;

      if (e != nullptr)
        e->parent = D;
    }
    else if (node == node->parent->right
             and node->parent->left->right != nullptr
	     and node->parent->left->right->red)
    { // Case 4
      TreeNode* B = node->parent->left; 
      TreeNode* D = node->parent->left->right;
      TreeNode* F = node->parent;
      TreeNode* H = node;
      TreeNode* e = D->right;
      TreeNode* c = D->left;

      replaceParentsChild(F, D);
      D->parent = F->parent;
      D->right = F;
      D->left = B;
      D->red = F->red;

      B->parent = D;
      B->right = c;
      
      F->parent = D;
      F->left = e;
      F->red = false;
      
      H->red = true;

      if (c != nullptr)
       c->parent = B;

      if (e != nullptr)
       e->parent = F;	
    }
    else if (node == node->parent->right
	     and node->parent->left->left != nullptr
	     and node->parent->left->left->red)
    { // Case 5
      TreeNode* B = node->parent->left->left;
      TreeNode* D = node->parent->left;
      TreeNode* F = node->parent;
      TreeNode* H = node;
      TreeNode* e = D->right;

      replaceParentsChild(F, D);
      D->parent = F->parent;
      D->right = F;
      D->left = B;
      D->red = F->red;
      assert (D->left == B);

      B->red = false;

      F->parent = D;
      F->left = e;
      F->red = false;
      
      H->red = true;

      if (e != nullptr)
	e->parent = F;

    }
    else
    {
      TreeDump::toStream<T>(node->parent->parent, cerr);
      throw "This case should be unreachable";
    }
  }
}


template<typename T>
typename RBTree<T>::TreeNode* RBTree<T>::successor(TreeNode* node)
{
  if (node->right == nullptr)
    return nullptr;

  TreeNode* retval = node->right;
  guaranteeRedLeaf(retval, false);


  while (retval->left != nullptr)
  {
    retval = retval->left;
    guaranteeRedLeaf(retval, false);
  }

  return retval;
}


template<typename T>
bool RBTree<T>::isValidRBTree() const
{
  return data == nullptr
      or (not data->red
          and data->validateAndCountBlack() != -1);
}


// TreeNode methods

template<typename T>
bool RBTree<T>::TreeNode::isTwoNode() const
{
  return not red
     and (left == nullptr or not left->red)
     and (right == nullptr or not right->red);
}

template<typename T>
bool RBTree<T>::TreeNode::isFourNode() const
{
  return not red
     and left != nullptr and left->red
     and right != nullptr and right->red;
}

template<typename T>
int RBTree<T>::TreeNode::validateAndCountBlack() const
{
  int leftCt = 0, rightCt = 0;

  if (left != nullptr)
  {
    if (left->parent != this
        or (red and left->red)
        or left->datum > datum)
      return -1;
    leftCt = left->validateAndCountBlack();
  }

  if (right != nullptr)
  {
    if (right->parent != this
       or (red and right->red)
       or datum > right->datum)
      return -1;
    rightCt = right->validateAndCountBlack();
  }

  if (leftCt != rightCt)
    return -1;
  if (leftCt == -1 or rightCt == -1)
    return -1;
  
  return leftCt + (red? 0 : 1);
}



#endif
