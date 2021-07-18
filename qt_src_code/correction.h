#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <algorithm>
#include <cstdio>

using namespace std;

struct Tag {
    int s_row, s_col, c_row, c_col, level;
    bool closed;
    string tag, error_type;
};

struct SimTag {
    string name;
    int s_row, s_col;
};

struct STag {
    string name, type;
    int s_row, s_col;
    SimTag parent;
};

// functions prototypes
bool is_found(std::stack<STag> s, string tag);
void minify (std::string file_path);
void mergeSort(std::vector<Tag> V, std::vector<Tag> &sorted_vector, int const begin, int const end);
void merge (std::vector<Tag> temp_sorted_vector, std::vector<Tag> &sorted_vector, int const left,
            int const mid, int const right);
std::string fix_errors (std::string file_path, std::vector<Tag> error_array);
void con_missing_tag(std::string &line, std::string tag_name, std::string error_type,
                    int c_col, int &shift);
std::string prettify (std::string xml);

// GUI functions
void check_for_errors(std::string file_path, std::vector<Tag> &errors);
std::string fix_and_save(std::string file_path);

