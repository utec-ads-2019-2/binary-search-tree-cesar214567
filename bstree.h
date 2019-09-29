#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"
#include <iostream>
using namespace std;

template <typename T> 
class BSTree {
    Node<T> *root;
    int sizes;
    int heights;

    void InOrderPrint(Node<T> *nodo){
        if (nodo!=nullptr){
            if (nodo->left!=nullptr ){
                InOrderPrint(nodo->left);
            }
            cout<<nodo->data<<" ";
            if (nodo->right!=nullptr){
                InOrderPrint(nodo->right);
            }
        }
    }

    void PostOrderPrint(Node<T> *nodo){
        if (nodo!=nullptr){
            if (nodo->left!=nullptr ){
                InOrderPrint(nodo->left);
            }
            if (nodo->right!=nullptr){
                InOrderPrint(nodo->right);
            }
            cout<<nodo->data<<" ";
        }
    }

    void PreOrderPrint(Node<T> *nodo){
        if (nodo!=nullptr){
            cout<<nodo->data<<" ";
            if (nodo->left!=nullptr ){
                InOrderPrint(nodo->left);
            }
            if (nodo->right!=nullptr){
                InOrderPrint(nodo->right);
            }
            
        }
    }

    void deleteNodo(Node<T> *nodo){
        if (nodo!=nullptr){
            deleteNodo(nodo->left);
            deleteNodo(nodo->right);
            delete this;
        }
    }

    public:
        BSTree() : root(nullptr),sizes(0),heights(0) {};

        bool find(T data) {
            auto temp=root; 
            if (root==nullptr){
                return false;
            }
            while (temp->data!=data){
                if (data<=temp->data){
                    if (temp->left!=nullptr){
                        temp=temp->left;
                    }else{
                        return false; 
                    }
                }else{
                    if (temp->right!=nullptr){
                        temp=temp->right;
                    }else{
                        return false;
                    }
                }
            }return true;
        } 

        bool insert(T data) {
            bool i=true;
            int temporal=0;
            if (root==nullptr){
                // Esto deberías poder sacarlo a un solo lugar, para crear el nodo
                // Cómo has hecho esto? Si el nodo no tiene constructor
                root=new Node<T>(data);
                sizes++;
                return true ;
            }
            Node<T>* b=root;
            while (i==true){
                if (data>b->data){
                    if (b->right==nullptr){
                        Node<T>* a=new Node<T>(data);
                        b->right=a;
                        i=false;
                    }else{
                        b=b->right;
                        temporal++;
                    }
                }else{
                    if (b->left==nullptr){
                        Node<T>* a=new Node<T>(data);
                        b->left=a;
                        i=false;
                    }else{
                        b=b->left;
                        temporal++;
                    }
                }
            }
            if (temporal>heights){
                heights=temporal;
            }
            sizes++;
            return true;

        }

        bool remove(T data) {
            if (root==nullptr){
                return false; 
            }
            Node<T> *padre1=root;
            Node<T> *data1=root;
            while (data1->data!=data){
                if (data>data1->data){
                    if (data1->right!=nullptr){
                        padre1=data1;
                        data1=data1->right;
                    }else{
                        return false;
                    }
                }else{
                    if (data1->left!=nullptr){
                        padre1=data1;
                        data1=data1->left;
                    }else{
                        return false;
                    }
                }
            }
            cout<<"padre1 "<<padre1->data<<endl;
            cout<<"data1 "<<data1->data<<endl;
            Node<T> *data2=data1;
            Node<T> *padre2=data2;
            if (data1==root){
                if (sizes==1){
                    delete root;
                    root=nullptr;
                }else{
                    //here goes if the data is  the root 
                    if (data1->right!=nullptr){
                        if(data1->left==nullptr){
                            root=data1->right;
                        }else{
                            data2=data2->left; 
                            while(data2->right!=nullptr){
                                padre2=data2;
                                data2=data2->right; 
                            }
                            cout<<"padre2 "<<padre2->data<<endl;
                            cout<<"data2 "<<data2->data<<endl;
                            data1->data=data2->data;
                            if(padre2->right==data2){
                                padre2->right=data2->left;
                            }else{
                                padre2->left=data2->left;
                            }  
                        }
                    }else{
                        if (data1->left!=nullptr){
                            root=data2->left;
                        }
                        // Dónde colocas los hijos como null?
                        delete data2;
                        sizes--;
                        return true;
                    }
                    

                }

                //here goes if the data is not the root
            }else{
                if (data1->left==nullptr){
                    if (data1->right==nullptr){
                        if (padre1->left==data1){
                            padre1->left=nullptr;
                        }else{
                            padre1->right=nullptr;
                        }
                        delete data1;
                    }else{
                        if (padre1->right==data1){
                            padre1->right=data1->right;
                        }else{
                            padre1->left=data1->right;
                        }
                        delete data1;
                    }
                }else{
                    if (data1->right==nullptr ){
                        if (padre1->right==data1){
                            padre1->right=data1->left;
                        }
                        else{
                            padre1->left=data1->left;
                        }
                        delete data1;
                    }else{
                        data2=data2->left;
                        while (data2->right!=nullptr){
                            padre2=data2;
                            data2=data2->right;
                        }
                        data1->data=data2->data;
                        if (padre2->right==data2){
                            padre2->right=data2->left;
                        }else{
                            padre2->left=data2->left;
                        }
                        delete data2;
                    }
                    }
                    sizes--;
                    return true;
                }
                

                



        }
            
        

        int size() {
            return sizes;
        }

        int height() {
            return heights;
        }

        void traversePreOrder() {
            PreOrderPrint(root);
            cout<<endl;
        }

        void traverseInOrder() {
            InOrderPrint(root);
            cout<<endl;
        }

        void traversePostOrder() {
            PostOrderPrint(root);
            cout<<endl;
        }

        Iterator<T> begin() {
            return {root,0};
        }

        Iterator<T> end() { 
            return {root,1};
        }

        ~BSTree() {
            deleteNodo(root);
        }
};

#endif
