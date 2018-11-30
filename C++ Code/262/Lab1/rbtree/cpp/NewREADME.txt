RBTree
CMSC 262 Project 1
Fall 2015 (Blaheta)  Daniel Lowdermilk

 // Compiling informoation at the top, details and proofs at the bottom.
 // Collaborated with Joshua Willis-Jones

test_TreeDump.u is used to test that my tree printing code works correctly.

To compile:
  compile test_TreeDump.u -o test_TreeDump
To then run the test:
  ./test_TreeDump


test_RBTree.u is used to test that the red-black tree implementation:
 - correctly observes the contract for set operations add, contains, and 
   remove.
 - correctly performs certain rotations when various add or remove
   operations are performed.
 - correctly preserves the red-black conditions after each operation.

To compile:
  compile test_RBTree.u -o test_RBTree
To then run the test:
  ./test_RBTree


speedtest.cpp empirically observes how long certain operations take on
randomly-generated list of numbers---irst in its original random order,
and then after it is sorted into ascending order. To change the tree you 
testing the speed of, you have to change what .h is included in the top of
the speedtest.cpp file.  Also, change the file name at the bottom to one of the
two current files that are holding the tree speed information depending on the tree 
you're testing.

To compile:
  compile speedtest.cpp -o speedtest
To run:
  ./speedtest

Running this on a fully-implemented red-black tree should produce
noticeably different results from running it on a naive BST.


Details:

Two seperated speedtest files. 
 - speedRBTree.txt has the speed of the fully implemented red-black tree.
 - speedBSTree.txt has the speed of the naive binary search tree.

Test cases added for the other three cases in maybeRotate are correct because they
are implemented and run without error.

The implementions and bug fix in case 3 and case 4 are correct because they match
how we said it was going to work in class and they are tested properly in test_RBTree.u
and do not fail.

Fixed the bugs in rotateThreeNodeRight.  It wasn't reassigning the nodes correctly when
rotating the tree making it out of order.  Changed the way the nodes were reassigned to 
put it in order and make the reassignments correct.

Implemented and tested removeRotate3, 4, and 5.  Runs tests cases without failure.

Added conditions to cases 4 and 5. Implemented them. Then ran test cases on all of them without
failure.

There is a test case named breakadd that will fail if the two lines in add are removed.

There is a test case named specialrootfusion that confirms the code works correctly.


