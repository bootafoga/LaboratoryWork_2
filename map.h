//
// Created by Мария on 27.02.2019.
//

#include <iostream>
using namespace std;

template <typename T, typename T1>
class Node {
public:
    Node(){
        this->key = (T)nullptr;
        this->value = (T1)nullptr;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        color = true;
    }
    Node(T key, T1 value){
        this->key = key;
        this->value = value;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        color = true;
    }

    ~Node(){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }


    T key;
    T1 value;
    bool color;     //if 0 it's black, if 1 it's red
    Node *left;
    Node *right;
    Node *parent;
};

template <typename T, typename T1>
class Map {
public:

    Map(){
        root = nullptr;
    }

    void leftRotation(Node<T,T1> *elemX);
    void rightRotation(Node<T,T1> *elemX);
    void fixTreeAfterInsert(Node<T,T1> *currentElem);
    void insert(T key, T1 value);
    void fixTreeAfterDelete(Node<T,T1> *elem);

    Node<T, T1>* find(T key);

    ///////////////////////////////

    void remove(T key);
    void clear();
    void get_keys();
    void get_values();
    void show(Node<T, T1> *current, int level);

    void Showw(Node<T, T1> *current, int level);


    void print();

    Node<T, T1> *root;
private:
    //Node<T, T1> *root;
};



template<typename T, typename T1>
void Map<T, T1>::leftRotation(Node<T, T1> *elemX) {


    Node<T, T1> *elemY = elemX->right;

    elemX->right = elemY->left;
    if (elemY->left != nullptr) elemY->left->parent = elemX;


    if (elemY != nullptr) elemY->parent = elemX->parent;
    if (elemX->parent) {
        if (elemX == elemX->parent->left)
            elemX->parent->left = elemY;
        else
            elemX->parent->right = elemY;
    } else {
        root = elemY;
    }


    elemY->left = elemX;
    if (elemX != nullptr) elemX->parent = elemY;
}

template<typename T, typename T1>
void Map<T, T1>::rightRotation(Node<T, T1> *elemX) {


    Node<T, T1> *elemY = elemX->left;

    elemX->left = elemY->right;
    if (elemY->right != nullptr) elemY->right->parent = elemX;


    if (elemY != nullptr) elemY->parent = elemX->parent;
    if (elemX->parent) {
        if (elemX == elemX->parent->right)
            elemX->parent->right = elemY;
        else
            elemX->parent->left= elemY;
    } else {
        root = elemY;
    }


    elemY->right = elemX;
    if (elemX != nullptr) elemX->parent = elemY;
}

template<typename T, typename T1>
void Map<T, T1>::fixTreeAfterInsert(Node<T, T1> *currentElem){


    while (currentElem!= root && currentElem->parent->color){ // while parent red
        // if parent node is left son
        if (currentElem->parent->parent->left == currentElem->parent){
            Node<T, T1> *uncle = currentElem->parent->parent->right;
            if (uncle!= nullptr && uncle->color){ //uncle red
                currentElem->parent->color = false;
                uncle->color = false;
                currentElem->parent->parent->color = true;
                currentElem = currentElem->parent->parent;
            } else { //uncle black or don't exist
                if (currentElem == currentElem->parent->right){
                    currentElem = currentElem->parent;

                    leftRotation(currentElem);
                }

                currentElem->parent->color = false;
                currentElem->parent->parent->color = true;

                rightRotation(currentElem->parent->parent);
            }

        } else {

            Node<T, T1> *uncle = currentElem->parent->parent->left;
            if (uncle!= nullptr && uncle->color) { //uncle red
                currentElem->parent->color = false;
                uncle->color = false;
                currentElem->parent->parent->color = true;
                currentElem = currentElem->parent->parent;
            } else {
                if (currentElem == currentElem->parent->left){
                    currentElem = currentElem->parent;

                    rightRotation(currentElem);
                }

                currentElem->parent->color = false;
                currentElem->parent->parent->color = true;

                leftRotation(currentElem->parent->parent);

            }

        }
    }
    root->color = false;
}

template<typename T, typename T1>
void Map<T, T1>::insert(T key1, T1 value1) {


    Node<T, T1> *newElem = new Node<T, T1>(key1, value1);

    if (root == nullptr){
        root = newElem;
    } else {
        Node<T, T1> *current = root;
        Node<T, T1> *parent = nullptr;

        while (current!= nullptr){
            parent = current;
            current =  (current->key < newElem->key)? current->right : current->left;
        }

        // now we have found the place where new ell will be added

        newElem->parent = parent;
        newElem->color = true;

        if (parent->key < newElem->key)
            parent->right = newElem;
        else
            parent->left = newElem;
    }

    fixTreeAfterInsert(newElem);
}

/*
template<typename T, typename T1>
void Map<T, T1>::print() {

    Node<T, T1> *current = root;

    cout << current->key << endl;

    cout << current->left->key << " " << current->right->key << endl;
    cout << current->left->left->key << " " << current->left->right->key << " || " << current->right->left->key << " " << current->right->right->key << " " << endl;
   // cout << current->left->left->right->key;
}*/



template<typename T, typename T1>
void Map<T, T1>::remove(T key) {


    Node<T, T1> *deletedNode = find(key);


    if (deletedNode == nullptr) return;

    if (deletedNode->left == nullptr || deletedNode->right == nullptr) {
        Node<T, T1> *sonOfDeleted;

        if (deletedNode->left != nullptr) {

            sonOfDeleted = deletedNode->left;
        }
        else if (deletedNode->right != nullptr){

            sonOfDeleted = deletedNode->right;
        }


        if (deletedNode->parent){
            if ((deletedNode->left == nullptr) && (deletedNode->right == nullptr)) {


                if (deletedNode == deletedNode->parent->left)
                    deletedNode->parent->left = nullptr;
                else
                    deletedNode->parent->right = nullptr;


            } else {
                sonOfDeleted->parent = deletedNode->parent;

                if (deletedNode == deletedNode->parent->left)
                    deletedNode->parent->left = sonOfDeleted;
                else
                    deletedNode->parent->right = sonOfDeleted;

            }


        }
        else {

            root = sonOfDeleted;
        }


        if (!deletedNode->color) fixTreeAfterDelete (sonOfDeleted);
        delete deletedNode;

    } else {
        Node<T, T1> *temporaryNode = deletedNode->right;
        while (temporaryNode->left != nullptr) temporaryNode = temporaryNode->left;

        Node<T, T1> *sonOfTemporary;
        if (temporaryNode->right != nullptr) sonOfTemporary = temporaryNode->right;

        if (temporaryNode->parent){

            if ((temporaryNode->left == nullptr) && (temporaryNode->right == nullptr)) {


                if (temporaryNode == temporaryNode->parent->left)
                    temporaryNode->parent->left = nullptr;
                else
                    temporaryNode->parent->right = nullptr;


            } else {
                sonOfTemporary->parent = temporaryNode->parent;

                if (temporaryNode == temporaryNode->parent->left)
                    temporaryNode->parent->left = sonOfTemporary;
                else
                    temporaryNode->parent->right = sonOfTemporary;

            }

        }
        else
            root = sonOfTemporary;

        deletedNode->value = temporaryNode->value;
        deletedNode->key = temporaryNode->key;
        if (!temporaryNode->color) fixTreeAfterDelete (sonOfTemporary);

        delete temporaryNode;
    }

}

template<typename T, typename T1>
Node<T, T1> *Map<T, T1>::find(T key) {
    Node<T, T1> *current = root;

    while (current != nullptr){
        if (current->key == key){
            return current;
        }
        else {
            current =  (current->key < key)? current->right : current->left;
        }
    }

    return nullptr;
}


/////////////////



template<typename T, typename T1>
void Map<T, T1>::fixTreeAfterDelete(Node<T, T1> *currentNode) {
    while (currentNode != root && !currentNode->color) {
        if (currentNode == currentNode->parent->left) {
            Node<T, T1> *brotherOfCurrent = currentNode->parent->right;
            if (brotherOfCurrent->color) {
                brotherOfCurrent->color = false;
                currentNode->parent->color = true;
                leftRotation(currentNode->parent);
                brotherOfCurrent = currentNode->parent->right;
            }
            if (!brotherOfCurrent->left->color && !brotherOfCurrent->right->color) {
                brotherOfCurrent->color = true;
                currentNode = currentNode->parent;
            } else {
                if (!brotherOfCurrent->right->color) {
                    brotherOfCurrent->left->color = false;
                    brotherOfCurrent->color = false;
                    rightRotation(brotherOfCurrent);
                    brotherOfCurrent = currentNode->parent->right;
                }
                brotherOfCurrent->color = currentNode->parent->color;
                currentNode->parent->color = false;
                brotherOfCurrent->right->color = false;
                leftRotation(currentNode->parent);
                currentNode = root;
            }
        } else {
            Node<T, T1> *brotherOfCurrent =  currentNode->parent->left;
            if (brotherOfCurrent->color) {
                brotherOfCurrent->color = false;
                currentNode->parent->color = true;
                rightRotation(currentNode->parent);
                brotherOfCurrent = currentNode->parent->left;
            }
            if (!brotherOfCurrent->right->color && !brotherOfCurrent->left->color) {
                brotherOfCurrent->color = true;
                currentNode = currentNode->parent;
            } else {
                if (!brotherOfCurrent->left->color) {
                    brotherOfCurrent->right->color = false;
                    brotherOfCurrent->color = true;
                    leftRotation(brotherOfCurrent);
                    brotherOfCurrent = currentNode->parent->left;
                }
                brotherOfCurrent->color = currentNode->parent->color;
                currentNode->parent->color = false;
                brotherOfCurrent->left->color = false;
                rightRotation(currentNode->parent);
                currentNode = root;
            }
        }
    }
    currentNode->color = false;
}



template<typename T, typename T1>
void Map<T, T1>::Showw(Node<T, T1> *node, int level) {
    if (node) {
        Showw(node->left,level+1);
        for(int i = 0;i< 3*level;i++) cout << " ";
         cout << node->key << "[" << node->color << "]" << endl;
        Showw(node->right,level+1);

    }
}

#ifndef LABORATORYWORK_2_MAP_H
#define LABORATORYWORK_2_MAP_H

#endif //LABORATORYWORK_2_MAP_H
