#include <iostream>
#include <stdio.h>
#include "book.h"

using namespace std;
                                                  //getters and setters
string book::get_bookID(){
     return this->bookID;
}s
string book::get_author(){
     return this->author;
}
string book::get_isbn(){
     return this->isbn;
}
string book::get_isbn13(){
     return this->isbn13;
}
string book::get_lang_code(){
     return this->language_code;
}
string book::get_num_pages(){
     return this->num_pages;
}
string book::get_publication_date(){
     return this->publciation_date;
}
string book::get_publisher(){
     return this->publisher;
}
string book::get_title(){
     return this->title;
}
string book::get_text_review(){
     return this->text_review;
}
string book::get_ratings_count(){
     return this->ratings_count;
}
double book::get_rating(){
    return this->average_rating;
}

void book::set_author(string author){
     this->author = author;
}
void book::set_bookID(string id){
     this->bookID = id;
}
void book::set_date(string date){
     this->publciation_date = date;
}
void book::set_isbn13(string isbn13){
     this->isbn13 = isbn13;
}
void book::set_isbn(string isbn){
     this->isbn = isbn;
}
void book::set_lang_code(string lang){
     this->language_code = lang;
}
void book::set_num_page(string num_pages){
     this->num_pages = num_pages;
}
void book::set_publisher(string publisher){
     this->publisher = publisher;
}
void book::set_rating(double ratings ){
     this->average_rating = ratings;
}
void book::set_ratings_count(string ratings_count){
     this->ratings_count = ratings_count;
}
void book::set_text_review(string text_review){
     this->text_review = text_review;
}
void book::set_title(string title){
     this->title = title;
}