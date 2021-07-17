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