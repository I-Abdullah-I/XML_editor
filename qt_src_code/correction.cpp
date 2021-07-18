# include "correction.h"

std::string fix_and_save(std::string file_path) {
    minify(file_path);
    std::vector<Tag> arr;
    check_for_errors("minified.xml", arr);
    auto xml = fix_errors("minified.xml", arr);
    xml = prettify(xml);
    return xml;
}

bool is_found(std::stack<STag> s, string tag) {
    std::stack<STag> s_copy = s;
    std::vector<STag> temp_vec;
    while (!s_copy.empty()) {
        temp_vec.push_back(s_copy.top());
        s_copy.pop();
    }
    for (auto it = temp_vec.begin(); it != temp_vec.end(); it++) {
        // closing tag found => tag(s) above it was/were opened without being closed
        if (temp_vec[it - temp_vec.begin()].name == tag)
            return true;
    }
    // element not found => a tag was closed without being opened
    return false;
}

void minify (std::string file_path) {
    std::ifstream file(file_path);
    std::string line, min_output;
    while (std::getline(file, line)) {
        if (line != "") {
            // trimming whitespaces before '<'
            int pos = line.find("<");
            if (pos != -1)
                line = line.substr(pos);
            // trimming whitespaces before values
            pos = line.find_first_not_of(' ');
            if (pos != -1)
                line = line.substr(pos);
            min_output += line;
        }
    }
    // remove spaces after opening tag
    for(int i = 0; i < min_output.size(); i++) {
        if (min_output[i] == '>' && min_output[i + 1] == ' ') {
            int clos_tag_pos = i + 1, first_letter_pos;
            while (min_output[i + 1] == ' ')
                i++;
            first_letter_pos = i;
            std::string line0, line1;
            line0 = min_output.substr(0, clos_tag_pos);
            line1 = min_output.substr(first_letter_pos + 1);
            min_output = line0 + line1;
            i = i - (first_letter_pos - clos_tag_pos);
        }
    }
    // remove spaces before closing tag
    for(int i = min_output.size(); i > 0; i--) {
        if (min_output[i] == '<' && min_output[i - 1] == ' ') {
            int opening_tag_pos = i - 1, first_letter_pos;
            while (min_output[i - 1] == ' ')
                i--;
            first_letter_pos = i;
            std::string line0, line1;
            line0 = min_output.substr(0, first_letter_pos);
            line1 = min_output.substr(opening_tag_pos + 1);
            min_output = line0 + line1;
            i = i + (first_letter_pos - opening_tag_pos);
        }
    }
    // Create and open a text file
    ofstream MyFile("minified.xml");
    // Write to the file
    MyFile << min_output;
    // Close the file
    MyFile.close();
}

void merge (std::vector<Tag> temp_sorted_vector, std::vector<Tag> &sorted_vector, int const left, int const mid, int const right) {
    // determining size
    int left1 =left, right1 = mid, left2 = mid + 1, right2 = right;
    // initialize indexes for left and right arrays
    int left_arr_index = left1, right_arr_index = left2, merged_arr_index = left;
    while (left_arr_index <= right1 && right_arr_index <= right2) {
        if (temp_sorted_vector[left_arr_index].c_col < temp_sorted_vector[right_arr_index].c_col) {
            sorted_vector[merged_arr_index] = temp_sorted_vector[left_arr_index];
            left_arr_index++;
        }
        else if (temp_sorted_vector[left_arr_index].c_col == temp_sorted_vector[right_arr_index].c_col
            && temp_sorted_vector[left_arr_index].level < temp_sorted_vector[right_arr_index].level) {
            sorted_vector[merged_arr_index] = temp_sorted_vector[right_arr_index];
            right_arr_index++;
        }
        else if (temp_sorted_vector[left_arr_index].c_col == temp_sorted_vector[right_arr_index].c_col
            && temp_sorted_vector[left_arr_index].level > temp_sorted_vector[right_arr_index].level) {
            sorted_vector[merged_arr_index] = temp_sorted_vector[left_arr_index];
            left_arr_index++;
        }
        else {
            sorted_vector[merged_arr_index] = temp_sorted_vector[right_arr_index];
            right_arr_index++;
        }
        merged_arr_index++;
    }

    while (left_arr_index <= right1) {
        sorted_vector[merged_arr_index] = temp_sorted_vector[left_arr_index];
        left_arr_index++;
        merged_arr_index++;
    }

    while (right_arr_index <= right2) {
        sorted_vector[merged_arr_index] = temp_sorted_vector[right_arr_index];
        right_arr_index++;
        merged_arr_index++;
    }
}

void mergeSort(std::vector<Tag> full_vector, std::vector<Tag> &sorted_vector,
                 int const begin, int const end) {
    if (begin == end) {
        sorted_vector[begin] = full_vector[begin]; return;
    }
    int mid = (begin + end) / 2;
    std::vector<Tag> temp_sorted_vector(end + 1);

    mergeSort(full_vector, temp_sorted_vector, begin, mid);
    mergeSort(full_vector, temp_sorted_vector, mid + 1, end);
    merge(temp_sorted_vector, sorted_vector, begin, mid, end);
}

std::string fix_errors (std::string file_path, std::vector<Tag> error_array) {
    std::ifstream file(file_path);
    std::string line;
    std::getline(file, line);
    int shift_amount = 0;
    if (error_array.size()) {
        std::vector<Tag> sorted_error_array(error_array.size());
        // sorting error_array by c_col
        mergeSort(error_array, sorted_error_array, 0, error_array.size() - 1);
        for (auto it = sorted_error_array.begin(); it != sorted_error_array.end(); it++) {
            auto c_col = sorted_error_array[it - sorted_error_array.begin()].c_col;
            auto tag_name = sorted_error_array[it - sorted_error_array.begin()].tag;
            auto error_type = sorted_error_array[it - sorted_error_array.begin()].error_type;
            // con_missing_tag
            con_missing_tag(line, tag_name, error_type, c_col, shift_amount);
        }
    }
    ofstream MyFile("fixed.xml");
    MyFile << line;
    MyFile.close();
    return line;
}

void con_missing_tag(std::string &line, std::string tag_name, std::string error_type,
                    int c_col, int &shift) {
    // add / to tag_name
    tag_name = "</" + tag_name.substr(1);
    int tag_name_size = tag_name.size(), pos = 0;
    // cutting line at c_col
    auto line0 = line.substr(0, c_col + shift);
    auto line1 = line.substr(c_col + shift);
    line = line0 + tag_name + line1;
    if (error_type == "wrong closing tag") {
        line0 = line.substr(0, c_col + tag_name_size + shift);
        line1 = line.substr(c_col + tag_name_size + shift);
        pos = line1.find(">");
        line1 = line1.substr(pos + 1);
        line = line0 + line1;
        pos = pos + 1;
    }
    shift = shift + tag_name_size - pos;
}

std::string prettify (std::string xml) {
    int ind_index = 0, open_tag_count = 0, clos_tag_count = 0, i = 0;
    std::string line, type, prettified_xml = "";
    bool consecutive_closure = false, last_is_closure = false;
    ofstream myfile ("prettified.xml");
    while (xml.size() != 0) {
        int pos = xml.find(">");
        line = xml.substr(0, pos + 1) + "\n";
        type = line[1];
        if (last_is_closure && line[1] == '/') ind_index--;
        while (i != ind_index) {line = "    " + line; i++;} i = 0;
        myfile << line;
        prettified_xml = prettified_xml + line;
        xml = xml.substr(pos + 1);
        if (type != "?") {
            if (type == "/") { clos_tag_count++; last_is_closure = true; }
            else { open_tag_count++; last_is_closure = false; }
            ind_index = open_tag_count - clos_tag_count;
        }
        if (xml[0] != '<' && xml.size() != 0) {
            pos = xml.find("<");
            line = xml.substr(0, pos) + "\n";
            while (i != ind_index) {line = "    " + line; i++;} i = 0;
            ind_index--;
            myfile << line;
            prettified_xml = prettified_xml + line;
            xml = xml.substr(pos);
        }
    }
    myfile.close();
    return prettified_xml;
}

void check_for_errors(std::string file_path, std::vector<Tag> &error_array) {
    std::ifstream infile(file_path);
    std::string line, tag;
    std::stack<STag> S;
    std::vector<string> content;
    std::vector<Tag> alltags;
    std::vector<Tag>::iterator TagIt;
    int current_row = 1, level = 0;
    bool char_check_pass = false;
    struct SimTag current_parent = { "root",0,0 };


    while (std::getline(infile, line))
    {
        if(line != "") {
            for (int i = 0; i < line.length(); i++){
                // OPENING TAG and ((ignore first line))
                if (line[i] == '<' && line[i + 1] != '?' && line[i + 1] != '/') {
                    // save column value for opening tag
                    int current_col = i;
                    // account for the case where a child tag is opened but
                    // not closed
                    if(!S.empty() && S.top().type == "child"){
                        auto child = S.top();
                        S.pop();
                        alltags[TagIt - alltags.begin()].c_row = current_row;
                        alltags[TagIt - alltags.begin()].c_col = current_col;
                        alltags[TagIt - alltags.begin()].error_type = "tag is opened but not closed";
                        alltags[TagIt - alltags.begin()].closed = false;
                        alltags[TagIt - alltags.begin()].level = level;
                    }
                    // populate 'tag' with the opening tag
                    tag.push_back(line[i]);
                    i++;
                    while (line[i] != '>' && line[i] != ' ') {
                        tag.push_back(line[i]);
                        i++;
                    }
                    tag.push_back('>');
                    // push STag to stack
                    struct STag s_temp = { tag, "parent",current_row, current_col };

                    S.push(s_temp);
                    // add tag to alltags vector
                    struct Tag temp = { current_row, current_col, 0,0,0, false, tag,"none" };
                    alltags.push_back(temp);
                    // set tag iterator to last place in vector
                    TagIt = alltags.end() - 1;
                    tag.clear();
                    char_check_pass = true;
                    // jump to closing tag
                    string c_line = line;
                    c_line = c_line.substr(i);
                    i = c_line.find('>') + i;
                    // increase level
                    level++;
                }
                // CLOSING TAG
                else if (line[i] == '<' && line[i + 1] == '/') {
                    // popped_tag is used much in this scope
                    auto popped_tag = S.top();
                    // saving column vlaue
                    int current_col = i;
                    // populate 'tag' with closing tag without '/'
                    tag.push_back(line[i]);
                    i = i + 2;
                    while (line[i] != '>') {
                        tag.push_back(line[i]);
                        i++;
                    }
                    tag.push_back(line[i]);
                    // check if encountered tag name is the same as first tag in stack
                    std::string popped_tag_name = popped_tag.name;
                    if (tag != popped_tag_name) {
                        if(is_found(S, tag)) {
                            // closing tag found => tag(s) above it was/were opened without being closed
                            // set TagIt to coressponding Tag in alltags
                            TagIt = alltags.end() - 1;
                            while (popped_tag_name != tag) {
                                while (true) {
                                    auto array_tag = alltags[TagIt - alltags.begin()];
                                    if (array_tag.tag == popped_tag.name && array_tag.s_col == popped_tag.s_col && array_tag.s_row == popped_tag.s_row)
                                        break;
                                    TagIt--;
                                }
                                alltags[TagIt - alltags.begin()].c_row = current_row;
                                alltags[TagIt - alltags.begin()].c_col = current_col;
                                alltags[TagIt - alltags.begin()].closed = false;
                                alltags[TagIt - alltags.begin()].error_type = "tag is opened but not closed";
                                alltags[TagIt - alltags.begin()].level = level;
                                TagIt--;
                                // check if closed tag is a parent
                                if (popped_tag.type == "parent") {
                                    // update current_parent
                                    current_parent.name = popped_tag.parent.name;
                                    current_parent.s_row = popped_tag.parent.s_row;
                                    current_parent.s_col = popped_tag.parent.s_col;
                                    level--;
                                }
                                S.pop();
                                popped_tag = S.top();
                                popped_tag_name = popped_tag.name;
                            }
                            if (popped_tag_name == tag) {
                                TagIt = alltags.end() - 1;
                                while (true) {
                                    auto array_tag = alltags[TagIt - alltags.begin()];
                                    if (array_tag.tag == popped_tag.name && array_tag.s_col == popped_tag.s_col && array_tag.s_row == popped_tag.s_row)
                                        break;
                                    TagIt--;
                                }
                                alltags[TagIt - alltags.begin()].c_row = current_row;
                                alltags[TagIt - alltags.begin()].c_col = current_col;
                                alltags[TagIt - alltags.begin()].closed = true;
                                alltags[TagIt - alltags.begin()].level = level;
                                // check if closed tag is a parent
                                if (popped_tag.type == "parent") {
                                    // update current_parent
                                    current_parent.name = popped_tag.parent.name;
                                    current_parent.s_row = popped_tag.parent.s_row;
                                    current_parent.s_col = popped_tag.parent.s_col;
                                    level--;
                                }
                                S.pop();
                            }
                        }
                        else if (!is_found(S, tag) && popped_tag.type == "child"){
                            // close the tag that corresponds to popped_tag_name
                            TagIt = alltags.end() - 1;
                            while (true) {
                                auto array_tag = alltags[TagIt - alltags.begin()];
                                if (array_tag.tag == popped_tag.name && array_tag.s_col == popped_tag.s_col && array_tag.s_row == popped_tag.s_row) {
                                    alltags[TagIt - alltags.begin()].c_row = current_row;
                                    alltags[TagIt - alltags.begin()].c_col = current_col;
                                    alltags[TagIt - alltags.begin()].closed = false;
                                    alltags[TagIt - alltags.begin()].error_type = "wrong closing tag";
                                    alltags[TagIt - alltags.begin()].level = level;
                                    break;
                                }
                                TagIt--;
                            }
                            S.pop();
                        }
                    }
                    // tag is closed normally
                    else {
                        // finding alltags memmber to be updated
                        TagIt = alltags.end() - 1;
                        while (alltags[TagIt - alltags.begin()].tag != popped_tag.name)
                            TagIt--;
                        alltags[TagIt - alltags.begin()].closed = true;
                        alltags[TagIt - alltags.begin()].c_row = current_row;
                        alltags[TagIt - alltags.begin()].c_col = current_col;
                        alltags[TagIt - alltags.begin()].level = level;
                        // check if closed tag is a parent
                        if (popped_tag.type == "parent") {
                            // update current_parent
                            current_parent.name = popped_tag.parent.name;
                            current_parent.s_row = popped_tag.parent.s_row;
                            current_parent.s_col = popped_tag.parent.s_col;
                            level--;
                        }
                        S.pop();
                    }
                    tag.clear();
                }
                // check for characters after opening tag
                else if (char_check_pass) {
                    while (i < line.length()){
                        // current STag is a parent
                        if (line[i + 1] == '<' && line[i] == ' '){
                            auto popped_tag = S.top();
                            S.pop();
                            popped_tag.type = "parent";
                            popped_tag.parent = current_parent;
                            S.push(popped_tag);
                            current_parent.name = popped_tag.name;
                            current_parent.s_row = popped_tag.s_row;
                            current_parent.s_col = popped_tag.s_col;
                            char_check_pass = false;
                            level++;
                            break;
                        }
                        else if (line[i] != ' '){
                            auto popped_tag = S.top();
                            S.pop();
                            popped_tag.type = "child";
                            popped_tag.parent = current_parent;
                            S.push(popped_tag);
                            char_check_pass = false;
                            level--;
                            break;
                        }
                        else if (line[i] == ' ') i++;
                    }
                }
            }

        }
        current_row++;
    }
    for (auto it = alltags.begin(); it != alltags.end(); it++){
        auto array_tag = alltags[it - alltags.begin()];
        if (array_tag.closed == false) {
            cout << "Tag name: " << array_tag.tag
                 << ", starting row and col: " << array_tag.s_row << "-" << array_tag.s_col
                 << ", ending row and col: " << array_tag.c_row << "-" << array_tag.c_col
                 << ", error type: " << array_tag.error_type << endl;
            error_array.push_back(array_tag);
        }
    }
    return;

}
