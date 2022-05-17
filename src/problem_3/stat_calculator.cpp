#include "stat_calculator.h"

float StatCalculator::mean(const List<float> &data) {
    float sum = 0;

    if(data.size() == 0){
        return sum;
    }

    for(size_t i = 0; i < data.size(); i++){
        sum += data[i];
    }

    return sum/data.size();
}

/*
 * based on https://www.calculatorsoup.com/calculators/statistics/percentile-calculator.php
 */
void StatCalculator::percentiles(List<float> &data,
                                 int percentile_target_step,
                                 Map<int, float> &result_map) {

    //sort the data first
    sort(data);

    int percentile = 0;
    //create a loop to increment the percentile by the target step
    while(percentile <= 100) {
        float rank = ((float)(percentile)/100 *(data.size() - 1) );

        //if the rank is an integer
        if(floor(rank) == rank){
            result_map.put(percentile, data[rank]);
        }
        //if it's not an integer use the formula to calculate the number
        else{
            float fractionalRank = rank - floor(rank);
            float inBetween = data[ceil(rank)] - data[floor(rank)];
            float finalNumber = data[floor(rank)] + (fractionalRank * inBetween);
            result_map.put(percentile, finalNumber);
        }
        percentile += percentile_target_step;
    }

}

void StatCalculator::sort(List<float> &data) {
    size_t length = data.size();
    if (length < 2) {
        return;
    }
    for (size_t i = 0; i < length; i++) {
        for (size_t j = 0; j < length - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                swap(data, j, j + 1);
            }
        }
    }
}

void StatCalculator::swap(List<float> &data, size_t i, size_t j) {
    float tmp = data[i];
    data[i] = data[j];
    data[j] = tmp;
}