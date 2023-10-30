#pragma once
#include <map>
// Not exposed to the Editor
struct CurveProperties {
    double Slope {};        //  m - slope-intercept of the curve.
    double Exponent {};     //  K - the Logistic growth rate or steepness of the curve.
    double XShift {};       //  b - the y-intercept of the curve.
    double YShift {};       //  c - the x-intercept of the curve.
    double UpperClamp {};   //  input values above this limit will all result in the maximal score for this curve
    double LowerClamp {};   //  input values below this limit will all result in the minimal score for this curve
};
enum ECurvePresetTypes {LinearRise, LinearFall, PolyRise, PolySlowRise, PolyFall, PolySlowFall, LogisticRise, LogisticFall, LogitRise, LogitFall};
const std::map<ECurvePresetTypes, CurveProperties> CurvePresets = {
    {LinearRise, {1.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
    {LinearFall, {-1.0, 1.0, 1.0, 0.0, 0.0, 1.0}},
    {PolyRise, {1.0, 2.0, 0.0, 0.0, 0.0, 1.0}},
    {PolySlowRise, {-1.0, 2.0, 1.0, 1.0, 0.0, 1.0}},
    {PolySlowFall, {-1.0, 2.0, 0.0, 1.0, 0.0, 1.0}},
    {PolyFall, {-1.0, 3.0, 1.0, 0.0, 0.0, 1.0}},
    {LogisticRise, {1.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
    {LogisticFall, {-1.0, 1.0, 0.0, 1.0, 0.0, 1.0}},
    {LogitRise, {1.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
    {LogitFall, {-1.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
};
