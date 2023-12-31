#pragma once

#include "CurveProperties.h"
// Not exposed to the Editor

enum EResponseCurveType { Poly, Logistic, Logit };
// Builds a Poly, Logistic or Logit curve to convert a normalized input value from the knowledge map to a score from 0 to 1 
class ResponseCurve 
{
    private:
    double Input {};
    double Score {};
    CurveProperties CurveProperty {};

    public:
    ResponseCurve () { CurveProperty = CurvePresets.at(LinearRise); }
    ResponseCurve(double Input) : Input (Input) { CurveProperty = CurvePresets.at(LinearRise); }
    ResponseCurve(double Input, ECurvePresetTypes CurvePresetType) : Input (Input) { CurveProperty = CurvePresets.at(CurvePresetType); }
    ResponseCurve(double Input, CurveProperties CurveProperty) : Input (Input), CurveProperty(CurveProperty) {}
    // Consider a Function to build a graph in the UE editor
    void PrintGraph(int DataPoints, EResponseCurveType CurveType);
    void setCurveProperties(ECurvePresetTypes InCurvePresetType);
    void setCurveProperties(CurveProperties InCurveProperty);
    // Formula for linear/polynomial graph.
    double CalculatePolyCurve();
    // Formula for logistic graph. A logistic Curve is a common S-shaped Curve (sigmoid Curve).
    // It might be worth it to look into the derivatives of the logistic function.
    double CalculateLogisticCurve();
    // Formula for logit graph. Mathematically, the logit is the inverse of the standard logistic function
    double CalculateLogitCurve();
};
