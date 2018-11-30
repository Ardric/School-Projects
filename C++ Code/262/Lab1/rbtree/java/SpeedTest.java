import java.util.*;

public class SpeedTest {
  static final int ITERS = 10000;

  public static void main (String[] args) {
    Random rand = new Random();

    long[] check = new long[6];

    ArrayList<Integer> nums = new ArrayList<>();

    // Substitute RBTree or RBTreeBST
    RBTreeBST<Integer> randorder = new RBTreeBST<>();
    RBTreeBST<Integer> inorder = new RBTreeBST<>();

    for (int i = 0; i < ITERS; ++i)
      nums.add(rand.nextInt());

    check[0] = System.nanoTime();

    for (int i = 0; i < ITERS; ++i)
      randorder.add(nums.get(i));

    check[1] = System.nanoTime();

    for (int i = 0; i < ITERS; ++i)
      randorder.contains(rand.nextInt());

    check[2] = System.nanoTime();

    Collections.sort (nums);

    check[3] = System.nanoTime();

    for (int i = 0; i < ITERS; ++i)
      inorder.add(nums.get(i));

    check[4] = System.nanoTime();

    for (int i = 0; i < ITERS; ++i)
      inorder.contains(rand.nextInt());

    check[5] = System.nanoTime();

    System.out.printf("Avg add (random): %dns\n", (check[1]-check[0])/ITERS);
    System.out.printf("Avg search (random): %dns\n", (check[2]-check[1])/ITERS);
    System.out.printf("Avg add (order): %dns\n", (check[4]-check[3])/ITERS);
    System.out.printf("Avg search (order): %dns\n", (check[5]-check[4])/ITERS);


  }
}
