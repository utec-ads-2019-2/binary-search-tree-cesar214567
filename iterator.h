#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stack>
template <typename T> 
class Iterator {
    private:
        Node<T> *current;
        stack<Node<T>*> stack_de_iterador;

    public:
        Iterator() {
            current=nullptr;
        }

        Iterator(Node<T> *node,int flag) {
            if (flag==0){
                while(node){
                    stack_de_iterador.push(node);
                    node=node->left;
                }
            }else{
                while(node){
                    node=node->right;
                }
            }
            this->current=node;

        }

        Iterator<T>& operator=(const Iterator<T> &other) {          
            current=other->current;
            return *this;
        }

        bool operator!=(Iterator<T> other) {
            if (current!=other.current){
                return true;
            }else{
                return false;
            }
        }

        Iterator<T>& operator++() {
            Node<T>* temporal=stack_de_iterador.top();
            stack_de_iterador.pop();
            if (temporal->right){
                stack_de_iterador.push(temporal->right);
                while (stack_de_iterador.top()->left ){
                    stack_de_iterador.push(stack_de_iterador.top()->left);
                }
            }
            if (stack_de_iterador.empty()==false){
                current=stack_de_iterador.top();
            }else{
                current==nullptr;
            }
        }

        Iterator<T>& operator--() {
            // TODO
        }

        T operator*() {
            if(current){
                return current->data;
            }else{
                cout<<"out of range"<<endl;
            }
        }
};

#endif
