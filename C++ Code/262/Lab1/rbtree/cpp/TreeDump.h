/* This first include is intentionally outside the header guard; see
 * README for explanation. */
#include "RBTree.h"

#ifndef _TREEDUMP_H_
#define _TREEDUMP_H_

#include <iostream>
#include <sstream>
#include <deque>

using namespace std;

class TreeDump
{
  public:
    template <typename T>
    static string toString (const RBTree<T>& tree)
    {
      return toString<T>(tree.data);
    }
    template <typename T>
    static void toCout (const RBTree<T>& tree)
    {
      toStream (tree, cout);
    }
    template <typename T>
    static void toStream (const RBTree<T>& tree, ostream& out)
    {
      out << toString<T>(tree.data);
    }

    // note: these must be called with explicit type parameter, e.g.
    // TreeDump::toString<T>(tree.data)
    template <typename T>
    static string toString (const typename RBTree<T>::TreeNode* root)
    {
      return toStringRep<T>(root).flatten();
    }
    template <typename T>
    static void toCout (const typename RBTree<T>::TreeNode* root)
    {
      toStream<T> (root, cout);
    }
    template <typename T>
    static void toStream (const typename RBTree<T>::TreeNode* root, ostream& out)
    {
      out << toString<T>(root);
    }

  private:
    struct StringRep
    {
      int midpoint;
      deque<string> grid;
      int width;

      StringRep()
        : midpoint(0), grid(), width(0) { }
      StringRep(int m, const deque<string>& g) 
        : midpoint(m), grid(g), width(g[0].length()) { }
      StringRep(string s)
      {
        grid.push_back(s);
        width = s.length();
        midpoint = (width - 1)/2;
      }

      string flatten() const;
    };

    static deque<string> zip (const StringRep& left,
                                  const StringRep& right);
    static void padLeft (string& data, int width);
    static void padLeft (deque<string>& data, int width);
    static void padRight (string& data, int width);
    static void padRight (deque<string>& data, int width);

    template <typename T>
    static StringRep toStringRep(const typename RBTree<T>::TreeNode* root);
};

string TreeDump::StringRep::flatten() const
{
  string retval = "\n";
  for (string row : grid)
    retval += row + '\n';
  return retval;
}

deque<string> TreeDump::zip (const StringRep& left,
                                        const StringRep& right)
{
  deque<string> result;
  unsigned int i;
  for (i = 0; i < min(left.grid.size(), right.grid.size()); ++i)
    result.push_back(left.grid[i] + " " + right.grid[i]);

  if (left.grid.size() < right.grid.size())
    for (; i < right.grid.size(); ++i)
      result.push_back(string(left.width + 1, ' ') + right.grid[i]);
  else if (left.grid.size() > right.grid.size())
    for (; i < left.grid.size(); ++i)
      result.push_back(left.grid[i] + string(right.width + 1, ' '));

  return result;
}

void TreeDump::padLeft (string& data, int width)
{
  data = string(width, ' ') + data;
}

void TreeDump::padLeft (deque<string>& data, int width)
{
  for (string& line : data)
  {
    padLeft(line, width);
  }
}

void TreeDump::padRight (string& data, int width)
{
  data += string(width, ' ');
}

void TreeDump::padRight (deque<string>& data, int width)
{
  for (string& line : data)
  {
    padRight(line, width);
  }
}

template <typename T>
TreeDump::StringRep TreeDump::toStringRep(const typename RBTree<T>::TreeNode* root)
{
  if (root == nullptr)
    return StringRep();
  else
  {
    ostringstream line;
    line << root->datum;
    string label = line.str();

    if (root->left == nullptr and root->right == nullptr)
      return StringRep(label);

    int labelmid = (label.length() - 1)/2;


    StringRep left = toStringRep<T>(root->left);
    StringRep right = toStringRep<T>(root->right);
    deque<string> result = zip(left, right);

    int leftmid = left.midpoint;
    int rightmid = right.midpoint + left.width + 1;
    int gridmid = (leftmid + rightmid)/2;

    if (labelmid < gridmid)
    {
      padLeft(label, gridmid - labelmid);
      labelmid = gridmid;
    }
    else if (labelmid > gridmid)
    {
      int offset = labelmid - gridmid;
      padLeft(result, offset);
      leftmid += offset;
      gridmid += offset;
      rightmid += offset;
    }

    int labelright = label.length();
    int gridright = result[0].length();
    if (labelright < gridright)
    {
      padRight(label, gridright - labelright);
      labelright = gridright;
    }
    else if (labelright > gridright)
    {
      padRight(result, labelright - gridright);
      gridright = labelright;
    }

    string treebranch;

    /*
    cerr << label << endl;
    cerr << leftmid << endl;
    cerr << gridmid << endl;
    cerr << rightmid << endl;
    cerr << gridright << endl;
    */

    bool lred = root->left != nullptr and root->left->red;
    bool rred = root->right != nullptr and root->right->red;
    
    if (root->left != nullptr and root->right != nullptr)
    {
      treebranch = 
        string(leftmid, ' ')
        + (lred?"#":"+") + string(gridmid - leftmid - 1, (lred?'=':'-'))
        + "+"
        + string(rightmid - gridmid - 1 , (rred?'=':'-')) + (rred?"#":"+")
        + string(gridright - rightmid - 1, ' ');
    }
    else if (root->left == nullptr)
    {
      treebranch =
        string(gridmid, ' ')
        + "+"
        + string(rightmid - gridmid - 1 , (rred?'=':'-')) + (rred?"#":"+")
        + string(gridright - rightmid - 1, ' ');
    }
    else if (root->right == nullptr)
    {
      treebranch =
        string(leftmid, ' ')
        + (lred?"#":"+") + string(gridmid - leftmid - 1, (lred?'=':'-'))
        + "+"
        + string(gridright - gridmid - 1, ' ');
    }

    result.push_front(treebranch);
    result.push_front(label);

    return StringRep(gridmid, result);
  }
}

#endif
