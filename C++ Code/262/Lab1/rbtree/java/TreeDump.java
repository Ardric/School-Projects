import java.io.PrintStream;
import java.util.ArrayList;

class TreeDump {
  static String toString (RBTree<?> tree) {
    return toString(tree.data);
  }
  static void toStream (RBTree<?> tree, PrintStream stream) {
    stream.print (toString(tree.data));
  }
  static String toString (RBTree<?>.TreeNode root) {
    return toStringRep(root).flatten();
  }
  static void toStream (RBTree<?>.TreeNode root, PrintStream stream) {
    stream.print (toString(root));
  }

  private static class StringRep {
    int midpoint;
    ArrayList<StringBuilder> grid;
    int width;

    StringRep() {
      this.midpoint = 0;
      this.grid = new ArrayList<StringBuilder>();
      this.width = 0;
    }
    StringRep(int midpoint, ArrayList<StringBuilder> grid) {
      this.midpoint = midpoint;
      this.grid = grid;
      this.width = grid.get(0).length();
    }
    StringRep(String s) {
      this.grid = new ArrayList<StringBuilder>();
      this.grid.add(new StringBuilder(s));
      this.width = s.length();
      this.midpoint = (this.width - 1)/2;
    }

    String flatten() {
      StringBuilder retval = new StringBuilder("\n");
      for (StringBuilder row : this.grid)
        retval.append(row).append('\n');
      return retval.toString();
    }
  }

  static StringRep toStringRep(RBTree<?>.TreeNode root) {
    if (root == null)
      return new StringRep();
    else {
      String label = root.datum.toString();

      if (root.left == null && root.right == null)
        return new StringRep(label);

      StringBuilder labelLine = new StringBuilder(label);

      int labelmid = (labelLine.length() - 1)/2;


      StringRep left = toStringRep(root.left);
      StringRep right = toStringRep(root.right);
      ArrayList<StringBuilder> result = zip(left, right);

      int leftmid = left.midpoint;
      int rightmid = right.midpoint + left.width + 1;
      int gridmid = (leftmid + rightmid)/2;

      if (labelmid < gridmid) {
        padLeft(labelLine, gridmid - labelmid);
        labelmid = gridmid;
      }
      else if (labelmid > gridmid) {
        int offset = labelmid - gridmid;
        padLeft(result, offset);
        leftmid += offset;
        gridmid += offset;
        rightmid += offset;
      }

      int labelright = labelLine.length();
      int gridright = result.get(2).length();  // first "real" line
      if (labelright < gridright) {
        padRight(labelLine, gridright - labelright);
        labelright = gridright;
      }
      else if (labelright > gridright) {
        padRight(result, labelright - gridright);
        gridright = labelright;
      }

      StringBuilder treebranch;

      boolean lred = root.left != null && root.left.red;
      boolean rred = root.right != null && root.right.red;
      
      if (root.left != null && root.right != null) {
        treebranch = dupchar(leftmid, ' ')
          .append(lred?"#":"+")
                .append(dupchar(gridmid - leftmid - 1, (lred?'=':'-')))
          .append("+")
          .append(dupchar(rightmid - gridmid - 1 , (rred?'=':'-')))
                .append(rred?"#":"+")
          .append(dupchar(gridright - rightmid - 1, ' '));
      }
      else if (root.left == null) {
        treebranch = dupchar(gridmid, ' ')
          .append("+")
          .append(dupchar(rightmid - gridmid - 1 , (rred?'=':'-')))
                 .append(rred?"#":"+")
          .append(dupchar(gridright - rightmid - 1, ' '));
      }
      else {
        assert (root.right == null);
        treebranch = dupchar(leftmid, ' ')
          .append(lred?"#":"+")
                .append(dupchar(gridmid - leftmid - 1, (lred?'=':'-')))
          .append("+")
          .append(dupchar(gridright - gridmid - 1, ' '));
      }

      result.set(0, labelLine);
      result.set(1, treebranch);

      return new StringRep(gridmid, result);
    }
  }

  static StringBuilder dupchar (int n, char ch) {
    StringBuilder ret = new StringBuilder();
    for (int i = 0; i < n; ++i)
      ret.append(ch);
    return ret;
  }

  /* note: destroys data in its first argument */
  static ArrayList<StringBuilder> zip (StringRep left, StringRep right) {
    ArrayList<StringBuilder> result = new ArrayList<>();
    result.add(null); // for label
    result.add(null); // for treebranch
    int i;
    for (i = 0; i < Math.min(left.grid.size(), right.grid.size()); ++i)
      result.add(left.grid.get(i).append(' ').append(right.grid.get(i)));

    if (left.grid.size() < right.grid.size())
      for (; i < right.grid.size(); ++i)
        result.add(dupchar(left.width + 1, ' ').append(right.grid.get(i)));
    else if (left.grid.size() > right.grid.size())
      for (; i < left.grid.size(); ++i)
        result.add(left.grid.get(i).append(dupchar(right.width + 1, ' ')));

    return result;
  }

  static void padLeft (StringBuilder data, int width)
  {
    data.insert(0, dupchar(width, ' '));
  }

  static void padLeft (ArrayList<StringBuilder> data, int width)
  {
    for (StringBuilder line : data)
      if (line != null)
        padLeft(line, width);
  }

  static void padRight (StringBuilder data, int width)
  {
    data.append(dupchar(width, ' '));
  }

  static void padRight (ArrayList<StringBuilder> data, int width)
  {
    for (StringBuilder line : data)
      if (line != null)
        padRight(line, width);
  }

}
