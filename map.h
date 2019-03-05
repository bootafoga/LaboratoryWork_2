//
// Created by Мария on 27.02.2019.
//


template <typename T, typename T1>
class Node {
public:
    Node(T value, T1 key){
        this->value = value;
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->color = true;
    }

    ~Node(){
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }

private:
    T value;
    T1 key;
    bool color;     //if 0 it's black, if 1 it's red
    Node *left;
    Node *right;
    Node *parent;
};

template <typename T, typename T1>
class Map {
public:
    void insert(T value, T1 key);
    void remove(T1 key);
    Node<T, T1>* find(T1 key);
    void clear();
    void get_keys();
    void get_values();
    void leftRotation(Node<T,T1> *elem);
    void rightRotation(Node<T,T1> *elem);
    void fixTree(Node<T,T1> *elem);

private:
    Node<T, T1> *root;
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
void Map<T, T1>::fixTree(Node<T, T1> *currentElem){

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

                rotateLeft(currentElem->parent->parent);

            }

        }
    }

    root->color = false;
}

template<typename T, typename T1>
void Map<T, T1>::insert(T value, T1 key) {
    Node<T, T1> *newElem = Node(value, key);

    if (root = nullptr){
        root = newElem;
       // newElem.parent = nullptr;
    } else {
        Node<T, T1> *current = root;
        Node<T, T1> *parent = nullptr;

        while (current!= nullptr){
            parent = current;
            current =  (current->key < newElem->key)? current->right : current->left;
        }

        // now we have found the place where new ell will be added

        newElem.parent = parent;
        newElem.color = true;

        if (parent->key < newElem->key)
            parent->right = newElem;
        else
            parent->left = newElem;
    }

    fixTree(newElem);

}




#ifndef LABORATORYWORK_2_MAP_H
#define LABORATORYWORK_2_MAP_H

#endif //LABORATORYWORK_2_MAP_H
