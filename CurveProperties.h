#ifndef CURVEPROPERTIES_H
#define CURVEPROPERTIES_H
#include <map>

struct CurveProperties {
    double exponent {};     //  K - the logistic growth rate or steepness of the curve.
    double slope {};        //  m - slope-intercept of the curve.
    double xShift {};       //  b - the y-intercept of the curve.
    double yShift {};       //  c - the x-intercept of the curve.
    double upperClamp {};   //  input values above this limit will all result in the maximal score for this curve
    double lowerClamp {};   //  input values below this limit will all result in the minimal score for this curve
};
enum CurvePresetTypes {linearRise, linearFall, polyRise, polySlowRise, polyFall, polySlowFall, logisticRise, logisticFall, logitRise, logitFall};
const std::map<CurvePresetTypes, CurveProperties> CurvePresets = {
    {linearRise, {1.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
    {linearFall, {-1.0, 1.0, 1.0, 0.0, 0.0, 1.0}},
    {polyRise, {1.0, 2.0, 0.0, 0.0, 0.0, 1.0}},
    {polySlowRise, {-1.0, 2.0, 1.0, 1.0, 0.0, 1.0}},
    {polySlowFall, {-1.0, 2.0, 0.0, 1.0, 0.0, 1.0}},
    {polyFall, {-1.0, 3.0, 1.0, 0.0, 0.0, 1.0}},
    {logisticRise, {1.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
    {logisticFall, {-1.0, 1.0, 0.0, 1.0, 0.0, 1.0}},
    {logitRise, {1.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
    {logitFall, {-1.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
};

#endif
