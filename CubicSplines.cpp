// CubicSplines.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "CubicSpline.h"
#include <iostream>
#include <iomanip>

int main()
{
    cubicSpline CSp;
    double xdata[3] = { 1,2,3 };
    double ydata[3] = { 2,3,5 };
    std::vector<double> xx(xdata, xdata + sizeof xdata / sizeof xdata[0]);
    std::vector<double> yy(ydata, ydata + sizeof ydata / sizeof ydata[0]);
    CSp.initialize(xx, yy);
    std::cout <<std::fixed<< std::setprecision(3);
    std::cout << "The equation is:\n" << CSp.getEquation()<<"\n";
    //std::cout << "Hello World!\n";
    return 0;
}

