RBTree
CMSC 262 Project 1
Fall 2015 (Blaheta)


This is an incomplete implementation of red-black trees.  The overall
red-black tree itself is implemented in RBTree.h; the underlying tree
will be linked objects of the inner class RBTree::TreeNode.  For
convenient debugging and testing purposes, a number of tree-printing
methods are also given, and to avoid confusing the main issue, they're
given as static methods of a TreeDump class (implemented in TreeDump.h).
Because of TreeDump, RBTree requires that any contained object must have
a working overload of the stream output operator << (as well as the
comparison operators < and == required for ordering the tree).

There is also an RBTree-BST.h file that implements a class that is still
called "RBTree" but which does nothing but the pure, naïve binary search
tree implementation (no rotations).  This can be useful as a point of
comparison, because it still correctly implements the set ADT (add,
remove, contains) but will fail at tests that check for balance.


There are three runnable programs used for testing the implementation.


test_TreeDump.u is used to test that my tree printing code works correctly.

To compile:
  compile test_TreeDump.u -o test_TreeDump
To then run the test:
  ./test_TreeDump

You should not have to modify these tests, or indeed to modify TreeDump
itself, for this project.  However, the test cases themselves serve as
useful documentation of what TreeDump does.



test_RBTree.u is used to test that the red-black tree implementation:
 - correctly observes the contract for set operations add, contains, and
   remove
 - correctly performs certain rotations when various add or remove
   operations are performed
 - correctly preserves the red-black conditions after each operation.

To compile:
  compile test_RBTree.u -o test_RBTree
To then run the test:
  ./test_RBTree

Some of these tests currently fail.  Others don't actually test
anything yet.



speedtest.cpp empirically observes how long certain operations take on
randomly-generated list of numbers---first in its original random order,
and then after it is sorted into ascending order.  

To compile:
  compile speedtest.cpp -o speedtest
To run:
  ./speedtest

Running this on a fully-implemented red-black tree should produce
noticeably different results from running it on a naïve BST.




The #include structure in the .h files is a little unusual: TreeDump.h
includes RBTree outside its header guard, and RBTree.h includes TreeDump
in the middle of the file.  This is intentional.  It forces the
following load order: RBTree declarations and class header; then full
definition of TreeDump; then RBTree method definitions, regardless of
which of the two is included first.  Importantly, this means that all of
the declarations precede all of the definitions.  See
  http://stackoverflow.com/questions/11394063/fixing-order-of-inclusion-when-there-is-circular-dependency-in-c-template-clas
and
  http://stackoverflow.com/questions/3353831/resolving-a-circular-dependency-between-template-classes
for more explanation of the problem and this solution to it.



You may notice that the command to compile is simply 'compile' rather
than 'g++' (or perhaps 'clang++').  It is using g++ behind the scenes,
but it runs it using an updated C++11 standard, prepares the output for
debugging, and limits the output to the first error message---none of
which are done by default if you just type 'g++'.  It also handles .u
files (see next paragraph).



The unit testing for TreeDump and for RBTree are in .u files, which are
written for a testing library called 'Unci' that I wrote as a wrapper
for cppunit, which has a confusing and clunky interface.  I aim for it
to be largely self-documenting, but the short version is that every .u
file should start with #include statements, contain a "test suite"
instead of a class, and inside the test suite have a "fixture", which
sets up the data values that will be standard starting points for every
test, and then "tests", which are a series of individual test cases that
each test a different unit of the code.  Inside a test case is a mix of
arbitrary C++ code and check/expect statements: an expression to check
the value of, and an expectation as to what it should evaluate to.
There are three types of check/expects that are relevant to you:

  check ( /* C++ expr */ ) expect true; // for bool exprs that should be true
  check ( /* C++ expr */ ) expect false; // for bool exprs that should be false
  check ( /* C++ expr */ ) expect == value; // for non-boolean exprs that
                                            // should eval to a specific value

There is, at the moment, not a lot of documentation for Unci (such is
the peril of writing your own library), but if you run into trouble I
can answer your questions.  You can also look at the labs where I rolled
it out to my 162 class last fall:
  http://cs.longwood.edu/courses/cmsc162/f14/lab02.pdf
  http://cs.longwood.edu/courses/cmsc162/f14/lab03.pdf

Answer to 4:  I believe it is making string representations of the trees we input. It should look along the lines of what's below.
     R
  +---=#
  Q    T
     +---+
     S   U
