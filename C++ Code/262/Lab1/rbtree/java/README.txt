RBTree
CMSC 262 Project 1
Fall 2015 (Blaheta)


This is an incomplete implementation of red-black trees.  The overall
red-black tree itself is implemented in RBTree.java; the underlying
tree will be linked objects of the inner class RBTree.TreeNode.  For
convenient debugging and testing purposes, a number of tree-printing
methods are also given, and to avoid confusing the main issue, they're
given as static methods of a TreeDump class (implemented in
TreeDump.java).  RBTree requires that any contained object must be
Comparable (so that the tree can maintain its order).

There is also an RBTreeBST.java file that implements a class RBTreeBST
with the same public interface but which does nothing but the pure,
naïve binary search tree implementation (no rotations).  This can be
useful as a point of comparison, because it still correctly implements
the set ADT (add, remove, contains) but will fail at tests that check
for balance.


There are three runnable programs used for testing the implementation.


TestTreeDump.java is used to test that my tree printing code works correctly.

To compile:
  javac -cp '/usr/share/java/junit-4.11.jar:.' TestTreeDump.java
To then run the test:
  jtest TestTreeDump

You should not have to modify these tests, or indeed to modify TreeDump
itself, for this project.  However, the test cases themselves serve as
useful documentation of what TreeDump does.



TestRBTree.java is used to test that the red-black tree implementation:
 - correctly observes the contract for set operations add, contains, and
   remove
 - correctly performs certain rotations when various add or remove
   operations are performed
 - correctly preserves the red-black conditions after each operation.

To compile:
  javac -cp '/usr/share/java/junit-4.11.jar:.' TestRBTree.java
To then run the test:
  jtest TestRBTree

Some of these tests currently fail.  Others don't actually test
anything yet.



SpeedTest.java empirically observes how long certain operations take on
randomly-generated list of numbers---first in its original random order,
and then after it is sorted into ascending order.  

To compile:
  javac SpeedTest.java
To run:
  java SpeedTest

Running this on a fully-implemented red-black tree should produce
noticeably different results from running it on a naïve BST.



The compile command given for the first two includes a command-line
option to set the classpath to include the JUnit library.  If you
prefer, you can set your CLASSPATH variable to include that jar file (or
more generally, to include /usr/share/java/* and get various other
libraries that we've installed on the system) and then you can just
'javac TestRBTree.java' (same thing, mutatis mutandis, for the other
one).  The testing command, 'jtest', is a wrapper script that executes
the main method from JUnit's JUnitCore class together with whatever
tests you have written in the class you specify, to actually run the
tests.



The unit testing for TreeDump and for RBTree are in JUnit format, which
is the de facto standard unit testing library in the Java world.
Briefly, inside any class that you wish to serve as a test suite, you
can annotate methods as @Before, @After, or @Test to indicate
(respectively) code to run before every test (to set up a fixture),
after each test (to tear down the fixture), and to mark the tests
themselves.  Each test method can then include an arbitrary number of
JUnit assertions, of which the most important to us are

  assertTrue ( /* Java expr */ ); // for boolean exprs that should be true
  assertFalse ( /* Java expr */ ); // for boolean exprs that should be false
  assertEquals ( value, /* Java expr */ ); // for non-boolean exprs that
                                           // should eval to a specific value
  
A variety of documentation can be found at
  http://junit.org/
although it can be a little dense sometimes; if you run into trouble
feel free to ask me questions.
