#pragma once
#include "Tree.h"
#include <fstream>   // file stream to read file
#include "Tree.h"

#include <sstream>   // to store file in string buffer less than 50k
using namespace std;
Tree* convert_2_tree(string path);
void add_next(string s);	//insert node of tag // open tag may contain values or attributes
void close_tag();	//detect close tag and move to new node
void tag_value(string s);	//add the tag value without attributes
string* prettify_json(std::string line);
void indentaion(int indentation_index, std::string& line);

string* convert2jason(string path);
