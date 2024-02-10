
/**
 * @file GenericTreeExercises.h
 * University of Illinois CS 400, MOOC 2, Week 3: Generic Tree
 * Spring 2019
 *                       STUDENT STARTER FILE
 *
 * @author Eric Huber - University of Illinois staff
 *
**/

/********************************************************************
  NOTE: There are 2 exercises in this file! Please complete them
  both and test your work before handing this file in on Coursera.
  You can jump to the functions that need editing by searching for
  "TODO", but ideally, you should read through this entire code file
  for background information and hints.
 ********************************************************************/

// Prevent the header from being included more than once per cpp file
#pragma once

// It's good to put system headers first, so that if your own libraries
// cause conflicts, the compiler will most likely identify the problem
// as being in your own source code files, where it arises later.
#include <iostream>
#include <string>

// This is the provided GenericTree class. You can study the header file
// liner notes for additional tips and information about the assignment.
#include "GenericTree.h"

/**
 * @file GenericTreeExercises.h
 * University of Illinois CS 400, MOOC 2, Week 3: Generic Tree
 * Spring 2019
 *                       STUDENT STARTER FILE
 *
 * @author Eric Huber - University of Illinois staff
 *
**/

/********************************************************************
  NOTE: There are 2 exercises in this file! Please complete them
  both and test your work before handing this file in on Coursera.
  You can jump to the functions that need editing by searching for
  "TODO", but ideally, you should read through this entire code file
  for background information and hints.
 ********************************************************************/

// It's good to put system headers first, so that if your own libraries
// cause conflicts, the compiler will most likely identify the problem
// as being in your own source code files, where it arises later.
#include <iostream>
#include <string>
#include <vector>
#include <stack>

// This is the provided GenericTree class. You can study the header file
// liner notes for additional tips and information about the assignment.
#include "GenericTree.h"

/*******************************************************************
  EXERCISE 1: Populate a tree by completing the treeFactory function.
  
  Here is a generic tree that stores ints, that is, an instance of
  GenericTree<int>:

  4
  |
  |_ 8
  |  |
  |  |_ 16
  |  |  |
  |  |  |_ 42
  |  |
  |  |_ 23
  |
  |_ 15

  This is how a GenericTree is printed to standard output in the
  terminal. The root is 4, which has two children: a left child, 8,
  and a right child, 15. 8 has a left child that is 16, and a right
  child that is 23. 16 has a single child that is 42.

  (Recall that for the sake of our terminal printing, "leftmost"
   children are printed first, at the top, and "rightmost" children
   are printed last, at the bottom.)

  You should try to build this tree as a GenericTree<int> in the
  treeFactory function. We'll help you get started below. You can study
  the other provided source files for hints, especially GenericTree.h,
  main.cpp, and this file, and the terminal output you see should resemble
  the diagram shown above.

  ****************************************************************/

// treeFactory: A GenericTree<int> is passed as input by reference, and this
// function populates it with contents according to the specification given
// above. If the tree passed in already has some contents then they should be
// properly destroyed first. There is no need to return a value because the
// tree is edited in-place by reference.
static void treeFactory(GenericTree<int>& tree) {
  tree.clear(); // Clear the existing contents of the tree

  auto rootNode = tree.getRootPtr(); // Get a pointer to the root node of the tree

  // If the root node is null, create a new root node
  if (!rootNode) {
    rootNode = tree.createRoot(4); // Set the root node value to 4
  }

  // Add nodes and children according to the specified structure
  auto node8 = rootNode->addChild(8); // Add child 8 to the root node
  auto node15 = rootNode->addChild(15); // Add child 15 to the root node
  auto node16 = node8->addChild(16); // Add child 16 to node8
  auto node23 = node8->addChild(23); // Add child 23 to node8
  auto node42 = node16->addChild(42); // Add child 42 to node16
}

// treeFactoryTest: This function demonstrates the execution of treeFactory
// and displays a preview of the results in the main function.
// (You do NOT need to edit this function.)
static void treeFactoryTest() {
  std::cout << std::endl;
  std::cout << "------------------------------" << std::endl;
  std::cout << "EXERCISE 1: treeFactoryTest" << std::endl;
  std::cout << "The output should match what you see in the code comments" << std::endl << std::endl;

  GenericTree<int> tree(9999);
  treeFactory(tree);
  std::cout << tree << std::endl;
}

/*******************************************************************
    The second exercise is found at the bottom of this file.
    Please read through for some background discussion.
  ****************************************************************/

// -------------------------------------------------------------------
// Breadth-first vs. Depth-first Search Strategies
// -------------------------------------------------------------------

// In the lecture about tree traversal, the professor made a distinction
// between traversal and search: Traversal aims to walk an entire tree,
// while search is meant to find a specific node. There is a certain
// relationship between the depth-first search strategy and the first
// types of traversal order that the professor discussed: Pre-, in-, and
// post-order reporting during traversal can all be accomplished with a
// very similar implementation strategy to depth-first search. That is,
// the goal is to descend entirely down one branch of the tree before
// descending another. This search strategy is easy to implement recursively,
// but you can also manage to do it iteratively using stack data structures.
// You can see some examples of this in the source code provided with this
// assignment.

// The level-order traversal strategy is related to breadth-first search,
// in that it attempts to finish work on an entire layer of the tree before
// working on the next layer. In contrast with the other methods, it is
// somewhat more natural to implement with a queue. However, it's possible
// to use a combination of data structures, iteration, and recursion to
// achieve certain walks through the tree in certain orders.

// -------------------------------------------------------------------
// Recursive vs. Iterative Design
// -------------------------------------------------------------------

// As a warm up, below is an example of how to implement the same essential
// function two different ways. Both of the countNullChildren functions
// intend to count the number of nodes in a subtree that have null pointers
// taking up space. Sometimes the recursive method is naturally suited to a
// certain problem and produces an elegant solution. However, you do need to
// be careful about memory usage in that case; There is more discussion about
// that in GenericTree.h in the commentary on GenericTree<T>::deleteSubtree.

// Since GenericTree has a vector of subchildren for each node, where each
// node can have many children, it seems natural that you would want to be
// able to iterate over the children nodes, even if you take a recursive
// approach to solving a problem. It's okay to combine recursive and
// iterative techniques in that way. It's also possible to convert
// recursive solutions into iterative ones entirely. Usually that just means
// using a data structure to keep track of what work still needs to be done;
// for example, you could use a queue or stack of node pointers that still
// remain to be explored. Then you would loop over the set of remaining work
// until no work is left to do.

// -------------------------------------------------------------------

// countNullChildrenRecursive: Given a pointer to a TreeNode, look at the
// subtree that is implicitly rooted at that node, and count how many children
// throughout the tree are null pointers. Here, templated type N should be a
// TreeNode inner type belonging to some type of GenericTree.
// (You do NOT need to edit this function.)
template <typename N>
int countNullChildrenRecursive(N* subtreeRoot) {
  if (!subtreeRoot) return 1;

  int nullChildrenSum = 0;
  for (auto childPtr : subtreeRoot->childrenPtrs) {
    nullChildrenSum += countNullChildrenRecursive(childPtr);
  }

  return nullChildrenSum;
}

// countNullChildrenIterative: Given a pointer to a TreeNode, look at the
// subtree that is implicitly rooted at that node, and count how many children
// throughout the tree are null pointers. Here, templated type N should be a
// TreeNode inner type belonging to some type of GenericTree.
// (You do NOT need to edit this function.)
template <typename N>
int countNullChildrenIterative(N* subtreeRoot) {

  int nullChildrenSum = 0;
  std::stack<N*> nodesToExplore;
  nodesToExplore.push(subtreeRoot);

  while (!nodesToExplore.empty()) {
    N* topNode = nodesToExplore.top();
    nodesToExplore.pop();

    if (!topNode) {
      nullChildrenSum++;
      continue;
    }

    for (auto childPtr : topNode->childrenPtrs) {
      nodesToExplore.push(childPtr);
    }
  }

  return nullChildrenSum;
}

/*******************************************************************
  EXERCISE 2: Implement level-order traversal in the traverseLevels function.

  As discussed above, a level-order traversal is related to the idea of a
  breadth-first traversal. You need to implement the traverseLevels function,
  which takes a tree as input and performs a level-order traversal. Traverse
  the tree one layer at a time, visiting child nodes from left to right, while
  storing copies of the node data in level order as a std::vector. If a null
  child pointer is encountered, no data item should be appended to the results
  for that one pointer. The function should return the std::vector of result
  data in the appropriate order.

  You may implement the body of the function however you want, but you must
  not leak any memory or crash, and your function should work for any
  simple instance of GenericTree<T> (such as GenericTree<int> or
  GenericTree<std::string>). You'll find several good strategies for building
  the function throughout the source files provided with this assignment.

  ****************************************************************/

// traverseLevels: Performs a level-order traversal of the input tree
// and records copies of the data found, in order, in a std::vector,
// which should then be returned.
template <typename T>
std::vector<T> traverseLevels(GenericTree<T>& tree) {

  using TreeNode = typename GenericTree<T>::TreeNode;
  std::vector<T> results;

  auto rootNodePtr = tree.getRootPtr();
  if (!rootNodePtr) return results;

  std::queue<TreeNode*> nodesToExplore;
  nodesToExplore.push(rootNodePtr);

  while (!nodesToExplore.empty()) {
    TreeNode* currentNode = nodesToExplore.front();
    nodesToExplore.pop();
    
    if (currentNode) {
      results.push_back(currentNode->data);
      for (auto childPtr : currentNode->childrenPtrs) {
        nodesToExplore.push(childPtr);
      }
    }
  }

  return results;
}

// traversalTest: Runs some tests with your traverseLevels function and
// displays comparison output. (You do NOT need to edit this function.)
static void traversalTest() {
  std::cout << std::endl;
  std::cout << "------------------------------" << std::endl;
  std::cout << "EXERCISE 2: traversalTest" << std::endl;
  std::cout << "Testing your traverseLevels function" << std::endl  << std::endl;

  {
    // This is the tree from exampleTree1() in main.cpp
    std::cout << "[Test 1] Expected output:" << std::endl
      << "A B E C D F G" << std::endl;
    GenericTree<std::string> tree1("A");
    auto nodeA = tree1.getRootPtr();
    auto nodeB = nodeA->addChild("B");
    nodeB->addChild("C");
    nodeB->addChild("D");
    auto nodeE = nodeA->addChild("E");
    nodeE->addChild("F");
    nodeE->addChild("G");
    std::vector<std::string> tree1_results = traverseLevels(tree1);
    std::cout << "Your traverseLevels output:" << std::endl;
    for (auto result : tree1_results) {
      std::cout << result << " ";
    }
    std::cout << std::endl << std::endl;
  }
  
  {
    // This is the tree from exampleTree2() in main.cpp
    std::cout << "[Test 2] Expected output:" << std::endl
      << "A B D J K C E I L F G M H" << std::endl;
    GenericTree<std::string> tree2("A");
    auto A = tree2.getRootPtr();
    A->addChild("B")->addChild("C");
    auto D = A->addChild("D");
    auto E = D->addChild("E");
    E->addChild("F");
    E->addChild("G")->addChild("H");
    D->addChild("I");
    A->addChild("J");
    auto L = A->addChild("K")->addChild("L");
    L->addChild("M");
    std::vector<std::string> tree2_results = traverseLevels(tree2);
    std::cout << "Your traverseLevels output:" << std::endl;
    for (auto result : tree2_results) {
      std::cout << result << " ";
    }
    std::cout << std::endl << std::endl;
  }

  {
    // This is the tree you should have built for the first part of this
    // assignment above, with treeFactory.
    std::cout << "[Test 3] Expected output:" << std::endl
      << "4 8 15 16 23 42" << std::endl;
    GenericTree<int> tree3(9999);
    treeFactory(tree3);
    std::vector<int> tree3_results = traverseLevels(tree3);
    std::cout << "Your traverseLevels output:" << std::endl;
    for (auto result : tree3_results) {
      std::cout << result << " ";
    }
    std::cout << std::endl << std::endl;
  }

}
