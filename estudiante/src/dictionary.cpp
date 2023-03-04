//
// Created by jdrg on 8/9/21.
//

#include <string>
#include <vector>
#include <utility>
#include <set>
#include "dictionary.h"
#include <cmath>

///////////////////////////////////////////////////////////////////////////////
//                             Private functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::node Dictionary::findLowerBoundChildNode(char character, Dictionary::node current) {
  node prev_child, curr_child = current.left_child();

  for (; !curr_child.is_null() && (*curr_child).character <= character; curr_child = curr_child.right_sibling()){
    prev_child = curr_child;
    if ((*curr_child).character == character) {
      return curr_child;
    }
  }
  if (!prev_child.is_null()) {
    return prev_child;
  }
  return current;
}

Dictionary::node Dictionary::insertCharacter(char character, Dictionary::node current) {
  node insertion_position = findLowerBoundChildNode(character, current);
  if (insertion_position == current){
    this->words.insert_left_child(current, char_info(character));
    return insertion_position.left_child();
  } else if ((*insertion_position).character != character){
    this->words.insert_right_sibling(insertion_position, char_info(character));
    return insertion_position.right_sibling();
  } else {
    return insertion_position;
  }
}

int Dictionary::getOccurrences(node curr_node, char c){
    int totalOcurrences = 0;
    if (toupper((curr_node).operator*().character) == c) {
        totalOcurrences++;
    }
    if(!curr_node.left_child().is_null()) {
        totalOcurrences += getOccurrences(curr_node.left_child(),c);
    }

    if (!curr_node.right_sibling().is_null()) {
        totalOcurrences += getOccurrences(curr_node.right_sibling(),c);
    }

    return totalOcurrences;
}

std::pair<int, int> Dictionary::getTotalUsages(node curr_node, char c){

    pair<int,int> totalUsages(0,0);
    pair<int,int> leftChild;
    pair<int,int> rightSibling;

    if(!curr_node.left_child().is_null())
        leftChild = getTotalUsages(curr_node.left_child(),c);

    if(!curr_node.right_sibling().is_null())
        rightSibling = getTotalUsages(curr_node.right_sibling(),c);

    totalUsages.first = leftChild.first + rightSibling.first;
    totalUsages.second = leftChild.second + rightSibling.second;

    if(toupper((curr_node).operator*().character) == c)
        totalUsages.first += leftChild.second;

    if(curr_node.operator*().valid_word){
        totalUsages.second++;
        if(toupper((curr_node).operator*().character) == c)
            totalUsages.first++;
    }

    return totalUsages;

}

///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::Dictionary() {
  this->words.set_root(char_info());
  this->total_words = 0;
}

Dictionary::Dictionary(const Dictionary &other) {
  this->words = other.words;
  this->total_words = other.total_words;
}

Dictionary::~Dictionary() {
  this->words.clear();
}

bool Dictionary::exists(const std::string & word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->findLowerBoundChildNode(word[i], current);
    if ((*current).character != word[i]) {
      return false;
    }
  }

  return (*current).valid_word;
}

bool Dictionary::insert(const std::string &word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->insertCharacter(word[i], current);
  }

  if (!(*current).valid_word) {
    (*current).valid_word = true;
    this->total_words++;
    return true;
  }

  return false;
}

bool Dictionary::erase(const std::string & val){
  node current = this->words.get_root();
  for (int i = 0; i < val.size(); ++i){
    current = this->findLowerBoundChildNode(val[i], current);
    if ((*current).character != val[i]) {
      return false;
    }
  }
  if ((*current).valid_word){
    (*current).valid_word = false;
    this->total_words--;
    return true;
  }
  return false;
}

Dictionary &Dictionary::operator=(const Dictionary &dic){
  if (this != &dic){
    this->words.clear();
    this->words = dic.words;
    this->total_words = dic.total_words;
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
//                               I/O overload                                //
///////////////////////////////////////////////////////////////////////////////

/*std::ostream& operator<<(std::ostream &os, const Dictionary &dict){
  for(Dictionary::iterator it = dict.begin();it != dict.end(); ++it){
    os << *it << std::endl;
  }
  return os;
}*/

std::istream& operator>>(std::istream &is, Dictionary &dict){
  std::string curr_word;
  while (getline(is, curr_word)){
    dict.insert(curr_word);
  }
  return is;
}

///////////////////////////////////////////////////////////////////////////////
//                            Recursive counters                             //
///////////////////////////////////////////////////////////////////////////////

int Dictionary::getOccurrences(const char c){
    return getOccurrences(this->words.get_root(), c);
}

int Dictionary::getTotalUsages(const char c){
    return getTotalUsages(this->words.get_root(), c).first;
}

///////////////////////////////////////////////////////////////////////////////
//                                 Iterator                                  //
///////////////////////////////////////////////////////////////////////////////



Dictionary::iterator::iterator() {
    this->curr_word="";
    this->iter = tree<char_info>::const_preorder_iterator();
}


Dictionary::iterator::iterator(tree<char_info>::const_preorder_iterator iter) {
    this->curr_word ="";
    this->iter = iter;
}


std::string Dictionary::iterator::operator*() {
    return curr_word;
}


Dictionary::iterator &Dictionary::iterator::operator++() {


    if (iter.get_level() == 0) {
        curr_word = "";
    }

    int level = iter.get_level();
    string pas_word=this->curr_word;
    while (this->iter.operator*().valid_word == false || pas_word == this->curr_word){

        level = this->iter.get_level();
        ++iter;
        if (level == iter.get_level()){
            this->curr_word.back() = this->iter.operator*().character;
        }
        else if (level < iter.get_level()){
            this->curr_word += this->iter.operator*().character;
        }
        else if(level > iter.get_level()){
            this->curr_word.pop_back();
            while(level != iter.get_level()){
                this->curr_word.pop_back();
                level--;
            }
            if(this->iter.get_level()!=0)
                this->curr_word.push_back(this->iter.operator*().character);
            else return *this;
        }


    }
    return *this;

}


bool Dictionary::iterator::operator==(const iterator &other) {
    return this->iter == other.iter;
}


bool Dictionary::iterator::operator!=(const iterator &other) {
    return this->iter != other.iter;
}


Dictionary::iterator Dictionary::begin() const {
    iterator i = words.cbegin_preorder();
    ++i;
    return i;
}


Dictionary::iterator Dictionary::end() const {
    iterator i = words.cend_preorder();
    return i;
}

///////////////////////////////////////////////////////////////////////////////
//                            Letters Iterator                               //
///////////////////////////////////////////////////////////////////////////////

/*
Dictionary::possible_words_iterator Dictionary::possible_words_begin(vector<char> available_characters) const {

}

Dictionary::possible_words_iterator Dictionary::possible_words_end() const {
}

Dictionary::possible_words_iterator::possible_words_iterator():available_letters(), current_node(), current_word(""){
}

Dictionary::possible_words_iterator::possible_words_iterator(node current_node, vector<char> available_letters){


}

Dictionary::possible_words_iterator::possible_words_iterator(const possible_words_iterator &other){}



Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator=(const Dictionary::possible_words_iterator &other){}



bool Dictionary::possible_words_iterator::operator==(const Dictionary::possible_words_iterator &other) const {


}

bool Dictionary::possible_words_iterator::operator!=(const Dictionary::possible_words_iterator &other) const {
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator++() {

}

std::string Dictionary::possible_words_iterator::operator*() const {

}*/
