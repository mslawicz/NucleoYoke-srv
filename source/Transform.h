#ifndef TRANSFORM_H_
#define TRANSFORM_H_

template<typename iType, typename oType> oType scale(iType iMin, iType iMax, iType input, oType oMin, oType oMax, bool limit = true)
{
    auto result = static_cast<oType>(1.0f * (input-iMin) / (iMax-iMin) * (oMax-oMin) + oMin);
    if(limit)
    {
        if(result < oMin)
        {
            result = oMin;
        }
        else if(result > oMax)
        {
            result = oMax;
        }
    }
    return result;
}

#endif /* TRANSFORM_H_ */