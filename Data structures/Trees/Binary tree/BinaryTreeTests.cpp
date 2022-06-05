#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../../includes/doctest.h"
#include "BinaryTree.h"

TEST_SUITE("Test binary tree node"){

    TEST_CASE("Test constructors"){

        SUBCASE("Default"){

            BinaryTreeNode<int> node;
            CHECK_EQ(node.value, 0);

        }

        SUBCASE("Parametric"){

            BinaryTreeNode<int> node(5);
            CHECK_EQ(node.value, 5);

        }

        SUBCASE("Copy"){

            BinaryTreeNode<int> node1(10);
            BinaryTreeNode<int> node2(node1);
            CHECK_EQ(node2.value, 10);

        }

    }

    TEST_CASE("Functions"){

        SUBCASE("Insert"){

            BinaryTreeNode<int> node(6);
            node.insert(10);
            node.insert(2);
            CHECK_EQ(node.left -> value, 2);
            CHECK_EQ(node.right -> value, 10);

        }

    }

}

TEST_SUITE("Test binary search tree class"){

    TEST_CASE("Test constructors"){

        SUBCASE("Default"){

            BinaryTree<int> tree;
            CHECK_EQ(tree.toString(), "0");

        }

        SUBCASE("Param"){

            BinaryTree<int> tree(5);
            CHECK_EQ(tree.toString(), "5");
            
        }

    }

    TEST_CASE("Test functions"){
        
        SUBCASE("Insert"){

            BinaryTree<int> tree(6);
            tree.insert(3);
            tree.insert(8);
            CHECK_EQ(tree.toString(), "3 6 8");

        }

        SUBCASE("SEARCH"){

            BinaryTree<int> tree(8);
            tree.insert(3);
            tree.insert(10);
            tree.insert(1);
            tree.insert(6);
            tree.insert(14);
            tree.insert(4);
            tree.insert(7);
            tree.insert(13);
            CHECK_EQ(tree.toString(), "1 3 4 6 7 8 10 13 14");
            CHECK_EQ(tree.search(13), true);
            CHECK_FALSE(tree.search(2));

        }

    }

}
