#include "pricingutil.h"


PricingUtil::PricingUtil() {
   
}

float PricingUtil::calcVal(float prevPrice, float interest, float oleoConstant) {
    val = (prevPrice * (0.9f + interest)) * oleoConstant;
    return val;
}

float PricingUtil::getVal() {
    return val;
}