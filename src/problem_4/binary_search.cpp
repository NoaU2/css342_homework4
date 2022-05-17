#include "binary_search.h"

int binary_search_helper(int *pInt, int target, int i, int length);

int binary_search(int *data, int length, int target) {

    if(length == 0 || data == nullptr){ //nullpointer check
        return -1;
    }
    return binary_search_helper(data, target, 0, length);
}

int binary_search_helper(int *data, int target, int start, int end) {
    if(end < start){ //if the data isn't found
        return -1;
    }

    int mid = (start + end)/2;
    if(data[mid] == target){
        return mid;
    }

    if(data[mid] > target){
        return binary_search_helper(data, target, start, end - 1);
    }

    else{
        return binary_search_helper(data, target, start + 1, end);
    }
}