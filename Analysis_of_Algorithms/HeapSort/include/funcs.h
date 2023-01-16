#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;                        //header file for functions

float get_mean(vector<float> datas, int counter){           //function to calculate mean
    float mean;
    float sum;

    for(int i = 0; i < counter; i++)
        sum = sum + datas[i];       

    mean = (sum / counter);
    return mean;
}

float get_min(vector<float> datas, float counter, int is_sorted){           //function to calculate min
        
    float min = datas[0];

    if(is_sorted == 1){                         //if dataset is already sorted complexity will be constant
        return min;
    }
    else{
        for(int i = 0; i < counter; i++){
            if(min > datas[i])
                min = datas[i];
        }
        return min;
    }    
}

float get_max(vector<float>datas, double counter, int is_sorted){       //function to calculate max
    
    float max = datas[0];

    if(is_sorted == 1){                     //if dataset is already sorted complexity will be constant
        return datas[counter];
    }
    else{
        
        for(int i = 0; i < counter; i++){
            
            if(max < datas[i]){
                max = datas[i];
            }
        }
        return max;
    }
}

float get_std(vector<float> datas, float counter){          //function to calculate standard deviation
    
    double mean = get_mean(datas,counter);
    double std;

    for(int i = 0; i < counter; i++){
        std += (datas[i] - mean) * (datas[i] - mean);
    }
    
    return sqrt(std/(counter-1));
}

void heapify(vector<float> &datas, float size, int sub_root){       //I ahve used heaps as a data sturcuture to sort values
    int left_child = (2 * sub_root) + 1;                            //getting the left child index
    int right_child = (2 * sub_root) + 2;                           //getting the right child index

    float temp_var;
    float largest = sub_root;

    if(left_child < size && datas[left_child] > datas[largest])     //checking if left child is greater than the largest
        largest = left_child;
    if(right_child < size && datas[right_child] > datas[largest])   //checking if right child is greater than the largest
        largest = right_child;
    
    if(largest != sub_root){
        temp_var = datas[sub_root];                         
        datas[sub_root] = datas[largest];                   //swap operation
        datas[largest] = temp_var;
        heapify(datas, size, largest);                      //heapify in the sub heap
    }
}

void heapSort(vector<float> &datas, float size){            //sorting algorithm
    float temp_var;

    for(int i = (size/2) - 1; i >= 0; i--)                  
        heapify(datas, size, i);
    for(int i = (size-1); i >= 0;i--){
        temp_var = datas[0];
        datas[0] = datas[i];
        datas[i] = temp_var;

        heapify(datas, i,0);
    }

}

float get_median(vector<float>datas, int size){         //function to calculate median
    
    heapSort(datas,size);                               //sorting to get the median
    
    if(size % 2 == 0)                                   //checking if size is divisble by two
        return ((datas[size/2] + datas[size/2-1])/2);
    else{
        return datas[size/2];
    }
}
float get_first_quartile(vector<float>datas, int size){     //calculating the first quartile

    heapSort(datas,size);                                   //sorting

    double step = 100/double(size - 1);                     //calculating the step_length
    int left_bound = (25/step);                             //calculating the left bound

    int right_bound = (left_bound + 1);                     //calculating the right bound

    float l_coefficent = 1 - ((25 - left_bound * step) / (float)step);      //calculating the coefficient for first term
    float r_coefficent = 1 - l_coefficent;                                  //calculating the coefficient for second term

    float quartile = (datas[left_bound] * l_coefficent) + (datas[right_bound] * r_coefficent);  //calculating the quartile

    return quartile;
}

float get_third_quartile(vector<float>datas, int size){             //calculating the tihrd quartile

    heapSort(datas,size);                                           //sorting

    double step = 100/double(size - 1);                             //calculating the step_length
    int left_bound = (75/step);                                     //calculating the left bound

    int right_bound = (left_bound + 1);                             //calculating the right bound

    float l_coefficent = 1 - ((75 - left_bound * step) / (float)step);      //calculating the coefficient for first term
    float r_coefficent = 1 - l_coefficent;                                  //calculating the coefficient for second term

    float quartile = (datas[left_bound] * l_coefficent) + (datas[right_bound] * r_coefficent);  //calculating the quartile

    return quartile;
}

