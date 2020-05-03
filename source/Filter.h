#ifndef FILTER_H_
#define FILTER_H_

#include <mbed.h>
#include <vector>

/*
Simple Moving Average filter
*/
class FilterSMA
{
public:
    FilterSMA(size_t filterSize);
    void calculate(float input);
    float getValue(void) const { return filterValue; }
private:
    size_t filterSize;                      // size of the averaging buffer
    std::vector<float> dataBuffer;          // data buffer for filter calculations
    size_t currentElement{0};               // index of the current element
    float filterValue{0.0f};                // current filter value
    float filterFactor{0.0f};               // reciprocal of filter size for calculation purposes
};


#endif /* FILTER_H_ */