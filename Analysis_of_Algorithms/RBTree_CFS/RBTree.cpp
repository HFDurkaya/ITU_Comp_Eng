#include <iostream>
#include <stdio.h>
#include <fstream>
#include "RBTree.h"

using namespace std;

Node::Node(string name, int arrival_time ,int alocated_time){
    this->virtual_run_time = 0;                         //Virtual run time is initialized as 0
    this->name = name;                                  //Attributes are set accoring to inputs of constructor
    this->arrival_time = arrival_time;
    this->alocated_time = alocated_time;                 
    this->set_left_child(NULL);                         //Left child is set to NULL
    this->set_right_child(NULL);                        //Right child is set to NULL
    this->set_parent(NULL);                             //Parent is set to NULL
    this->colour = "Red";                               //Created node's colour must be red by definiton
}

void Node::set_alocated_time(int alocated_time){        //Getters and Setters
    this->alocated_time = alocated_time;    
}

void Node::increase_vrun_time(){
    this->virtual_run_time = this->virtual_run_time + 1;            //Increasing the virtual run time by 1
}

void Node::set_vrun_time(int virtual_run_time){
    this->virtual_run_time = virtual_run_time;
}

void Node::set_colour(string colour){
    this->colour =  colour;
}

int Node::get_alocated_time(){
    return this->alocated_time;
}

int Node::get_arrival_time(){
    return this->arrival_time;
}

string Node::get_name(){
    return this->name;
}

int Node::get_virtual_run_time(){
    return this->virtual_run_time;
}

string Node::get_colour(){
    return this->colour;
}

void Node::set_right_child(Node* node){
    this->right_child = node;
}

void Node::set_left_child(Node* node){
    this->left_child = node;
}

void Node::set_parent(Node* node){
    this->parent = node;
}

Node* Node::get_right_child(){
    return this->right_child;
}

Node* Node::get_left_child(){
    return this->left_child;
}

Node* Node::get_parent(){
    return this->parent;
}

Node* RBTree::get_root(){
    return this->root;
}

void RBTree::set_root(Node* new_root){
    this->root = new_root;
}

Node* RBTree::get_nil(){
    return this->NIL;
}

RBTree::RBTree(){                                   //Constructor for Red-Black Tree

    Node* NIL_node = new Node("nil",0,0);           //First create a node with values set            
    NIL_node->set_colour("Black");                  //By definiton nil's colour must be black

    this->NIL = NIL_node;                           //Set the tree's NIL equal to NIL_node
    this->root = this->NIL;                         //When tree is first created there are not any nodes so root is nil
}



void RBTree::rotate_left(Node* secondary_node){             
    
    Node* node = secondary_node->get_right_child();                             
    secondary_node->set_right_child(node->get_left_child());                    //turn node's left subtree into secondary_node's right subtree

    if(node->get_left_child() != this->get_nil()){                              //if node's left subtree is not empty
        node->get_left_child()->set_parent(secondary_node);                     // ... then secondary_node bceomes the parent of subtree's root
    }
    node->set_parent(secondary_node->get_parent());                             //secondary node's parent becomes node's parent

    if(secondary_node->get_parent() == this->get_nil()){                        //if secondary_node was the root
        this->set_root(node);                                                   //...then node becomes the root
    }
    else if(secondary_node == secondary_node->get_parent()->get_left_child()){  //otherwise, if secondary_node was a left child..
        secondary_node->get_parent()->set_left_child(node);                     //then node becomes a left child
    }
    else{                                                           
        secondary_node->get_parent()->set_right_child(node);                    //otherwise, secondary_node was a right child and now node is
    }
    node->set_left_child(secondary_node);                                       // make secondary_node become node's left child
    secondary_node->set_parent(node);

}

void RBTree::rotate_right(Node* secondary_node){

    Node* node = secondary_node->get_left_child();
    secondary_node->set_left_child(node->get_right_child());                    //turn node's rightsubtree into secondary node's left subtree

    if(node->get_right_child() != this->get_nil()){                             //if node's right subtree is not empty
        node->get_right_child()->set_parent(secondary_node);                    //... then secondary_node becomes the parent of subtree's root
    }
    node->set_parent(secondary_node->get_parent());                             //secondary_node's parent becomes node's parent

    if(secondary_node->get_parent() == this->get_nil()){                        //if secondary_node was the root
        this->set_root(node);                                                   //... then node becomes the root
    }
    else if(secondary_node == secondary_node->get_parent()->get_right_child()){ //otherwise, if secondary_node was a right child...
        secondary_node->get_parent()->set_right_child(node);                    //then node becomes a right child
    }
    else{
        secondary_node->get_parent()->set_left_child(node);                     //otherwise, secondary_node was a left child and now node is
    }
    node->set_right_child(secondary_node);                                      //make secondary_node becomes node's right child
    secondary_node->set_parent(node);

}

void RBTree::reorder_insert(Node* new_node){

    while(new_node->get_parent()->get_colour() == "Red"){
        
        if(new_node->get_parent() == new_node->get_parent()->get_parent()->get_left_child()){   //is new_node's parent a left child

            Node* temp_node = new_node->get_parent()->get_parent()->get_right_child();          // temo_node is uncle of new_Node
            
            if(temp_node->get_colour() == "Red"){                               //are new_node's parent and uncle both red
                new_node->get_parent()->set_colour("Black");                    //CASE 1
                temp_node->set_colour("Black");                                 
                new_node->get_parent()->get_parent()->set_colour("Red");
                new_node = new_node->get_parent()->get_parent();
            }
            else{
                if(new_node == new_node->get_parent()->get_right_child()){      //CASE 2
                    new_node = new_node->get_parent();
                    this->rotate_left(new_node);
                }
                new_node->get_parent()->set_colour("Black");                    //CASE 3
                new_node->get_parent()->get_parent()->set_colour("Red");
                this->rotate_right(new_node->get_parent()->get_parent());
            }
        }
        else{                                       // below this else it is just same as above but right and left reversed
                    
            Node* temp_node = new_node->get_parent()->get_parent()->get_left_child();
            
            if(temp_node->get_colour() == "Red"){
                new_node->get_parent()->set_colour("Black");
                temp_node->set_colour("Black");
                new_node->get_parent()->get_parent()->set_colour("Red");
                new_node = new_node->get_parent()->get_parent();
            }
            else{
                if(new_node == new_node->get_parent()->get_left_child()){
                    new_node = new_node->get_parent();
                    this->rotate_right(new_node);
                }
                new_node->get_parent()->set_colour("Black");
                new_node->get_parent()->get_parent()->set_colour("Red");
                this->rotate_left(new_node->get_parent()->get_parent());
            }

        }
    }

    this->get_root()->set_colour("Black");

} 


void RBTree::RBinsert(Node* new_node){ 

    Node* temp_node = this->get_root();                            //temp_node being compared with new_node
    Node* node = this->get_nil();                                  // node will be parent of new_node

    while(temp_node != this->get_nil()){                            //descend until reaching a nil node

        node = temp_node;

        if(new_node->get_virtual_run_time() < temp_node->get_virtual_run_time()){
            temp_node = temp_node->get_left_child();
        }
        else if (new_node->get_virtual_run_time() > temp_node->get_virtual_run_time()){
            temp_node = temp_node->get_right_child();
        }
        else if(new_node->get_virtual_run_time() == temp_node->get_virtual_run_time()){

            if(new_node->get_arrival_time() < temp_node->get_arrival_time()){
                temp_node = temp_node->get_left_child();
            }
            else{
                temp_node = temp_node->get_right_child();  
            }
        }
    }
    new_node->set_parent(node);                             //location is found, insert new_node with parent node

    if(node == this->get_nil()){                            // The tree was empty
        this->set_root(new_node);
    }
    else if(new_node->get_virtual_run_time() < node->get_virtual_run_time()){
        node->set_left_child(new_node);
    }
    else if(new_node->get_virtual_run_time() > node->get_virtual_run_time()){
        node->set_right_child(new_node);
    }
    else if(new_node->get_virtual_run_time() == node->get_virtual_run_time()){

        if(new_node->get_arrival_time() < node->get_arrival_time()){
            node->set_left_child(new_node);
        }
        else{
            node->set_right_child(new_node);
        }
    }

    new_node->set_left_child(this->get_nil());              //both of the children of new_node are sentinel
    new_node->set_right_child(this->get_nil());

    this->reorder_insert(new_node);                         //correct any violations of red-black tree properity if there are any with this function

}

void RBTree::transplant(Node* node1, Node* node2){

        if(node1->get_parent() == this->get_nil()){             //if node1's parent is nil, node1 is root

            this->set_root(node2);                              //set node2 as root
        }
        else if(node1 == node1->get_parent()->get_left_child()){        //if node1 is it's parent's left_child

            node1->get_parent()->set_left_child(node2);                 //set node1's parent's left child as node2
        }
        else{                                                           //node 1 is it's parent's left_child

            node1->get_parent()->set_right_child(node2);                //node1's parent's right child is node2
        
        }

        node2->set_parent(node1->get_parent());                 //node2's parent is node1's parent

}

void RBTree::reorder_delete(Node* secondary_node){
    
    while(secondary_node != this->get_root() && secondary_node->get_colour() =="Black"){
        
        if(secondary_node == secondary_node->get_parent()->get_left_child()){       //is secondary_node a left child
            
            Node* new_node = secondary_node->get_parent()->get_right_child();       //new_Node is secondary_node's sibling
            
            if(new_node->get_colour() == "Red"){                            //CASE1
                new_node->set_colour("Black");
                secondary_node->get_parent()->set_colour("Red");
                rotate_left(secondary_node->get_parent());
                new_node = secondary_node->get_parent()->get_right_child();
            }
            if(new_node->get_left_child()->get_colour() == "Black" && new_node->get_right_child()->get_colour() == "Black"){
                new_node->set_colour("Red");                                //CASE2
                secondary_node = secondary_node->get_parent();
            }
            else{                                                           //CASE3
                if(new_node->get_right_child()->get_colour() == "Black"){
                    new_node->get_left_child()->set_colour("Black");
                    new_node->set_colour("Red");
                    rotate_right(new_node);
                    new_node = secondary_node->get_parent()->get_right_child();
                }                                                           //CASE4
                new_node->set_colour(secondary_node->get_parent()->get_colour());
                secondary_node->get_parent()->set_colour("Black");
                new_node->get_right_child()->set_colour("Black");
                rotate_left(secondary_node->get_parent());
                secondary_node = this->get_root();
            }
        }
        else{                       //same as above but right and left parts are reversed
            
            Node* new_node = secondary_node->get_parent()->get_left_child();
            
            if(new_node->get_colour() == "Red"){
               
                new_node->set_colour("Black");
                secondary_node->get_parent()->set_colour("Red");
                rotate_right(secondary_node->get_parent());
                new_node = secondary_node->get_parent()->get_left_child();

            }

            if(new_node->get_right_child()->get_colour() == "Black" && new_node->get_left_child()->get_colour() == "Black"){
                new_node->set_colour("Red");
                secondary_node = secondary_node->get_parent();
            }
            else{
                if(new_node->get_left_child()->get_colour() == "Black"){
                    new_node->get_right_child()->set_colour("Black");
                    new_node->set_colour("Red");
                    rotate_left(new_node);
                    new_node = secondary_node->get_parent()->get_left_child();
                }
                new_node->set_colour(secondary_node->get_parent()->get_colour());
                secondary_node->get_parent()->set_colour("Black");
                new_node->get_left_child()->set_colour("Black");
                rotate_right(secondary_node->get_parent());
                secondary_node = this->get_root();
            }

        }
    }
    secondary_node->set_colour("Black");

}

void RBTree::RBDelete(Node* target_node){

    Node* temp = target_node;
    Node* temp_node;
    std::string temp_color = temp->get_colour();

    if(target_node->get_left_child() == this->get_nil()){                   //if target_node does not have any left child

        temp_node = target_node->get_right_child();
        transplant(target_node, target_node->get_right_child());            //replace target_node with it's right child
        
    }
    else if(target_node->get_right_child() == this->get_nil()){

        temp_node = target_node->get_left_child();
        transplant(target_node, target_node->get_left_child());             //replace target_node by it's left child
    }
    else{
        temp = get_left_most(target_node->get_right_child());               //temp is target_node's successor
        temp_color = temp->get_colour();
        temp_node = temp->get_right_child();

        if(temp->get_parent() == target_node){                  //if temp's parent is target_node
            temp_node->set_parent(target_node);                 //set temp_node's parent as target_node
        }
        else{
            transplant(temp, temp->get_right_child());              //replace temp with it's right child
            temp->set_right_child(target_node->get_right_child());  //target_node's right child becomes
            temp->get_right_child()->set_parent(temp);              //temp's right chid
        }
        transplant(target_node, temp);                              //replace target_node with temp
        temp->set_left_child(target_node->get_left_child());        //give target_node's left child to temp
        temp->get_left_child()->set_parent(temp);                   //temp had no left child
        temp->set_colour(target_node->get_colour());
    }
    if(temp_color == "Black")                       //if any red-black tree properity is violated , fix them up
        reorder_delete(temp_node);

}


Node* RBTree::get_left_most(Node* root){                //Function to get the left most element in the tree

    while(root->get_left_child() != this->get_nil())
        root = root->get_left_child();
    
    return root;
}

void RBTree::inorder_traversal(ofstream &myfile, Node *root){       //Inorder traversal function sepcialized to print the node's names and their virtual run time

    if(root != this->get_nil()){
        inorder_traversal(myfile,root->get_left_child());

        cout<<root->get_name()<<":"<<root->get_virtual_run_time()<<"-"<<root->get_colour();
        myfile<<root->get_name()<<":"<<root->get_virtual_run_time()<<"-"<<root->get_colour();
        if(root != this->get_right_most(this->get_root())){
            cout<<";";
            myfile<<";";
        }
        inorder_traversal(myfile,root->get_right_child());
    }

}

Node* RBTree::get_right_most(Node* root){                       //Function to get the right most element in a tree

    while(root->get_right_child() != this->get_nil())
        root = root->get_right_child();
    
    return root;
}
