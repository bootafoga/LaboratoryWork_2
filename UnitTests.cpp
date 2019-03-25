//
// Created by Мария on 27.02.2019.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "List.h"
#include "map.h"
using testing::Eq;

namespace {
    class ClassDeclaration: public testing::Test, public Map<int,int>
            {
    public:
        //initialization of object that will be used in test
        Map<int, int> lst;

        ClassDeclaration(){
            lst;
        }
    };
}

TEST_F(ClassDeclaration, insert_checkKeys){
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);

    MapNode<int, int> root = lst.getRootCopy();

    //check keys
    ASSERT_EQ(root.key, 13);
    ASSERT_EQ(root.left->key, 8);
    ASSERT_EQ(root.right->key, 17);
}

TEST_F(ClassDeclaration, insert_checkValues){
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);

    MapNode<int, int> root = lst.getRootCopy();

    //check values
    ASSERT_EQ(root.value, 1);
    ASSERT_EQ(root.left->value, 2);
    ASSERT_EQ(root.right->value, 3);
}

TEST_F(ClassDeclaration, insert_checkColors){
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);

    MapNode<int, int> root = lst.getRootCopy();

    //check colors
    ASSERT_EQ(root.color, 0);
    ASSERT_EQ(root.left->color, 1);
    ASSERT_EQ(root.right->color, 1);
}


TEST_F(ClassDeclaration, insert_checkLinks){
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);

    MapNode<int, int> root = lst.getRootCopy();

    //check that these are all nodes of tree
    ASSERT_EQ(root.left->left, nullptr);
    ASSERT_EQ(root.left->right, nullptr);
    ASSERT_EQ(root.right->left, nullptr);
    ASSERT_EQ(root.right->right, nullptr);
}


TEST_F(ClassDeclaration, remove_checkKeys){
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);

    lst.remove(13);
    MapNode<int, int> root = lst.getRootCopy();

    //check keys
    ASSERT_EQ(root.key, 17);
    ASSERT_EQ(root.left->key, 8);
}

TEST_F(ClassDeclaration, remove_checkValues){
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);

    lst.remove(13);
    MapNode<int, int> root = lst.getRootCopy();

    //check values
    ASSERT_EQ(root.value, 3);
}

TEST_F(ClassDeclaration, remove_checkColors){
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);

    lst.remove(13);
    MapNode<int, int> root = lst.getRootCopy();

    //check colors
    ASSERT_EQ(root.color, 0);
    ASSERT_EQ(root.left->color, 1);
}

TEST_F(ClassDeclaration, remove_checkLinks){
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);

    lst.remove(13);
    MapNode<int, int> root = lst.getRootCopy();

    //check that these are all nodes of tree
    ASSERT_EQ(root.right, nullptr);
    ASSERT_EQ(root.left->left, nullptr);
    ASSERT_EQ(root.left->right, nullptr);
}

TEST_F(ClassDeclaration, remove_checkException){
    try {
        lst.insert(13, 1);
        lst.insert(8, 2);
        lst.insert(17, 3);

        lst.remove(1);
    }
    catch (exception& ex) {
        EXPECT_STREQ("Item with this key not found", ex.what());
    }
}

TEST_F(ClassDeclaration, find){
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);

    MapNode<int, int> root = lst.getRootCopy();
    MapNode<int, int> *forFind = lst.find(8);
    //check that founded node is eq
    ASSERT_EQ(forFind, root.left);
}

TEST_F(ClassDeclaration, find_checkException){
    try {
        lst.insert(13, 1);
        lst.insert(8, 2);
        lst.insert(17, 3);

        lst.find(1);
    }
    catch (exception& ex) {
        EXPECT_STREQ("Item with this key not found", ex.what());
    }
}

TEST_F(ClassDeclaration, clear_onInt){
    lst.insert(13, 1);
    lst.insert(8, 2);
    lst.insert(17, 3);

    MapNode<int, int> root = lst.getRootCopy();
    ASSERT_EQ(lst.getSize() != 0, 1);
    lst.clear();
    ASSERT_EQ(lst.getSize() == 0, 1);
}

TEST_F(ClassDeclaration, getKeys_onInt){
    lst.insert(1, 4);
    lst.insert(2, 5);
    lst.insert(3, 6);

    List<int> listOfKeys = lst.get_keys();

    for (int i = 1; i < 4; i++){
        ASSERT_EQ(i, listOfKeys.At(i-1));
    }
    ASSERT_EQ(3, listOfKeys.getSize());
}

TEST_F(ClassDeclaration, getValues_onInt){
    lst.insert(1, 4);
    lst.insert(2, 5);
    lst.insert(3, 6);

    List<int> listOfValues = lst.get_values();

    for (int i = 1; i < 4; i++){
        ASSERT_EQ(i+3, listOfValues.At(i-1));
    }
    ASSERT_EQ(3, listOfValues.getSize());
}
