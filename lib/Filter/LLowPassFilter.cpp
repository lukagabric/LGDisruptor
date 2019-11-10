#include "LLowPassFilter.h"

LLowPassFilter::LLowPassFilter(double RC, double dt) {
    _RC = RC;
    _dt = dt;
    updateAlpha();
}

void LLowPassFilter::setRC(double RC) {
    _RC = RC;
    updateAlpha();
}

double LLowPassFilter::RC() {
    return _RC;
}

void LLowPassFilter::setDt(double dt) {
    _dt = dt;
    updateAlpha();
}

double LLowPassFilter::dt() {
    return _dt;
}

double LLowPassFilter::alpha() {
    return _alpha;
}

double LLowPassFilter::currentFilteredValue() {
    return _currentFilteredValue;
}


double LLowPassFilter::currentRawValue() {
    return _currentRawValue;
}


void LLowPassFilter::updateAlpha() {
    _alpha = dt() / (RC() + dt());
}

double LLowPassFilter::filterValue(double rawValue) {
    _currentRawValue = rawValue;
    _currentFilteredValue = rawValue * alpha() + (1 - alpha()) * currentFilteredValue();
    return currentFilteredValue();
}
