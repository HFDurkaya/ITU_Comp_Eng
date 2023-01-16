#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>



using namespace std;

class Node{                             //Class for Node representation
    
    private:
                                        //Data attributes
        string name;                    //string variable which stores name of process     
        int arrival_time;               //integer variable which stores the arrival time of process
        int virtual_run_time;           //integer variable which stores the virtual run time of process
        int alocated_time;              //integer variable which stores the allocated time of process
        string colour;                  //string variable which stores the colour of the node
                                        
        Node* right_child;              //Pointer to right child of node
        Node* left_child;               //Pointer to left child of node
        Node* parent;                   //pointer to parent of node

    public:                             

        Node(string name, int arrival_time ,int alocated_time);         //Constructor for node class
        void set_alocated_time(int alocated_time);                      //Getters and setters
        void increase_vrun_time();                                      //Increase the virtual run time of current node
        void set_vrun_time(int virtual_run_time);       
        void set_colour(string colour);
        int get_alocated_time();
        int get_arrival_time();
        string get_name();
        int get_virtual_run_time();
        string get_colour();
        void set_left_child(Node* node);
        void set_right_child(Node* node);
        void set_parent(Node* node);
        Node* get_right_child();
        Node* get_left_child();
        Node* get_parent();

};

class RBTree{                       //Class for Red Black Tree representation
    
    private:                        //Root and NIL
        Node* root;
        Node* NIL;

    public:
                                    
        RBTree();                                   //Constructor
        Node* get_root();                           //GEtters and setters
        Node* get_nil();
        void set_root(Node* new_root);
        
        void rotate_left(Node* secondary_node);     //Rotation Left function for reordering
        void rotate_right(Node* secondary_node);    //Rotation right function for reordering
        void reorder_insert(Node* secondary_node);  //Reordering after inseriton function
        void reorder_delete(Node* secondary_node);  //Reordering after deletion function

        void RBinsert(Node* new_node);              //Red-Black Tree node insertion function
        void RBDelete(Node* target_node);           //Red-Black Tree node deletion function
        void transplant(Node* node1, Node* node2);  //Transplant function for reorder delete
        void inorder_traversal(ofstream &myfile , Node* root);      //Inorder traversal function
        Node* get_left_most(Node* root);                    //Function to reach left most element
        Node* get_right_most(Node* root);                   //Function to reach right most element

};