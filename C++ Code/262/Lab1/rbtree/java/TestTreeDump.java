import org.junit.*;
import static org.junit.Assert.*;

public class TestTreeDump {

  @Test
    public void testLeaf() {
      RBTree<String> oneString = new RBTree<String>();
      oneString.add("baz");
      assertEquals("\nbaz\n", TreeDump.toString(oneString));
    }
  @Test
    public void testBalanced() {
      RBTree<Character> RBT = new RBTree<Character>();
      RBTree<Character>.TreeNode sevenChars = RBT.new TreeNode('h', null, false);
      sevenChars.left = RBT.new TreeNode('d', sevenChars, false);
      sevenChars.right = RBT.new TreeNode('l', sevenChars, false);
      sevenChars.left.left = RBT.new TreeNode('b', sevenChars.left, false);
      sevenChars.left.right = RBT.new TreeNode('f', sevenChars.left, false);
      sevenChars.right.left = RBT.new TreeNode('j', sevenChars.right, false);
      sevenChars.right.right = RBT.new TreeNode('n', sevenChars.right, false);
      String result = "\n"+
                "   h   \n"+
                " +-+-+ \n"+
                " d   l \n"+
                "+++ +++\n"+
                "b f j n\n";
      assertEquals(result, TreeDump.toString(sevenChars));
    }
  @Test
    public void testLeft() {
      RBTree<Integer> RBT = new RBTree<Integer>();
      RBTree<Integer>.TreeNode tree = RBT.new TreeNode(4, null, false);
      tree.left = RBT.new TreeNode(3, tree, false);
      tree.left.left = RBT.new TreeNode(2, tree.left, false);
      tree.left.left.left = RBT.new TreeNode(1, tree.left.left, false);

      String result =  "\n"+
                "   4\n"+
                "  ++\n"+
                "  3 \n"+
                " ++ \n"+
                " 2  \n"+
                "++  \n"+
                "1   \n";
      assertEquals(result, TreeDump.toString(tree));
    }
  @Test
    public void testRight() {
      RBTree<Integer> RBT = new RBTree<Integer>();
      RBTree<Integer>.TreeNode tree = RBT.new TreeNode(1, null, false);
      tree.right = RBT.new TreeNode(2, tree, false);
      tree.right.right = RBT.new TreeNode(3, tree.right, false);
      tree.right.right.right = RBT.new TreeNode(4, tree.right.right, false);

      String result =  "\n"+
                "1   \n"+
                "++  \n"+
                " 2  \n"+
                " ++ \n"+
                "  3 \n"+
                "  ++\n"+
                "   4\n";
      assertEquals(result, TreeDump.toString(tree));
    }
  @Test
    public void testWideroot() {
      RBTree<String> RBT = new RBTree<String>();
      RBTree<String>.TreeNode tree = RBT.new TreeNode("wide String", null, false);
      tree.left = RBT.new TreeNode("a", tree, false);
      tree.right = RBT.new TreeNode("z", tree, false);

      String result = "\n"+
                "wide String\n"+
                "    +++    \n"+
                "    a z    \n";
      assertEquals(result, TreeDump.toString(tree));
    }
  @Test
    public void testWideleft() {
      RBTree<String> RBT = new RBTree<String>();
      RBTree<String>.TreeNode tree = RBT.new TreeNode("y", null, false);
      tree.left = RBT.new TreeNode("wide String", tree, false);
      tree.right = RBT.new TreeNode("z", tree, false);

      String result = "\n"+
                "        y    \n"+
                "     +--+---+\n"+
                "wide String z\n";
      assertEquals(result, TreeDump.toString(tree));
    }
  @Test
    public void testWideright() {
      RBTree<String> RBT = new RBTree<String>();
      RBTree<String>.TreeNode tree = RBT.new TreeNode("b", null, false);
      tree.left = RBT.new TreeNode("a", tree, false);
      tree.right = RBT.new TreeNode("wide String", tree, false);

      String result = "\n"+
                "   b         \n"+
                "+--+---+     \n"+
                "a wide String\n";
      assertEquals(result, TreeDump.toString(tree));
    }
  @Test
    public void testMixed() {
      RBTree<String> RBT = new RBTree<String>();
      RBTree<String>.TreeNode tree = RBT.new TreeNode("ghi", null, false);
      tree.left = RBT.new TreeNode("abc", tree, false);
      tree.right = RBT.new TreeNode("nopqr", tree, false);
      tree.right.left = RBT.new TreeNode("k", tree.right, false);
      tree.right.right = RBT.new TreeNode("xyz", tree.right, false);
      tree.right.left.left = RBT.new TreeNode("jkl", tree.right.left, false);
      tree.right.left.right = RBT.new TreeNode("lm", tree.right.left, false);

      String result = "\n"+
                "    ghi       \n"+
                " +---+---+    \n"+
                "abc    nopqr  \n"+
                "      +--+--+ \n"+
                "      k    xyz\n"+
                "     ++-+     \n"+
                "    jkl lm    \n";
      assertEquals(result, TreeDump.toString(tree));
    }
  @Test
    public void testMixedRB() {
      RBTree<String> RBT = new RBTree<String>();
      RBTree<String>.TreeNode tree = RBT.new TreeNode("ghi", null, false);
      tree.left = RBT.new TreeNode("abc", tree, false);
      tree.right = RBT.new TreeNode("nopqr", tree, true);
      tree.right.left = RBT.new TreeNode("k", tree.right, false);
      tree.right.right = RBT.new TreeNode("xyz", tree.right, false);
      tree.right.left.left = RBT.new TreeNode("jkl", tree.right.left, true);
      tree.right.left.right = RBT.new TreeNode("lm", tree.right.left, true);
      /* In 234 form:
       *       (ghi      nopqr)
       *     /        |         \
       * (abc)    (jkl k lm)   (xyz)
       * */

      String result = "\n"+
                "    ghi       \n"+
                " +---+===#    \n"+
                "abc    nopqr  \n"+
                "      +--+--+ \n"+
                "      k    xyz\n"+
                "     #+=#     \n"+
                "    jkl lm    \n";
      assertEquals(result, TreeDump.toString(tree));
    }
}
