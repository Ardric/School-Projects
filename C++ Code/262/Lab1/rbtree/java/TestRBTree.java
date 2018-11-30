import org.junit.*;
import static org.junit.Assert.*;

public class TestRBTree {
  RBTree<String> empty;
  RBTree<Integer> oneInt;
  RBTree<String> threeStrings;
  RBTree<Character> sevenChars;
  RBTree<Integer> case2;

  @Before
    public void setUp() {
      empty = new RBTree<String>();

      oneInt = new RBTree<Integer>();
      oneInt.add(3);

      threeStrings = new RBTree<String>();
      threeStrings.add("def");
      threeStrings.add("ghi");
      threeStrings.add("abc");

      sevenChars = new RBTree<Character>();
      sevenChars.add('h'); //root
      sevenChars.add('d'); //first row
      sevenChars.add('l');
      sevenChars.add('b'); //second row
      sevenChars.add('f');
      sevenChars.add('j');
      sevenChars.add('n');

      case2 = new RBTree<Integer>();
      case2.add(15);
      case2.add(18);
      case2.add(6);
      case2.add(3);
      case2.add(12);
      case2.add(9);

    }

  /* TESTING BST CORRECTNESS (black-box) */

  @Test
    public void testContainsEmpty() {
      assertFalse (empty.contains("foo"));
    }

  @Test
    public void testAddContainsRoot() {
      assertTrue (oneInt.contains(3));
      assertTrue (threeStrings.contains("def"));
    }

  @Test
    public void testAddContainsLeaf() {
      assertTrue (threeStrings.contains("abc"));
      assertTrue (threeStrings.contains("ghi"));
      assertTrue (sevenChars.contains('b'));
      assertTrue (sevenChars.contains('n'));
    }

  @Test
    public void testSize() {
      assertEquals (0, empty.size());
      assertEquals (1, oneInt.size());
      assertEquals (7, sevenChars.size());
    }

  @Test
    public void testAddContainsInternal() {
      assertTrue (sevenChars.contains('d'));
      assertTrue (sevenChars.contains('l'));
    }

  @Test
    public void testAddContainsFalse() {
      assertFalse (oneInt.contains(2));
      assertFalse (threeStrings.contains("xyz"));
      assertFalse (sevenChars.contains('e'));
    }

  @Test
    public void testRemoveFail() {
      assertFalse (empty.remove("foo"));
      assertEquals (0, empty.size());
      assertFalse (sevenChars.remove('e'));
      assertEquals (7, sevenChars.size());
    }

  @Test
    public void testRemoveLeafLeft() {
      assertTrue (threeStrings.remove("abc"));
      assertTrue (threeStrings.contains("def"));
      assertFalse (threeStrings.contains("abc"));
      assertTrue (sevenChars.remove('b'));
      assertTrue (sevenChars.contains('d'));
      assertFalse (sevenChars.contains('b'));
    }

  @Test
    public void testRemoveLeafRight() {
      // prep work: add tests here to verify that remove works
      // on right leaf nodes.  Use removeLeafLeft as a model.

    }

  @Test
    public void testRemoveInternalLeft() {
      assertTrue (sevenChars.remove('d'));
      assertTrue (sevenChars.contains('h'));
      assertFalse (sevenChars.contains('d'));
      assertTrue (sevenChars.contains('b'));
      assertTrue (sevenChars.contains('f'));
    }

  @Test
    public void testRemoveInternalRight() {
      assertTrue (sevenChars.remove('l'));
      assertTrue (sevenChars.contains('h'));
      assertFalse (sevenChars.contains('l'));
      assertTrue (sevenChars.contains('j'));
      assertTrue (sevenChars.contains('n'));
    }

  @Test
    public void testRemoveRoot() {
      assertTrue (threeStrings.remove("def"));
      assertFalse (threeStrings.contains("def"));
      assertTrue (threeStrings.contains("abc"));
      assertTrue (threeStrings.contains("ghi"));
      assertTrue (sevenChars.remove('h'));
      assertFalse (sevenChars.contains('h'));
      assertTrue (sevenChars.contains('d'));
      assertTrue (sevenChars.contains('l'));
      assertTrue (sevenChars.contains('f'));
      assertTrue (sevenChars.contains('j'));
    }

  @Test
    public void testRemoveOnly() {
      assertTrue (oneInt.remove(3));
      assertFalse (oneInt.contains(3));
      assertEquals (0, oneInt.size());
    }

  @Test
    public void testRemoveSize() {
      sevenChars.remove('h');
      assertEquals (6, sevenChars.size());
      sevenChars.remove('f');
      assertEquals (5, sevenChars.size());
      threeStrings.remove("abc");
      assertEquals (2, threeStrings.size());
    }

    /* TESTING BALANCE CORRECTNESS (white-box) */

  @Test
    public void testAddMakeThreeRight() {
      oneInt.add(4);
      String result = "\n"+
                "3 \n"+
                "+#\n"+
                " 4\n";
      assertEquals (result, TreeDump.toString(oneInt));
      assertTrue (oneInt.isValidRBTree());
    }

  @Test
    public void testAddMakeThreeLeft() {
      oneInt.add(2);
      String result = "\n"+
                " 3\n"+
                "#+\n"+
                "2 \n";
      assertEquals (result, TreeDump.toString(oneInt));
      assertTrue (oneInt.isValidRBTree());
    }

  @Test
    public void testAddSplit4() {
      threeStrings.add("jkl");
      String result = "\n"+
                "  def   \n"+
                " +-+-+  \n"+
                "abc ghi \n"+
                "     +# \n"+
                "     jkl\n";
      assertEquals (result, TreeDump.toString(threeStrings));
      assertTrue (threeStrings.isValidRBTree());
    }

  @Test
    public void testAddRotateCase1() {

    }

  @Test
    public void testAddRotateCase2() {
      threeStrings.add("jkl");
      threeStrings.add("mno");
      String result = "\n"+
                "   def     \n"+
                " +--+--+   \n"+
                "abc   jkl  \n"+
                "     #=+=# \n"+
                "    ghi mno\n";
      assertEquals (result, TreeDump.toString(threeStrings));
      assertTrue (threeStrings.isValidRBTree());
    }

  @Test
    public void testAddRotateCase3() {

    }

  @Test
    public void testAddRotateCase4() {

    }

  @Test
    public void testAddPropagate() {
      sevenChars.add('i');
      String result = "\n"+
                "   h    \n"+
                " +-+==# \n"+
                " d    l \n"+
                "#+#  +++\n"+
                "b f  j n\n"+
                "    #+  \n"+
                "    i   \n";
      assertEquals (result, TreeDump.toString(sevenChars));
      assertTrue (oneInt.isValidRBTree());
    }

  @Test
    public void testAddSplitRotate() {
      sevenChars.add('m');
      sevenChars.add('e');
      sevenChars.add('p');
      sevenChars.add('o');
      sevenChars.add('q');
      String result = "\n"+
                "   h        \n"+
                " +-+--+     \n"+
                " d    l     \n"+
                "++-+ ++=#   \n"+
                "b  f j  n   \n"+
                "  #+   ++-+ \n"+
                "  e    m  p \n"+
                "         #+#\n"+
                "         o q\n";
      assertEquals (result, TreeDump.toString(sevenChars));

      sevenChars.add('r');

      String result2 = "\n"+
                "    h        \n"+
                " +--+---+    \n"+
                " d      n    \n"+
                "++-+  #=+=#  \n"+
                "b  f  l   p  \n"+
                "  #+ +++ +++ \n"+
                "  e  j m o q \n"+
                "           +#\n"+
                "            r\n";
      assertEquals (result2, TreeDump.toString(sevenChars));
      assertTrue (sevenChars.isValidRBTree());
    }

  @Test
    public void testRemoveRotateThreeLeft() {
      RBTree<Integer> tree = new RBTree<Integer>();
      tree.add(4);
      tree.add(2);
      tree.add(6);
      tree.add(8);

      String result = "\n"+
                " 4  \n"+
                "+++ \n"+
                "2 6 \n"+
                "  +#\n"+
                "   8\n";
      assertEquals (result, TreeDump.toString(tree));

      tree.remove(5);

      String result2 = "\n"+
                " 4  \n"+
                "++-+\n"+
                "2  8\n"+
                "  #+\n"+
                "  6 \n";
      assertEquals (result2, TreeDump.toString(tree));
      assertTrue (tree.isValidRBTree());
    }

  @Test
    public void testRemoveRotateThreeRight() {
      RBTree<Integer> tree = new RBTree<Integer>();
      tree.add(4);
      tree.add(2);
      tree.add(8);
      tree.add(6);

      String result = "\n"+
                " 4  \n"+
                "++-+\n"+
                "2  8\n"+
                "  #+\n"+
                "  6 \n";
      assertEquals (result, TreeDump.toString(tree));

      tree.remove(9);

      String result2 = "\n"+
                " 4  \n"+
                "+++ \n"+
                "2 6 \n"+
                "  +#\n"+
                "   8\n";
      assertEquals (result2, TreeDump.toString(tree));
      assertTrue (tree.isValidRBTree());
    }

  @Test
    public void testRemoveRotateCase1() {
      // case 1 doesn't arise except after removals, so:
      case2.remove(9);
      RBTree<Integer> case1 = case2;

      String result = "\n"+
                "   15  \n"+
                " #=+-+ \n"+
                " 6   18\n"+
                "+++    \n"+
                "3 12   \n";
      assertEquals (result, TreeDump.toString(case1));

      case1.remove(2);

      String result2 = "\n"+
                "   15  \n"+
                " +-+-+ \n"+
                " 6   18\n"+
                "#+#    \n"+
                "3 12   \n";
      assertEquals (result2, TreeDump.toString(case1));
      assertTrue (case1.isValidRBTree());
    }

  @Test
    public void testRemoveRotateCase2() {
      String result = "\n"+
                "   15   \n"+
                " #=+--+ \n"+
                " 6    18\n"+
                "++-+    \n"+
                "3  12   \n"+
                "  #+    \n"+
                "  9     \n";
      assertEquals (result, TreeDump.toString(case2));

      case2.remove(2);

      String result2 = "\n"+
                "    15  \n"+
                "  #=+-+ \n"+
                "  9   18\n"+
                " +++    \n"+
                " 6 12   \n"+
                "#+      \n"+
                "3       \n";
      assertEquals (result2, TreeDump.toString(case2));
      assertTrue (case2.isValidRBTree());
    }

  @Test
    public void testRemoveRotateCase3() {

    }

  @Test
    public void testRemoveRotateCase4() {

    }

  @Test
    public void testRemoveRotateCase5() {

    }


    /* TESTING RB CORRECTNESS (black-box) */

  @Test
    public void testAddValid() {
      assertTrue (empty.isValidRBTree());
      assertTrue (oneInt.isValidRBTree());
      assertTrue (threeStrings.isValidRBTree());
      assertTrue (sevenChars.isValidRBTree());
    }

  @Test
    public void testNoRemoveValid() {
      assertFalse (empty.remove("foo"));
      assertFalse (sevenChars.remove('e'));
      assertTrue (empty.isValidRBTree());
      assertTrue (sevenChars.isValidRBTree());
    }

  @Test
    public void testRemoveLeafLeftValid() {
      assertTrue (threeStrings.remove("abc"));
      assertTrue (threeStrings.isValidRBTree());
      assertTrue (sevenChars.remove('b'));
      assertTrue (sevenChars.isValidRBTree());
    }

  @Test
    public void testRemoveLeafRightValid() {
      assertTrue (threeStrings.remove("ghi"));
      assertTrue (threeStrings.isValidRBTree());
      assertTrue (sevenChars.remove('n'));
      assertTrue (sevenChars.isValidRBTree());
    }

  @Test
    public void testRemoveInternalLeftValid() {
      assertTrue (sevenChars.remove('d'));
      assertTrue (sevenChars.isValidRBTree());
    }
  @Test
    public void testRemoveInternalRightValid() {
      assertTrue (sevenChars.remove('l'));
      assertTrue (sevenChars.isValidRBTree());
    }

  @Test
    public void testRemoveRootValid() {
      assertTrue (threeStrings.remove("def"));
      assertTrue (threeStrings.isValidRBTree());
      assertTrue (sevenChars.remove('h'));
      assertTrue (sevenChars.isValidRBTree());
      assertTrue (oneInt.remove(3));
      assertTrue (oneInt.isValidRBTree());
    }

  @Test
    public void testRemoveMystery() { 
      // what is this testing? why does it fail?
      assertFalse (case2.remove(16));
      assertTrue (case2.contains(3));
      assertTrue (case2.contains(6));
      assertTrue (case2.contains(9));
      assertTrue (case2.contains(12));
      assertTrue (case2.contains(15));
      assertTrue (case2.contains(18));
    }

}
