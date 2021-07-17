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