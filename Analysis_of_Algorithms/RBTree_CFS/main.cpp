#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include "RBTree.h"

using namespace std;

int main(int argc, char* argv[]){

    clock_t time_req = clock();             //Clock is set to calculate how much time has passed in running

    RBTree tree;                            //Tree has been set
    vector<Node*> process_list;             //Vector to store processes to insert to tree when arrival time has come
    vector<string> list_finished_process;   //Vector to store names of the finished processes
    Node* CPU_node = NULL;                  // Temporary node to represent CPU's working node

    fstream fin;                            

    fin.open(argv[1], ios::in);             //opening the stream to read from the file
    ofstream myfile("output.txt");          //opening the stream to write to file

    string number_of_process_str;           //variables to read datas from the files
    string time_str;
    int time;                               //time variable to get how many seconds will simulation last
    int number_of_process;
    int finished_process = 0;               //counter to hold how many processes have been finished
    bool is_complete = false;               //bool variable to get if simulation is completed or not

    string name;                            //variables
    string arrival_time_str;
    string alocated_time_str;
    int arrival_time;
    int alocated_time;

    getline(fin, number_of_process_str,' ');            //reading from the file with getline
    getline(fin, time_str);
    number_of_process = stoi(number_of_process_str);    //conerting from string to integer
    time = stoi(time_str);

    for(int i = 0; i < number_of_process; i++){
        getline(fin, name,' ');
        getline(fin, arrival_time_str,' ');
        getline(fin, alocated_time_str);

        arrival_time = stoi(arrival_time_str);
        alocated_time = stoi(alocated_time_str);

        Node* new_node = new Node(name, arrival_time, alocated_time);   //creating a node with read values

        process_list.push_back(new_node);           //pushing created node to processlist vector
    }
    
    for(int i = 0; i < time; i++){          //main for loop to represent the simulation time

        if(is_complete == true)             //checking if the simulation is completed before the loop
            break;
        
        cout<<i;                            //writing to file
        myfile << i;
        for(int k = 0; k < number_of_process; k++){         //checking if any of the processes arrival time has come
            
            if(process_list[k]->get_arrival_time() == i){
                
                tree.RBinsert(process_list[k]);             //if arrival time has come insert to the tree

            }
        }

        if(tree.get_root() != tree.get_nil() && CPU_node == NULL){          //checking if the root is nil and CPU_node is null
            
            if(tree.get_left_most(tree.get_root())->get_right_child() == tree.get_nil()){       //getting the left most element's right is nil
                
                CPU_node = tree.get_left_most(tree.get_root());         //CPU_node is set to leftmost node
            

                cout<<","<<CPU_node->get_name();                        //printing the current node's data
                cout<<","<<CPU_node->get_virtual_run_time();
                cout<<","<<CPU_node->get_virtual_run_time()<<",";

                myfile<<","<<CPU_node->get_name();
                myfile<<","<<CPU_node->get_virtual_run_time();
                myfile<<","<<CPU_node->get_virtual_run_time()<<",";
                
                tree.inorder_traversal(myfile ,tree.get_root());       //traversing the tree

                CPU_node->increase_vrun_time();                         //increasing the processed node's virtual run time
                
                if(CPU_node->get_virtual_run_time() < CPU_node->get_alocated_time()){   //checking if run time is lower than allocated time

                    if(CPU_node == tree.get_root()){            //checking if the CPU_node is root
                        tree.set_root(CPU_node);
                    }

                    else if(CPU_node->get_virtual_run_time() > CPU_node->get_parent()->get_virtual_run_time()){ //if virtual tun time is greater than its parent
                                               
                        Node* new_node = new Node(CPU_node->get_name(), CPU_node->get_arrival_time(), CPU_node->get_alocated_time());
                        new_node->set_vrun_time(CPU_node->get_virtual_run_time());  //delete the node and create a new node with its values
                        tree.RBDelete(tree.get_left_most(tree.get_root()));         //and insert created node to tree
                        tree.RBinsert(new_node);                      
                    }


                    CPU_node = NULL;            //refreshing the CPU_node
                }
                else if(CPU_node->get_virtual_run_time() == CPU_node->get_alocated_time()){         //if allocate time is equal to run time
                                                       
                    tree.RBDelete(tree.get_left_most(tree.get_root()));         //delete the node

                    list_finished_process.push_back(CPU_node->get_name());      //label the node as finishde and push to vector
                    finished_process++;             //increase the amount of finished processes
                    CPU_node = NULL;                //refresh the CPU_node
   
                }

            }
            else{
                
                CPU_node = tree.get_left_most(tree.get_root());     //same setup as above

                cout<<","<<CPU_node->get_name();
                cout<<","<<CPU_node->get_virtual_run_time();
                cout<<","<<CPU_node->get_virtual_run_time()<<",";

                myfile<<","<<CPU_node->get_name();
                myfile<<","<<CPU_node->get_virtual_run_time();
                myfile<<","<<CPU_node->get_virtual_run_time()<<",";


                tree.inorder_traversal(myfile ,tree.get_root());


                CPU_node->increase_vrun_time();

                if(CPU_node->get_virtual_run_time() < CPU_node->get_alocated_time()){   //cheking if run time is smaller than allocated time
                    
                    if(CPU_node == tree.get_root() && CPU_node->get_virtual_run_time() < CPU_node->get_right_child()->get_virtual_run_time()){
                        //checking if the node's run time is smaller than parent's and it's right child
                        tree.get_left_most(tree.get_root())->increase_vrun_time();  //only the increment is done
                    }
                    
                    if(CPU_node->get_virtual_run_time() > CPU_node->get_parent()->get_virtual_run_time()){  //checking if run time is greater than it's parent
                        Node* new_node = new Node(CPU_node->get_name(), CPU_node->get_arrival_time(), CPU_node->get_alocated_time());
                        new_node->set_vrun_time(CPU_node->get_virtual_run_time());
                        tree.RBDelete(tree.get_left_most(tree.get_root()));         //delete and create a new node with it's values
                        tree.RBinsert(new_node);                                    //insert created node to tree
                    }

                    else if(CPU_node->get_virtual_run_time() > CPU_node->get_right_child()->get_virtual_run_time()){    //checking the run time is greater than it's right child
                        
                        tree.RBDelete(tree.get_left_most(tree.get_root()));
                        Node* new_node = new Node(CPU_node->get_name(), CPU_node->get_arrival_time(), CPU_node->get_alocated_time());
                        new_node->set_vrun_time(CPU_node->get_virtual_run_time());      // delete and create a new node with it's values
                        tree.RBinsert(new_node);                                        //insert created node to tree             
                    }
                    else{}

                    CPU_node = NULL;            //refreshing the CPU_node 
                }
                else if(CPU_node->get_virtual_run_time() == CPU_node->get_alocated_time()){      //if run time is equal to allocated time              
                        
                        tree.RBDelete(tree.get_left_most(tree.get_root()));     //deleting the node

                        list_finished_process.push_back(CPU_node->get_name());  //pushing finished node (labelling the node)
                        finished_process++;         //incrementing finished process counter
                        CPU_node = NULL;            //refreshing the CPU_node 

                }

            }

        }
        else{           //if none of the above has worked

            myfile<<",-,-,-,-,-,-";    
            cout<<",-,-,-,-,-,-";
        }

            if(finished_process > 0 && finished_process < number_of_process){ //Checking if one or more processes but not all have been finished
                myfile << ",Completed";    
                cout<<",Completed";
            }    
            else if(finished_process < number_of_process && tree.get_root() != tree.get_nil()){//checking o none of the processes have been completed and tree is not null
                myfile << ",Incomplete";    
                cout<<",Incomplete";
            }
            else if(finished_process >= number_of_process){ //all of the processes have been finished
                myfile << ",Completed";    
                cout<<",Completed";
                is_complete = true;
            }
            cout<<endl;
            myfile<<endl;
        


    }
    
    myfile<<endl;    
    cout<<endl;
    time_req = clock() - time_req;      //calculating the scheduling time
    cout << "Scheduling finished in " << (float)time_req/CLOCKS_PER_SEC << " ms." <<endl;
    myfile << "Scheduling finished in " << (float)time_req << " ms." <<endl;
    cout<<finished_process<<" of "<<number_of_process<<" processes are completed."<<endl;
    cout<<"The order of completion of the tasks: ";                                     //printing the order of completion
    myfile<<finished_process<<" of "<<number_of_process<<" processes are completed."<<endl;
    myfile<<"The order of completion of the tasks: ";
    
    for(unsigned int i = 0; i < list_finished_process.size(); i++){
        if(list_finished_process.size() == (i+1) || list_finished_process.size() == 1){
            myfile<<list_finished_process[i]<<endl;    
            cout<<list_finished_process[i]<<endl;
        }
        else{
            myfile<<list_finished_process[i]<<"-";    
            cout<<list_finished_process[i]<<"-";
        }
    }
}
