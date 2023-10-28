#pragma once

#include "CurveProperties.h"
// Not exposed to the Editor
// Transforms the value from the knowledge map into a score from 0 to 1

enum EResponseCurveType { Poly, Logistic, Logit };

class ResponseCurve 
{
    private:
    double input {};
    double score {};
    CurveProperties curveProperty {};

    public:
    ResponseCurve () { curveProperty = CurvePresets.at(linearRise); }
    // input needs to be normalized with the clamp of its value. receive clamps in constructor and normalize in calculateCurve?
    // or do this like I have it implemented in blueprints currently, outside of the response curve
    ResponseCurve(double input) : input (input) { curveProperty = CurvePresets.at(linearRise); }
    ResponseCurve(double input, CurvePresetTypes curvePresetType) : input (input) { curveProperty = CurvePresets.at(curvePresetType); }
    ResponseCurve(double input, CurveProperties curveProperty) : input (input), curveProperty(curveProperty) {}
    // Consider a Function to build a graph in the UE editor
    void PrintGraph(int dataPoints, EResponseCurveType CurveType);
    void selectPreset(CurvePresetTypes curvePresetType);
    // Formula for linear/polynomial graph.
    double CalculatePolyCurve();
    // Formula for logistic graph. A logistic curve is a common S-shaped curve (sigmoid curve).
    // It might be worth it to look into the derivatives of the logistic function.
    double CalculateLogisticCurve();
    // Formula for logit graph. Mathematically, the logit is the inverse of the standard logistic function
    double CalculateLogitCurve();
};
