
public class RBTreeBST<T extends Comparable<T>> {

  TreeNode data;
  int count;

  public RBTreeBST() {
    this (null, 0);
  }
  RBTreeBST(TreeNode data, int count) {
    this.data = data;
    this.count = count;
  }


  public boolean contains (T item) { return contains (data, item); }
  public void add (T item) {
    if (data == null)
      data = new TreeNode(item, null);
    else
      addBelow (data, item);

    ++count;
  }
  public boolean remove (T item) {
    if (count == 1 && data.datum.equals(item)) { //special: rm only item
      data = null;
      count = 0;
      return true;
    }
    else {
      boolean removed = remove (data, item);
      if (removed)
        --count;
      return removed;
    }
  }

  public int size() { return count; }


  public boolean isValidRBTree() {
    return data == null
        || (! data.red
            && data.validateAndCountBlack() != -1);
  }


  class TreeNode {
    boolean red;
    T datum;
    TreeNode left = null;
    TreeNode right = null;
    TreeNode parent;

    TreeNode (T datum, TreeNode parent, boolean red) {
      this.red = red;
      this.datum = datum;
      this.parent = parent;
    }
    TreeNode (T datum, TreeNode parent) {
      this(datum, parent, true);
    }

    TreeNode next() {
      if (right == null)
        return right;

      TreeNode retval = right;
      while (retval.left != null)
        retval = retval.left;

      return retval;
    }

    /** Returns num black edges from here to leaf, or -1 if not valid RB*/
    int validateAndCountBlack() {
      int leftCt = 0, rightCt = 0;

      if (left != null)
      {
        if (left.parent != this
            || (red && left.red)
            || left.datum.compareTo(datum) > 0)
          return -1;
        leftCt = left.validateAndCountBlack();
      }

      if (right != null)
      {
        if (right.parent != this
            || (red && right.red)
            || datum.compareTo(right.datum) > 0)
          return -1;
        rightCt = right.validateAndCountBlack();
      }

      if (leftCt != rightCt)
        return -1;
      if (leftCt == -1 || rightCt == -1)
        return -1;

      return leftCt + (red? 0 : 1);
    }
  } // end class TreeNode

  boolean contains (TreeNode root, T item) {
    if (root == null)
      return false;
    else if (root.datum.equals(item))
      return true;
    else if (item.compareTo(root.datum) < 0)
      return contains(root.left, item);
    else // root.datum < item
      return contains(root.right, item);
  }

  void addBelow (TreeNode root, T item) {
    assert (root != null);

    if (item.compareTo(root.datum) < 0) {
      if (root.left == null)
        root.left = new TreeNode(item, root);
      else
        addBelow (root.left, item);
    }
    else { // root.datum <= item
      if (root.right == null)
        root.right = new TreeNode(item, root);
      else
        addBelow (root.right, item);
    }
  }

  boolean remove (TreeNode root, T item) {
    //System.err.printf ("remove item %s from\n", item);
    //TreeDump.toStream (root, System.err);
    
    if (root == null)
      return false;
    else if (root.datum.equals(item))
    {
      removeItemIn(root);
      return true;
    }
    else if (item.compareTo(root.datum) < 0)
      return remove(root.left, item);
    else // (root.datum < item)
      return remove(root.right, item);
  }

  void removeItemIn (TreeNode node)
  {
    assert (node != null);
    //System.err.printf ("remove item in\n");
    //TreeDump.toStream (node, System.err);

    if (node.left != null && node.right != null) {
      TreeNode next = node.next();  // guaranteed to have null on left
      T tmp = node.datum;
      node.datum = next.datum;
      next.datum = tmp;
      removeItemIn(next);
    }
    else  { // leaf or has one child
      assert (node.parent != null); // already handled as special case

      if (node.left == null) { // leaf or has right child
        replaceParentsChild(node, node.right);
        replaceNodesParent(node.right, node.parent);
      }
      else { // node.right == null
        replaceParentsChild(node, node.left);
        replaceNodesParent(node.left, node.parent);
      }
    }
  }

  void replaceParentsChild (TreeNode node, TreeNode child)
  {
    if (node.parent.left == node)
      node.parent.left = child;
    else {
      assert (node.parent.right == node);
      node.parent.right = child;
    }
  }

  void replaceNodesParent (TreeNode node, TreeNode parent) {
    if (node != null)
      node.parent = parent;
  }

}
