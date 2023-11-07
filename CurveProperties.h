<<<<<<< HEAD
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
=======
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
>>>>>>> e84c3b2d08233d7664f1705257443c2ed67f8426
