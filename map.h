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

private:
    Node<T, T1> *root;
};

template<typename T, typename T1>
void Map<T, T1>::insert(T value, T1 key) {
    Node newElem = Node(value, key);

    if (root = nullptr){
        root = newElem;
        newElem.parent = nullptr;
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

    // fixTree();

}

#ifndef LABORATORYWORK_2_MAP_H
#define LABORATORYWORK_2_MAP_H

#endif //LABORATORYWORK_2_MAP_H
