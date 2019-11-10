//
//  LLowPassFilter.h
//
//  Created by Luka Gabric on 25/07/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __LLowPassFilter__
#define __LLowPassFilter__

class LLowPassFilter
{
private:
    double _alpha, _dt, _RC, _currentFilteredValue, _currentRawValue;
    void updateAlpha();
public:
    LLowPassFilter(double RC, double dt);
    
    void setRC(double RC);
    double RC();
    void setDt(double dt);
    double dt();
    double alpha();
    
    double filterValue(double rawValue);
    double currentFilteredValue();
    double currentRawValue();
};

#endif /* defined(__LLowPassFilter__) */
