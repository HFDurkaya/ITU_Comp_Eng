#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

class book{                             //class definition to hold values of csv as a packet

private:

    string bookID;                      //attributes of book class which we got from csv file
    string title;
    string author;
    double average_rating;
    string isbn;
    string isbn13;
    string language_code;
    string num_pages;
    string ratings_count;
    string text_review;
    string publciation_date;
    string publisher;


public:
    
    book() = default;                           //constructor

    string get_bookID();                        //getters for attributes
    string get_title();
    string get_author();
    double get_rating();
    string get_isbn();
    string get_isbn13();
    string get_lang_code();
    string get_num_pages();
    string get_ratings_count();
    string get_text_review();
    string get_publication_date();
    string get_publisher();

    void set_bookID(string id);                 //setter for attributes
    void set_title(string title);
    void set_author(string author);
    void set_rating(double average_rating);
    void set_isbn(string isbn);
    void set_isbn13(string isbn13);
    void set_lang_code(string language_code);
    void set_num_page(string num_pages);
    void set_ratings_count(string ratings_count);
    void set_text_review(string text_review);
    void set_date(string publciation_date);
    void set_publisher(string publisher);
};

