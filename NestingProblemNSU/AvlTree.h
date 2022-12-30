#pragma once

#include<iostream>
using namespace std;

template <typename Key, typename Value>
class AvlTree{
public:
    class node{
    public:
        Key key;
        Value value;
        int height;
        node* left;
        node* right;

        node( Key _key, Value _value ){
            height = 1;
            key = k;
            value = _value;
            left = nullptr;
            right = nullptr;
        }
    };
    node* root = nullptr;
    int n;
    void insert( Key x, Value value ){
        root = insertUtil( root, x, value );
    }
    void remove( Key x ){
        root = removeUtil( root, x );
    }
    node* search( Key x ){
        return searchUtil( root, x );
    }

    node* maxNode(){
        return maxNodeUtil( root );
    }

    node* minNode(){
        return minNodeUtil( root );
    }

    void inorder(){
        inorderUtil( root );
        cout << endl;
    }
private:
    int height( node* head ){
        if ( head == nullptr ) return 0;
        return head->height;
    }
    node* rightRotation( node* head ){
        node* newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1 + max( height( head->left ), height( head->right ) );
        newhead->height = 1 + max( height( newhead->left ), height( newhead->right ) );
        return newhead;
    }

    node* leftRotation( node* head ){
        node* newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1 + max( height( head->left ), height( head->right ) );
        newhead->height = 1 + max( height( newhead->left ), height( newhead->right ) );
        return newhead;
    }

    void inorderUtil( node* head ){
        if ( head == nullptr ) return;
        inorderUtil( head->left );
        cout << head->key << " ";
        inorderUtil( head->right );
    }

    node* insertUtil( node* head, Key x, Value value ){
        if ( head == nullptr )
        {
            n += 1;
            node* temp = new node( x, value );
            return temp;
        }
        if ( x < head->key ) head->left = insertUtil( head->left, x, value );
        else if ( x > head->key ) head->right = insertUtil( head->right, x, value );
        head->height = 1 + max( height( head->left ), height( head->right, value ) );
        int bal = height( head->left ) - height( head->right );
        if ( bal > 1 )
        {
            if ( x < head->left->key )
            {
                return rightRotation( head );
            }
            else
            {
                head->left = leftRotation( head->left );
                return rightRotation( head );
            }
        }
        else if ( bal < -1 )
        {
            if ( x > head->right->key )
            {
                return leftRotation( head );
            }
            else
            {
                head->right = rightRotation( head->right );
                return leftRotation( head );
            }
        }
        return head;
    }
    node* removeUtil( node* head, Key x ){
        if ( head == nullptr ) return nullptr;
        if ( x < head->key )
        {
            head->left = removeUtil( head->left, x );
        }
        else if ( x > head->key )
        {
            head->right = removeUtil( head->right, x );
        }
        else
        {
            node* r = head->right;
            if ( head->right == nullptr )
            {
                node* l = head->left;
                delete( head );
                head = l;
            }
            else if ( head->left == nullptr )
            {
                delete( head );
                head = r;
            }
            else
            {
                while ( r->left != nullptr ) r = r->left;
                head->key = r->key;
                head->right = removeUtil( head->right, r->key );
            }
        }
        if ( head == nullptr ) return head;
        head->height = 1 + max( height( head->left ), height( head->right ) );
        int bal = height( head->left ) - height( head->right );
        if ( bal > 1 )
        {
            if ( height( head->left ) >= height( head->right ) )
            {
                return rightRotation( head );
            }
            else
            {
                head->left = leftRotation( head->left );
                return rightRotation( head );
            }
        }
        else if ( bal < -1 )
        {
            if ( height( head->right ) >= height( head->left ) )
            {
                return leftRotation( head );
            }
            else
            {
                head->right = rightRotation( head->right );
                return leftRotation( head );
            }
        }
        return head;
    }
    node* searchUtil( node* head, Key x ){
        if ( head == nullptr ) return nullptr;
        Key k = head->key;
        if ( k == x ) return head;
        if ( k > x ) return searchUtil( head->left, x );
        if ( k < x ) return searchUtil( head->right, x );
    }

    node* maxNodeUtil( node* head ){
        if ( head == nullptr ) return head;
        if ( head->right == nullptr ) return head;
        return maxNodeUtil( head->right );
    }

    node* minNodeUtil( node* head ){
        if ( head == nullptr ) return head;
        if ( head->left == nullptr ) return head;
        return minNodeUtil( head->left );
    }
};