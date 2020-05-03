#include "Filter.h"

FilterSMA::FilterSMA(size_t filterSize) :
    filterSize(filterSize),
    dataBuffer(filterSize, 0.0f)
{
    MBED_ASSERT(filterSize);
    filterFactor = 1.0f / filterSize;
}

/*
calculate filter value for a new input value
*/
void FilterSMA::calculate(float input)
{
    filterValue += filterFactor * (input - dataBuffer[currentElement]);
    dataBuffer[currentElement] = input;
    currentElement = (currentElement + 1) % filterSize;
}