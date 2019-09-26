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
            Node<T> *data1=root;
            Node<T> *padre1=nullptr;
            if (root==nullptr){
                return false;
            }
            if (sizes==1 && data==root->data){
                cout<<"CASO1"<<endl;
                auto temporal=root; 
                root=nullptr;
                sizes--;
                delete temporal;
                return true;
            }
            
            while (data1->data!=data){
                if (data<=data1->data){
                    if (data1->left!=nullptr){
                        padre1=data1;
                        data1=data1->left;
                    }else{
                        return false; 
                    }
                }else{
                    if (data1->right!=nullptr){
                        padre1=data1;
                        data1=data1->right;
                    }else{
                        return false;
                    }
                }
            }
            cout<<"data es"<<data1->data<<endl;
            if (padre1!=nullptr){
                cout<<"padre es"<<padre1->data<<endl;
            
            }else{
                cout<<"el padre del root no existe "<<endl;
            }
            Node<T> *data2=data1;
            Node<T> *padre2=nullptr;
            if (data2->left==nullptr && data2->right==nullptr){
                cout<<"no tiene hijos"<<endl;
                if (padre1->right!=nullptr){
                    if (padre1->right->data==data ){
                        cout<<"CASO2"<<endl;
                        padre1->right=nullptr;
                        delete data2;
                        sizes--;
                        return true;
                    }   
                }
                if (padre1->left!=nullptr){
                    if (padre1->left->data==data ){
                        cout<<"CASO3"<<endl;
                        padre1->left =nullptr;
                        delete data2;
                        sizes--;
                        return true;
                    }
                }
            }else{
                if (data2->left!=nullptr){
                    padre2=data2;
                    data2=data2->left;
                }else{
                    cout<<"NO SE QUE ESTA PASANDO"<<endl;
                    cout<<"data2 es "<<data2->right->data<<endl; 
                    auto dataaaa=data2->right;
                    cout<<"CASO3.9"<<endl;
                    if (padre1->right!=nullptr && padre1!=nullptr){
                        if (padre1->right->right==dataaaa){  
                            padre1->right=dataaaa;
                            cout<<"CASO4"<<endl;
                            delete data2;
                            sizes--;
                            return true;
                        }
                        else{
                            if (padre1->left->right==dataaaa && padre1!=nullptr){
                                cout<<"CASO 5"<<endl;
                                padre1->left=dataaaa;
                                sizes--;
                                delete data2;
                                return true;
                            }
                    
                        }
                    }
                    
                }
                
                while (data2->right!=nullptr){
                    padre2=data2;
                    data2=data2->right;
                }
                cout<<"data2 "<<data2->data<<endl;
                if (padre2!=nullptr){
                    cout<<"padre2 "<<padre2->data<<endl;
                }
                

                // until here works very well
                if (root->data==data){
                    int temporal=root->data;

                }
                if (data2==padre2->left && padre2!=nullptr){
                    if (data2->left==nullptr){
                        padre2->left=nullptr;
                        int temporal=data1->data;
                        data1->data=data2->data;
                        data2->data=temporal;
                        cout<<"CASO6"<<endl;
                        delete data2;
                        sizes--;
                        return true;
                    }
                }
                if (data2->left!=nullptr &&padre2->right==data2 && padre2!=nullptr){
                    cout<<"went here "<<endl;
                    padre2->right=data2->left;
                }else{
                    if (padre2->right==data2){
                        padre2->right=nullptr;
                    }
                }
                cout<<"CASO7"<<endl;
                int temporal=data1->data;
                data1->data=data2->data;
                data2->data=temporal;
                sizes--;                
                delete data2;
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
            // TODO
        }

        void traverseInOrder() {
            InOrderPrint(root);
        }

        void traversePostOrder() {
            // TODO
        }

        Iterator<T> begin() {
            // TODO
        }

        Iterator<T> end() { 
            // TODO
        }

        ~BSTree() {
            // TODO
        }
};

#endif
