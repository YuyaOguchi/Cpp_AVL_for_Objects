#pragma once
#include <cstdlib>    // Provides size_t
#include "bintree.h"  // Provides binary_tree_node<Item> template class
#include <algorithm>
using namespace std;

    template <typename Item>
    class binary_tree
    {
    public:
        // CONSTRUCTORS and DESTRUCTOR
        binary_tree( );
        binary_tree(const binary_tree& source);
        binary_tree(const Item& entry);
        ~binary_tree( );

        // AVL rotates
        binary_tree_node<Item>* rotateRight(binary_tree_node<Item> *y);
        binary_tree_node<Item>* rotateLeft(binary_tree_node<Item> *x);
        //AVL other
        int height(binary_tree_node<Item> *N);
        void insert(Item& object);
        // MODIFICATION MEMBER FUNCTIONS
        void create_first_node(const Item& entry);
        void shift_to_root( );
        void shift_up( );
        void shift_left( );
        void shift_right( );
        void change(const Item& new_entry);
        void add(const Item& entry);
        // CONSTANT MEMBER FUNCTIONS
        std::size_t size( ) const;
        Item retrieve( ) const;
        bool has_parent( ) const;
        bool has_left_child( ) const;
        bool has_right_child( ) const;
    //private:
        binary_tree_node<Item>* insert(binary_tree_node<Item>*node, Item& object);
        binary_tree_node<Item> *root;
        binary_tree_node<Item> *current;
        int nodecounter;
    };


    template <typename Item>
    binary_tree<Item>::binary_tree( ){ //initial state
        root = NULL;
        current = NULL;
        nodecounter = 0;
    }

    template <typename Item>
    binary_tree<Item>::binary_tree(const binary_tree<Item>& source){ //copy the trees
        root = tree_copy(source.root);
        current = root;
        nodecounter = source.nodecounter;
    }

    template <typename Item>
    binary_tree<Item>::binary_tree(const Item& entry) {
        nodecounter = 0;
        create_first_node(entry);
    }

    template <typename Item>
    binary_tree<Item>::~binary_tree( ){ //deconstructor
        tree_clear(root);
    }

    //rotate the node and its child to right
    template <typename Item>
    binary_tree_node<Item>* binary_tree<Item>::rotateRight(binary_tree_node<Item> *y){

        binary_tree_node<Item> *x = y->left();
        binary_tree_node<Item> *T2 = x->right();

        x->set_right(y);
        y->set_left(T2);
        y->set_height(max(height(y->left()), height(y->right()))+1);
        x->set_height(max(height(x->left()), height(x->right()))+1);
        return x;
    }

    //rotate the node and its child to left
    template <typename Item>
    binary_tree_node<Item>* binary_tree<Item>::rotateLeft(binary_tree_node<Item> *x){
        binary_tree_node<Item> *y = x->right();
        binary_tree_node<Item> *T2 = y->left();

        y->set_left(x);
        x->set_right(T2);

        x->set_height(max(height(x->left()), height(x->right()))+1);
        y->set_height(max(height(y->left()), height(y->right()))+1);

        return y;
    }

    //get height
    template <typename Item>
    int binary_tree<Item>::height(binary_tree_node<Item> *N){
        if (N == NULL)
            return 0;
        return N->getHeight();
    }

    //insert the function
    template <typename Item>
    void binary_tree<Item>::insert(Item& object){
        root = insert(root, object);
        nodecounter++;
    }

    //recursive call to insert at the right location
    template <typename Item>
    binary_tree_node<Item>* binary_tree<Item>::insert(binary_tree_node<Item>*node, Item& object){
        if (node == NULL)
            return(new binary_tree_node<Item>(object));
        if (object < node->data())
            node->set_left(insert(node->left(), object));
        else
            node->set_right(insert(node->right(), object));

        node->set_height(max(height(node->left()), height(node->right())) + 1);

        int balance = 0;
        if (node != NULL)
            balance = height(node->left()) - height(node->right());

        // Left Left
        if (balance > 1 && object < node->left()->data())
            return rotateRight(node);

        // Right Right
        if (balance < -1 && object > node->right()->data())
            return rotateLeft(node);

        // Left Right
        if (balance > 1 && object > node->left()->data())
        {
            node->set_left(rotateLeft(node->left()));
            return rotateRight(node);
        }
        // Right Left
        if (balance < -1 && object < node->right()->data())
        {
            node->set_right(rotateRight(node->right()));
            return rotateLeft(node);
        }
        return node;
    }

    template <typename Item>
    // create the first node with no child and set that as rot
    void binary_tree<Item>::create_first_node(const Item& entry){
        if(size() == 0){
            root = new binary_tree_node<Item>(entry);
            current = root;
            nodecounter++;
        }
    }

    template <typename Item>
    void binary_tree<Item>::shift_to_root( ){ //move currrent cursor to root
        if(size() > 0){
            current = root;
        }
    }

    template <typename Item>
    void binary_tree<Item>::shift_up( ){ // move current cursor to its parent if it exist
        if(has_parent() == true){
            current = current->parent();
        }
    }

    template <typename Item>
    void binary_tree<Item>::shift_left( ){ // move current cursor to its left child if it exist
        if(has_left_child() == true){
            current = current->left();
        }
    }

    template <typename Item>
    void binary_tree<Item>::shift_right( ){// move current cursor to its right child if it exist
        if(has_right_child() == true){
            current = current->right();
        }
    }

    template <typename Item>
    void binary_tree<Item>::change(const Item& new_entry){ // change the value of the current node
        if(size() > 0){
            current->set_data(new_entry);
        }
    }

    template <typename Item>
    void add(const Item& entry){


    }

    template <typename Item>
    std::size_t binary_tree<Item>::size( ) const{ //return the size of nodes
        return nodecounter;
    }

    template <typename Item>
    Item binary_tree<Item>::retrieve( ) const{ //retrieve the data of current node
        if(size() > 0){
            return current->data();
        }
        return Item();
    }

    template <typename Item>
    bool binary_tree<Item>::has_parent( ) const{ // check if current has parent
        if(size() > 0 && current->parent() != NULL){
            return true;
        }
        return false;
    }

    template <typename Item>
    bool binary_tree<Item>::has_left_child( ) const{// check if current has left child
        if(current ->left() != NULL){
            return true;
        }
        return false;
    }

    template <typename Item>
    bool binary_tree<Item>::has_right_child( ) const{// check if current has right child
        if(current ->right() != NULL){
            return true;
        }
        return false;
    }
