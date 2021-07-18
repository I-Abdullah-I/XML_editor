#include "XMLfunctions.h"

Tree *XML=new Tree;
string* convert2jason(string path){
    convert_2_tree(path);
    string*jason_text=XML->convert_jason(XML->getRoot());

    jason_text= prettify_json(*jason_text);
    return jason_text;
}
Tree* convert_2_tree(string path){
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    string xmlString = buffer.str(); // convert buffer to string

    // i points to start
    // j tag size counter
    // text parser
    for (int i = 0; i < xmlString.length(); i++) {

        // space ,newline ,and tab ignore "outside tag"
        if (xmlString[i] == ' ' || xmlString[i] == '\n' || xmlString[i] == '\t') continue; //continue to move the starting cruser i

        //open tag detection
        int j = 1; // tag length
        if (xmlString[i] == '<' && xmlString[i + 1] != '/') {
            while (xmlString[i + j] != '>') j++;  // keep counting till it reach '>'
            add_next(xmlString.substr(i, j + 1));
            i += j;
            continue;
        }
        //close tag detection
        if (xmlString[i] == '<' && xmlString[i + 1] == '/') {
            while (xmlString[i + j] != '>') j++;  // keep counting till it reach '>'
            close_tag(); // call closing tag
            i += j;
            continue;
        }
        //tag normal content "tag_value"
        while (xmlString[i + j] != '<' && xmlString[i + j] != '>' && xmlString[i + j] != '\n') j++;
        //we can remove the space and tab and new line as they may contain it
            //xmlString[i+j] != ' ' &&
            //xmlString[i+j] != '\t') // take all the values that doesn't include privious items
        tag_value(xmlString.substr(i, j));  // add previosu node value
        i += j - 1;
        continue;
    }

    return XML;
}
void add_next(string s)
{
    string type, val;
    // first sending tag
    int i = 1;
    while (s[i] != ' '&&i<s.size()-1)i++;
    type = s.substr(1, i - 1);
    XML->add2tree(type, "");  //send tag type

    // special case
    // adding variables as sons
    int j;// temp start
    while (i < s.size()-1) {
        // skip space
        while (s[i] == ' ')i++;
        //letter found
        j = i;
        //count letters
        while (s[i] != '=' && s[i] != ' ')i++;
        type = s.substr(j, i - j);
        // skip space and '='
        while (s[i] == ' '||s[i]=='=')i++;
        //letter found or " is found
        if (s[i]=='"'){
            i++;
            j = i;
            while (s[i] != '"')i++;
            val = s.substr(j, i - j);
            i++;//skip '"'
        }
        XML->add2tree(type, val);
        XML->end_chain();
    }
    //end special case
}
void close_tag()
{
    XML->end_chain();
}

void tag_value(string s)
{
    XML->add_value(s);

}

string* prettify_json(std::string line) {
    std::string prettified_line, line0, line1;
    int indentation_index = 0;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '{' || line[i] == '[') {
            line0 = line.substr(0, i + 1);
            line = line.substr(i + 1);
            line0 = line0 + "\n";
            indentaion(indentation_index, line0);
            prettified_line = prettified_line + line0;
            indentation_index++;
            i = -1;
        }
        else if (line[i] == ',') {
            line0 = line.substr(0, i + 1);
            line = line.substr(i + 1);
            line0 = line0 + "\n";
            indentaion(indentation_index, line0);
            prettified_line = prettified_line + line0;
            i = -1;
        }
        else if (line[i] == '}' && line[i + 1] == ',') {
            // before },
            line0 = line.substr(0, i);
            line = line.substr(i);
            line1 = line.substr(0, 2);
            line = line.substr(2);
            line0 = line0 + "\n";
            line1 = line1 + "\n";
            indentaion(indentation_index, line0);
            prettified_line = prettified_line + line0;
            indentation_index--;
            indentaion(indentation_index, line1);
            prettified_line = prettified_line + line1;
            i = -1;
        }
        else if (line[i] == '}' || line[i] == ']') {
            line0 = line.substr(0, i + 1);
            if (line0.size() == 1) {
                indentation_index--;
                line = line.substr(i + 1);
                line0 = line0 + "\n";
                indentaion(indentation_index, line0);
                prettified_line = prettified_line + line0;
                i = -1;
            }
            else {
                line0 = line.substr(0, i);
                line = line.substr(i);
                line1 = line.substr(0, 1);
                line = line.substr(1);
                line0 = line0 + "\n";
                line1 = line1 + "\n";
                indentaion(indentation_index, line0);
                prettified_line = prettified_line + line0;
                indentation_index--;
                indentaion(indentation_index, line1);
                prettified_line = prettified_line + line1;
                i = -1;
            }
        }
    }
    string* doc_mistake=new string;
    * doc_mistake= prettified_line;
    return doc_mistake;
//    std::cout << prettified_line << std::endl;
}
void indentaion(int indentation_index, std::string& line) {
    int i = 0;
    while (i < indentation_index) {
        line = "    " + line;
        i++;
    }
}
