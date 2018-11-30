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

    bool isValidRBTree() const;

  private:
    struct TreeNode
    {
      bool red;
      T datum;
      TreeNode* left;
      TreeNode* right;
      TreeNode* parent;

      TreeNode (T d, TreeNode* p)
        : red(false), datum(d), left(nullptr), right(nullptr), parent(p) { }

      TreeNode* next();
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

    static bool remove (TreeNode* root, const T& item);
    static void removeItemIn (TreeNode* root);
    static void replaceParentsChild (TreeNode* node, TreeNode* child);
    static void replaceNodesParent (TreeNode* node, TreeNode* child);


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
    branch = new TreeNode(item, parent);
  else
    addBelow (branch, item);
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
bool RBTree<T>::remove (TreeNode* root, const T& item)
{
  //cerr << "remove item " << item << " from" << endl;
  //TreeDump::toStream<T> (root, cerr);
  
  if (root == nullptr)
    return false;
  else if (root->datum == item)
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
    TreeNode* next = node->next();  // guaranteed to have null on left
    swap (node->datum, next->datum);
    removeItemIn(next);
  }
  else  // leaf or has one child
  {
    assert (node->parent != nullptr); // already handled as special case

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
bool RBTree<T>::isValidRBTree() const
{
  return data == nullptr
      or (not data->red
          and data->validateAndCountBlack() != -1);
}


// TreeNode methods
template<typename T>
typename RBTree<T>::TreeNode* RBTree<T>::TreeNode::next()
{
  if (right == nullptr)
    return right;

  TreeNode* retval = right;
  while (retval->left != nullptr)
    retval = retval->left;

  return retval;
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
