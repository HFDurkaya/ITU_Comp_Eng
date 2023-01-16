#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "book.h"

using namespace std;

int swap_counter = 0;                   //counter to hold how many swap operation is made
int partition_counter = 0;              //counter to hold how many partition operation is made

int partition(vector<book*>& book_list, int low, int high){                 //partition function
    
    int i = low;
    int j = low;

    partition_counter++;                //partition counter is updated whenever this function is called
    
    double pivot = book_list[high]->get_rating();
    
    while(j >= i){
        
        if(book_list[i]->get_rating() <= pivot && book_list[j]->get_rating() <= pivot){     
            j++;
            i++;
        }

        if(book_list[j]->get_rating() > pivot){                 
            
            j++;

            swap(book_list[i],book_list[j]);
            swap_counter++;                         //swap counter update
            

            if(book_list[i]->get_rating() <= pivot)
                i++;

            if((j+1) == high){
                swap(book_list[i], book_list[high]);
                swap_counter++;                     //swap counter update
                break;
            }                        
        }

        if(j == high){
            swap(book_list[i], book_list[high]);
            swap_counter++;                         //swap counter update
            break;
        }
    }    
    return i;
}

void quicksort_1(vector<book*>& book_list, int head, int tail){

    if(head >= tail){
        return;
    }

    int border = partition(book_list, head, tail);
    
    quicksort_1(book_list, head, (border-1));                   //quicksort for lower part
    quicksort_1(book_list, (border + 1), tail);                 //quicksort for upper part

}

int main(){

    fstream fin;

    fin.open("books.csv", ios::in);

    vector<book*> book_list;                                    //vector that holds book datas

    int counter = 0;                                            //counter for how many books there are

    clock_t time_req;                                           //clock to calculate execution time
    
    string line;

    string bookID;                                              //attributes that we will be loaded from csv
    string title;
    string author;
    string average_rating;
    double rating;
    string isbn;
    string isbn13;
    string language_code;
    string num_pages;
    string ratings_count;
    string text_review;
    string publciation_date;
    string publisher;


    getline(fin, line);                                     //removing the first line with bookID Tıtle and etc.

    while(fin.good()){
    //for(int i = 0; i < 5564; i++){                        //for half of data
    //for(int i = 0; i < 2782; i++){                        //for quarter of data

        getline(fin, bookID,',');                           //loading the attributes from csv
        getline(fin, title,',');
        getline(fin, author,',');
        getline(fin, average_rating,',');        

        rating = stod(average_rating);                      // string to double conversion for sorting

        getline(fin, isbn,',');
        getline(fin, isbn13,',');
        getline(fin, language_code,',');
        getline(fin, num_pages,',');
        getline(fin, ratings_count,',');
        getline(fin, text_review,',');
        getline(fin, publciation_date,',');
        getline(fin, publisher);

        book* new_book = new(book);                         // creation of a new book node
        new_book->set_rating(rating);

        new_book->set_author(author);                       //setting the new books attributes
        new_book->set_bookID(bookID);
        new_book->set_date(publciation_date);
        new_book->set_isbn13(isbn13);
        new_book->set_isbn(isbn);
        new_book->set_lang_code(language_code);
        new_book->set_num_page(num_pages);
        new_book->set_publisher(publisher);
        new_book->set_ratings_count(ratings_count);
        new_book->set_text_review(text_review);
        new_book->set_title(title);

        book_list.push_back(new_book);                      // pushing the new book node to vector
        counter++;                                          //counter update

    }

    //for(int a = 0; a < counter; a++){                     //for writing the books unsorted
    //    cout<<book_list[a]->get_rating()<<endl;
    //}
    
    time_req = clock();

    quicksort_1(book_list, 0, (counter-1));

    time_req = clock() - time_req;                          //calculation of execution time

    cout << "Running time of quicksort1 with full data: " << (float)time_req/CLOCKS_PER_SEC << " seconds" << endl;

    cout<<"Number of partitions: "<< partition_counter<<endl;
    cout<<"Number of swaps: "<< swap_counter<<endl;    

    //for(int a = 0; a < counter; a++){                     //for writing the books sorted
    //    cout<<book_list[a]->get_rating()<<endl;
    //}

    ofstream my_file("sorted_books_full.csv");              // writing to csv file full attributes

    for(int b = 0; b < counter; b++){
        my_file << book_list[b]->get_bookID()<<",";
        my_file << book_list[b]->get_title()<<","; 
        my_file << book_list[b]->get_author()<<","; 
        my_file << book_list[b]->get_rating()<<","; 
        my_file << book_list[b]->get_isbn()<<","; 
        my_file << book_list[b]->get_isbn13()<<","; 
        my_file << book_list[b]->get_lang_code()<<","; 
        my_file << book_list[b]->get_num_pages()<<","; 
        my_file << book_list[b]->get_ratings_count()<<","; 
        my_file << book_list[b]->get_text_review()<<","; 
        my_file << book_list[b]->get_publication_date()<<",";
        my_file << book_list[b]->get_publisher()<<"\n";     
    }
    my_file.close();
    
    ofstream myFile("sorted_books.csv");                        // writing to csv file with only id and rating

    for(int c = 0; c < counter; c++){
        myFile << book_list[c]->get_bookID() << " --> ";
        myFile << book_list[c]->get_rating() << "\n";
    }

    myFile.close();
}