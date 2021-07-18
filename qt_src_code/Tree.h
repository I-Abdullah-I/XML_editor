#pragma once

#include <iostream>
#include<vector>
#include<iterator> 
using namespace std;

class Node
{
	Node* parent;
	string type;
	string val;
	vector<Node*> Sons;
	
public:
	Node() { type = ""; val = ""; parent = NULL; }
	Node(string t) { type = t;  parent = NULL; }
	Node(string t, string v, Node* pa) { type = t; val = v; parent = pa; }
	string get_type() { return type; }
	string get_val() { return val; }
	void set_type(string t) { type = t; }
	void set_val(string v) { val = v; }
	int get_sons_num() { return Sons.size(); }  //returns number of child_nodes in node
	Node* get_first() { return Sons[0];}			 //returns pointer to first child in sons victor
	void set_first(Node* t) { Sons[0]=t; }			//store pointer to first child in sons victor
	void replace_Node(int i, Node* t) { Node* temp = Sons[i]; Sons[i] = t; delete temp; }	//change child with order "i" to a new pointer to passed child pointer 

	int find_son(Node* t) {    //returns indiactaor to the son order in sons vector
		for (int i = 0; i < this->get_sons_num(); ++i)
			if (t == this->get_son(i))return i;
			else return -1;
        return -1;
	}
	int get_my_order() { return parent->find_son(this); }
	Node* get_son(int i) { if (i < 0)return NULL; return Sons[i]; }
	void add_son(Node* t) { Sons.push_back(t);}		//insert pointer to child in sons vector 
	void remove_son(int i) { delete Sons[i]; Sons[i] = NULL; }

	Node* get_parent() { return parent; }
	void set_parent(Node* n) { parent = n; }
};


class Tree
{
	Node* root;
	Node* current;
    string* jasonText=new string;
public:
	Tree() { root = new Node(); current = NULL; }
	Tree(string type, string val) { root = new Node(type, val,NULL); current = NULL;}

	Node* getRoot() { return root; }

	void add2tree(string type, string val) // insert in tree in chain sequence
	{
		//case tree is empty first element to be inserted
		if (current == NULL) {
			current = root;
			current->set_type(type);
		}
		else {// add son or variable as son
			Node* temp = new Node(type,val, current);
			current->add_son(temp);
			current = temp;
		}
	}
	void add_value(string val) {
		current->set_val(val);
	}
	void end_chain() { current = current->get_parent(); }  //to go to the father and end chain
	
	// count number of leaf nodes (the operands)
	int countLeaves(Node* t)
	{
		if (t == NULL)return 0;

		if ((t->get_sons_num()==0)) return 1;

		int sum = 0;
		for (int it = 0; it < t->get_sons_num(); ++it) {
			sum += countLeaves(t->get_son(it));
		}
		return sum;
	}
	// count number of nodes inside the tree
	int count(Node* t)
	{
		if (t == NULL)return 0;
		else if (t->get_sons_num() == 0) return 0;
		int sum = 0;
		for (int it = 0; it < t->get_sons_num(); ++it) {
			sum += count(t->get_son(it));
		}
		return 1 +sum;
	}

	void Print_pre_order(Node* rootptr) {
		if (rootptr == NULL)return;
		cout << "\"" << rootptr->get_type() << "\": \"" << rootptr->get_val() << "\"\n";
		for (int i = 0; i < rootptr->get_sons_num(); i++)
			Print_pre_order(rootptr->get_son(i));
	}
	void Print_jason(Node* rootptr) {
		if (rootptr == NULL)return ;//stop condition

		bool flag = false;

		//first curly bracet
		if ( rootptr->get_parent() == NULL)cout << "{";
		
		if (rootptr->get_val().empty())
			cout << "\"" << rootptr->get_type() << "\": ";
		// if this is the first node
		else {
			if (rootptr->get_sons_num() == 0) {
				cout << "\"" << rootptr->get_type() << "\": " << "\"" << rootptr->get_val() << "\"";
			}
			else {
				cout << "\"" << rootptr->get_type() << "\": " << "{\"#text\": " << "\"" << rootptr->get_val() << "\",";
				flag = true;
			}
		}
		
		for (int i = 0; i < rootptr->get_sons_num(); i++) {
			if (i == 0 && flag == false) {
				//same types from start
				if (rootptr->get_son(0)->get_type() == rootptr->get_son(1)->get_type())
					cout << "[";
				cout << "{";  // diffrent types
			}
			Print_jason(rootptr->get_son(i));
			if (i == rootptr->get_sons_num()-1)cout << "}";
			else cout << ",";
		}
	}
    string* convert_jason(Node* rootptr) {
            if (rootptr == NULL)return NULL;//stop condition

            bool flag = false;

            //first curly bracet
            if (rootptr->get_parent() == NULL)*jasonText+= "{";

            if (rootptr->get_val().empty())
                *jasonText += "\"" + rootptr->get_type() + "\": ";
            // if this is the first node
            else {
                if (rootptr->get_sons_num() == 0) {
                    *jasonText += "\"" + rootptr->get_type() + "\": " + "\"" + rootptr->get_val() + "\"";
                }
                else {
                    *jasonText += "\"" + rootptr->get_type() + "\": " + "{\"#text\": " + "\"" + rootptr->get_val() + "\",";
                    flag = true;
                }
            }

            for (int i = 0; i < rootptr->get_sons_num(); i++) {
                if (i == 0 && flag == false) {
                    //same types from start
                    if(rootptr->get_sons_num()>1)
                        if (rootptr->get_son(0)->get_type() == rootptr->get_son(1)->get_type())
                            *jasonText += "[";
                   *jasonText += "{";  // diffrent types
                }
                convert_jason(rootptr->get_son(i));
                if (i == rootptr->get_sons_num() - 1)*jasonText += "}";
                else *jasonText += ",";
            }
            return jasonText;
        }
};
//{"synset": {"id": "a00001740","type": "a","lex_filenum": {"#text": "0123","book": {"id": "bk103","author": "Corets, Eva","title": "Maeve Ascendant","genre": "Fantasy","price": "5.95 ","publish_date": "2000 - 11 - 17 "}},"word": {"#text": "able","lex_id": "0"},

//"pointer": [{"#text" : "Attribute","-refs": "n05200169 n05616246"},{"#text" : "Derivationally related form","-refs": "n05616246 n05200169","-source" : "1","-target" : "1"},{"-refs": "a00002098","-source" : "1","-target" : "1","#text" : "Antonym"}],"def": "(usually followed by `to') having the necessary means or skill or know-how or authority to do something","example" : ["able to swim","she was able to program her computer","we were at last able to buy a car","able to get a grant for the project"]},"#omit-xml-declaration": "yes"}
//"pointer": {"#text": "Attribute","refs": "n05200169 n05616246"},"pointer": {"#text": "Derivationally related form","refs": "n05616246 n05200169","source": "1","target": "1"},"pointer": {"#text": "Antonym","refs": "a00002098","source": "1","target": "1"},"def": "(usually followed by `to') having the necessary means or skill or know-how or authority to do something","example": "able to swim","example": "she was able to program her computer","example": "we were at last able to buy a car","example": "able to get a grant for the project"}

//{"synset": {"id": "a00001740","type": "a","lex_filenum": {"#text": "0123","book": {"id": "bk103","author": "Corets, Eva","title": "Maeve Ascendant","genre": "Fantasy","price": "5.95 ","publish_date": "2000 - 11 - 17 "}},"word": {"#text": "able","lex_id": "0"},
