#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include "funcs.h"


using namespace std;

int main(int argc, char* argv[]){               //taking command line arguments to read text file

    vector<string> wanted_values;               //vector to hold functions : median, firstq...
    vector<float> dataset;                      //vector to hold values of gap...

    fstream fin;                        

    fin.open(argv[1], ios::in);                 //opening input stream
    ofstream myfile("output.txt");              //creating output file

    int function_call = 0;                      //function call counter
    int counter = 0;                            //counter to hold number of elements is dataset
    int func_count = 1;                         //counter for print settings
    int line_count;                             //counter for input taking
    int is_sorted = 0;                          //counter to get is dataset already sorted for efficiency
    
    float gap;                                  //variables for parameters
    float grp;
    float v;
    float gi;

    int size;                               

    string temp;                                // temporary variables for reading

    string size_str;
    string line_count_str;
    string date;
    string hour;
    string first_date;                          //variable for first date and hour
    string first_hour;
    string expected_temp;                       //variable for gap,grp,v or gi

    getline(fin,size_str);                      //reading how many functions will call
    size = stoi(size_str);                      //casting to integer

    for(int i = 0; i < size; i++){              //reading expected functions and pushing them to vector
        getline(fin, temp);
        wanted_values.push_back(temp);
    }

    getline(fin, temp);                         //jumping the blank line

    getline(fin, line_count_str, ',');          //reading how many lines will be needed
    line_count = stoi(line_count_str);          //casting to integer
    
    getline(fin, expected_temp);               //reading the type of value gap...

    clock_t time_req = clock();

    for(int i = 0; i < line_count; i++){  //reading the functions(add or print) and getting datas

        getline(fin,temp);                      //reading the type of value (gap,grp...)

        if(temp == "add"){                      //checking the type of value so there won't be any further computational costs
            if(expected_temp == "gap"){
                if(counter == 0){               //checking the first time adding to get first date and hour
                        
                    getline(fin, first_date, ',');
                    getline(fin, first_hour, ',');

                    counter++;

                    getline(fin,temp,',');      //getting the gap value and letting others
                    gap = stof(temp);           //casting it to float

                    dataset.push_back(gap);     //pushing to vector
                                
                    getline(fin,temp,',');
                    getline(fin,temp,',');
                    getline(fin,temp);

                    i++;                        //increasing counter to jump to next line(escaping from input line)
                }
                else{

                getline(fin, date, ',');        //date and hour value for print call
                getline(fin, hour, ',');

                counter++;

                getline(fin,temp,',');          //getting the gap value and letting others
                gap = stof(temp);

                dataset.push_back(gap);
                            
                getline(fin,temp,',');
                getline(fin,temp,',');
                getline(fin,temp);

                i++;

                }    
            }

            else if(expected_temp == "grp"){            //same procedure with gap but this time for grp
                if(counter == 0){
                        
                    getline(fin, first_date, ',');
                    getline(fin, first_hour, ',');

                    counter++;

                    getline(fin,temp,',');

                    getline(fin,temp,',');
                    grp = stof(temp);

                    dataset.push_back(grp);
                                
                    getline(fin,temp,',');
                    getline(fin,temp);

                    i++;
                }
                else{
                    getline(fin, date, ',');
                    getline(fin, hour, ',');

                    counter++;

                    getline(fin,temp,',');

                    getline(fin,temp,',');
                    grp = stof(temp);

                    dataset.push_back(grp);
                                
                    getline(fin,temp,',');
                    getline(fin,temp);

                    i++;
                }    
            }

            else if(expected_temp == "v"){              //same procedure with gap but this time for v
                if(counter == 0){
                        
                    getline(fin, first_date, ',');
                    getline(fin, first_hour, ',');

                    counter++;

                    getline(fin,temp,',');
                    getline(fin,temp,',');

                    getline(fin,temp,',');

                    v = stof(temp);
                    dataset.push_back(v);

                    getline(fin,temp);
        
                    i++;
                }
                else{
                    getline(fin, date, ',');
                    getline(fin, hour, ',');

                    counter++;

                    getline(fin,temp,',');
                    getline(fin,temp,',');

                    getline(fin,temp,',');

                    v = stof(temp);
                    dataset.push_back(v);

                    getline(fin,temp);
        
                    i++;
                }    
            }

            else if(expected_temp == "gi"){                 //same procedure with gap but this time for gi
                if(counter == 0){
                        
                    getline(fin, first_date, ',');
                    getline(fin, first_hour, ',');

                    counter++;

                    getline(fin,temp,',');
                    getline(fin,temp,',');            
                    getline(fin,temp,',');

                    getline(fin,temp);
                    gi = stof(temp);
                    dataset.push_back(gi);

                    i++;
                }
                else{
                    getline(fin, date, ',');
                    getline(fin, hour, ',');

                    counter++;

                    getline(fin,temp,',');
                    getline(fin,temp,',');            
                    getline(fin,temp,',');

                    getline(fin,temp);
                    gi = stof(temp);
                    dataset.push_back(gi);

                    i++;
                }    
            }
        }
        else if(temp == "print"){               //checking if the called functions is print
            
            function_call++;

            //cout<<first_date<<",";            //control prints for values
            //cout<<first_hour<<",";

            myfile << first_date << ",";        //writing to output file
            myfile << first_hour << ",";

            //cout<<date<<",";
            //cout<<hour<<",";

            myfile << date << ",";
            myfile << hour << ",";

            for(int i = 0; i < size; i++){          //for loop to check every element in wanted values list
                                                    // to call functions which is necessary
                if(wanted_values[i] == "mean"){
                    myfile << get_mean(dataset, counter);       //writing to output
                    //cout<<get_mean(dataset, counter);
                    if(func_count < size){
                        myfile << ",";
                        //cout<<",";
                        func_count++;
                    }
                }
                else if(wanted_values[i] == "std"){
                    myfile<<get_std(dataset, counter);
                    //cout<<get_std(dataset, counter);
                    if(func_count < size){
                        myfile <<",";
                        //cout<<",";
                        func_count++;
                    }
                }
                else if(wanted_values[i] == "min"){
                    myfile << get_min(dataset, counter, is_sorted);
                    //cout<<get_min(dataset, counter, is_sorted);
                    if(func_count < size){
                        myfile<<",";
                        //cout<<",";
                        func_count++;
                    }
                }
                else if(wanted_values[i] == "firstq"){
                    myfile<<get_first_quartile(dataset, counter);
                    //cout<<get_first_quartile(dataset, counter);
                    if(func_count < size){
                        myfile<<",";
                        //cout<<",";
                        func_count++;
                    }
                }                
                else if(wanted_values[i] == "median"){
                    myfile<<get_median(dataset, counter);
                    //cout<<get_median(dataset, counter);
                    if(func_count < size){
                        myfile<<",";
                        //cout<<",";
                        func_count++;
                    }
                }
                else if(wanted_values[i] == "thirdq"){
                    myfile<<get_third_quartile(dataset, counter);
                    //cout<<get_third_quartile(dataset, counter);
                    if(func_count < size){
                        myfile<<",";
                        //cout<<",";
                        func_count++;
                    }
                }
                else if(wanted_values[i] == "max"){
                    myfile<<get_max(dataset, counter,is_sorted);
                    //cout<<get_max(dataset, counter, is_sorted);
                    if(func_count < size){
                        myfile<<",";
                        //cout<<",";
                        func_count++;
                    }                   
                }                
                //cout<<endl;
            }
            myfile<<endl;           //next line
        }
    }                                   //calculating time of functions that are called
    //time_req = clock() - time_req;
    //cout << "Running time of algorithm " << (float)time_req/CLOCKS_PER_SEC << " miliseconds" << endl;
    //cout << "function call  : " <<function_call<< endl;
    //cout << "Ratio of running time to faunction call quantity " <<  (float)((time_req)/function_call)<<endl;      
}