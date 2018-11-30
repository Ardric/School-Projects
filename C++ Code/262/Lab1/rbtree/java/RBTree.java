
public class RBTree<T extends Comparable<T>> {

  TreeNode data;
  int count;

  public RBTree() {
    this (null, 0);
  }
  RBTree(TreeNode data, int count) {
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
    if (data.parent != null)  // why is this if statement here?  what
      data = data.parent;     // happens if it is commented out?
    data.red = false; // special case for root
  }
  public boolean remove (T item) {
    if (count == 1 && data.datum.equals(item)) { //special: rm only item
      data = null;
      count = 0;
      return true;
    }
    else {
      if (count >= 3 && data.isTwoNode()
              && data.left.isTwoNode() && data.right.isTwoNode()) {
        // special root "fusion" case
        data.left.red = true;
        data.right.red = true;
      }

      boolean removed = remove (data, item);
      if (removed)
        --count;
      return removed;
    }
  }

  public int size() { return count; }


  public bool isValidRBTree() {  // should always be true!
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

    boolean isTwoNode() {
      return !red
          && (left == null || !left.red)
          && (right == null || !right.red);
    }

    boolean isFourNode() {
      return !red
          && left != null && left.red
          && right != null && right.red
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
    if (root.isFourNode())
      splitFour(root);

    if (item.compareTo(root.datum) < 0) {
      if (root.left = null) {
        root.left = new TreeNode(item, root);
        maybeRotate(root.left);
      }
      else 
        addBelow (root.left, item);
    }
    else { // root.datum <= item
      if (root.right == null) {
        root.right = new TreeNode(item, root);
        maybeRotate(root.right);
      }
      else
        addBelow (root.right, item);
    }
  }

  void splitFour (TreeNode node) {
    assert (node.isFourNode());

    node.left.red = false;
    node.right.red = false;
    node.red = true;
    maybeRotate(node);
  }
  
  void maybeRotate (TreeNode node) {
    assert (node != null);
    if (node.red && node.parent != null && node.parent.red) {
      //System.err.println("About to rotate:");
      //TreeDump.toStream(node.parent.parent, System.err);

      // inside an unbalanced 4-node, so rotate.  
      // First, get a handle on existing nodes that may move:
      TreeNode parent = node.parent;
      TreeNode grandparent = parent.parent;

      TreeNode B, D, F; // will point to node, parent, grandparent
      TreeNode c, e; // will point to middle children;

      if (node == parent.left && parent == grandparent.left) {
        // Case 1
        B = node;
        D = parent;
        F = grandparent;
        c = B.right;
        e = D.right;
      }
      else if (node == parent.right && parent == grandparent.right) {
        // Case 2
        B = grandparent;
        D = parent;
        F = node;
        c = D.left;
        e = F.left;
      }
      else if (node == parent.right && parent == grandparent.left) {
        // Case 3
        // XXX: currently buggy!
        B = node;
        D = parent;
        F = grandparent;
        c = D.left;
        e = D.right;
      }
      else { // node == parent.left && parent == grandparent.right
        // Case 4

        return; // replace with correct implementation
      }

      // Then, perform rotation:
      replaceParentsChild(grandparent, D); // root special, handled later
      D.parent = grandparent.parent;
      D.left = B;
      D.right = F;
      D.red = false;

      B.parent = D;
      B.right = c;
      B.red = true;

      F.parent = D;
      F.left = e;
      F.red = true;

      if (c != null)
        c.parent = B;
      if (e != null)
        e.parent = F;
    }
  }


  boolean remove (TreeNode root, T item) {
    if (root == null)
      return false;

    //System.err.printf ("remove item %s from\n", item);
    //TreeDump.toStream (root, System.err);
    
    guaranteeRedLeaf(root, (root.datum.compareTo(item) <= 0));
    
    if (root.datum.equals(item))
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
      TreeNode next = successor(node);  // guaranteed to have null on left
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

  void rotateThreeNodeLeft (TreeNode node) {
    TreeNode child = node.right;
    assert(! node.red);
    assert(child.red);

    TreeNode B = node;
    TreeNode D = child;
    TreeNode c = D.left;

    replaceParentsChild(B, D);
    D.parent = B.parent;
    D.left = B;
    D.red = false;

    B.parent = D;
    B.right = c;
    B.red = true;

    if (c != null)
      c.parent = B;
  }

  void rotateThreeNodeRight (TreeNode node) {
    // XXX: currently buggy!
    TreeNode child = node.left;
    assert (! node.red);
    assert (child.red);

    TreeNode B = child;
    TreeNode D = node;
    TreeNode c = B.left;

    replaceParentsChild(D, B);
    B.parent = D.parent;
    B.left = c;
    B.red = false;

    D.parent = B.parent;
    D.left = c;
    D.red = true;

    if (c != null)
      c.parent = D;
  }

  void guaranteeRedLeaf (TreeNode node, boolean seekRight) {
    assert (node != null);
    if (node.red)
      return;
    if (node.isFourNode())
      return;

    if (node.right != null && node.right.red) {
      if (seekRight)
        return;
      else
        rotateThreeNodeLeft (node);
    }
    else if (node.left != null && node.left.red) {
      if (seekRight)
        rotateThreeNodeRight(node);
      else
        return;
    }
    else {
      assert (node.isTwoNode());
      if (node.parent == null)            // 2-node root is special
        return;

      assert (node.parent.parent == null || node.parent.red);

      if (node.parent.left.isTwoNode()
          && node.parent.right.isTwoNode()) {
        // Case 1
        //borrow from parent to make 4-node
        assert (node.parent.red); // root fusion case handled elsewhere
        node.parent.red = false;
        node.parent.left.red = true;
        node.parent.right.red = true;
      }
      else if (node == node.parent.left
          && node.parent.right.left != null
          && node.parent.right.left.red) {
        // Case 2

      }
      else if (node == node.parent.left
          && node.parent.right.right != null
          && node.parent.right.right.red) {
        // Case 3
        // move sibling up, parent down
        TreeNode B = node;
        TreeNode D = node.parent;
        TreeNode F = node.parent.right;
        TreeNode H = node.parent.right.right;
        TreeNode e = F.left;

        replaceParentsChild(D, F);
        F.parent = D.parent;
        F.left = D;
        assert (F.right == H);
        F.red = D.red; // true unless D was root

        H.red = false;

        D.parent = F;
        assert (D.left == B);
        D.right = e;
        D.red = false;

        B.red = true;

        if (e != null)
          e.parent = D;
      }
      else if (false /* test for case 4 */) {
        // Case 4

      }
      else if (false /* test for case 5 */) {
        // Case 5

      }
      else {
        throw new RuntimeException("This case should be unreachable");
      }
    }
  }

  TreeNode successor(TreeNode node) {
    if (node.right == null)
      return null;

    TreeNode retval = node.right;
    guaranteeRedLeaf(retval, false);

    while (retval.left != null) {
      retval = retval.left;
      guaranteeRedLeaf(retval, false);
    }

    return retval;
  }

  void replaceParentsChild (TreeNode node, TreeNode child)
  {
    if (node.parent == null)
      return;

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
