//
//  Name: Yuya Oguchi
//  COEN 70
//  Chapter 10, Project 12
//  3/13/2016
//  AVL tree for objects
//  In this case, object is a book with a few elements in it

#include "bt_class.h"
#include "list.h"
#include "book.h"
#include <iostream>
using namespace std;

//turn binary search tree to priority queue
template <typename T>
binary_tree<T> *turnToBTree(List<T> &list){
    list.start();
    if (list.size() == 0){
        return NULL;
    }
    return loop(list, 0, list.size()-1);;
}

//inorder traverse and push into queue to make priority queue
template <typename T>
binary_tree<T>* loop(List<T> &list, int start, int end){
    if (start > end){
        return NULL;
    }
    int mid = start + (end - start) / 2;
    binary_tree<T> *left = loop(list, start, mid-1);
    binary_tree<T> *root = new binary_tree<T>(list.current());
    list.advance();
    binary_tree<T> *right = loop(list, mid+1, end);
    root->add_left_tree(left);
    root->add_right_tree(right);
    return root;
}

int main(){
    binary_tree<Book> booklist;
    Book a("a", "a", "a", "a");
    Book b("b", "b", "b", "b");
    Book c("c", "c", "c", "c");
    Book d("d", "d", "d", "d");
    Book e("e", "e", "e", "e");
    Book f("f", "f", "f", "f");
    Book g("g", "g", "g", "g");
    Book h("h", "h", "h", "h");
    booklist.insert(a);
    booklist.insert(b);
    booklist.insert(c);
    booklist.insert(d);
    booklist.insert(e);
    booklist.insert(f);
    booklist.insert(g);
    booklist.insert(h);
    print(booklist.root,1);

    return 0;
}
