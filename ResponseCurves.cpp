#include <math.h>
#include <algorithm>
#include <iostream>
#include "ResponseCurves.h"
//#include "Math/UnrealMathUtility.h"

// Not exposed to the Editor

/* // normalize and clamp input
void ResponseCurve::ResponseCurve(double input, CurveProperties& curveProperty) {
        input = FMath::GetMappedRangeValueClamped 
        (FVector2D(curveProperty.lowerClamp, curveProperty.upperClamp), FVector2D(0.0f, 1.0f), input) 

}
*/

// Transforms the value from the knowledge map into a score from 0 to 1
void ResponseCurve::PrintGraph(int dataPoints ) {

    // Consider a Function to build a graph in the UE editor
        std::cout << "Input" << '\t' << "Score" << '\n';
        for (double i = 0; i <= dataPoints; i++)
        {
            input =  i/dataPoints;
            std::cout << input << '\t' << CalculateCurve() << '\n';
        }
};
/*
void ResponseCurve::selectPreset(CurvePresetTypes* CurvePresetType) {
       curveProperty = CurvePresets[*CurvePresetType];
}
*/
// Formula for linear/polynomial graph.
double PolyCurve::CalculateCurve() {
       
        score = curveProperty.slope * pow((input - curveProperty.xShift), curveProperty.exponent) + curveProperty.yShift;
        score = std::clamp(score, 0.0, 1.0);
        return score;
};

// Formula for logistic graph. A logistic curve is a common S-shaped curve (sigmoid curve).
// It might be worth it to look into the derivatives of the logistic function.
double LogisticCurve::CalculateCurve() {
        
        score = curveProperty.slope / (1 + exp(-10 * curveProperty.exponent * (input - 0.5 - curveProperty.xShift))) + curveProperty.yShift;
        score = std::clamp(score, 0.0, 1.0);
        return score;
};

// Formula for logit graph. Mathematically, the logit is the inverse of the standard logistic function
double LogitCurve::CalculateCurve() {
        //examine that 5 + 0.5 term
        score = ((curveProperty.slope * ( log10 ((input - curveProperty.xShift)/(1 - input - curveProperty.xShift)) )) / (5 + 0.5 + curveProperty.yShift));
        score = std::clamp(score, 0.0, 1.0);
        return score;
};
void selecPreset (CurvePresetTypes CurvePresetType, PolyCurve curve, const std::map<CurvePresetTypes, CurveProperties>& map) 
{
       curve.curveProperty = map[CurvePresetType];
       return;
}

int main ()
{
   // LogisticCurve TestCurve(100, {-1.0, 0.7, -0.05, 1.08});
    // TestCurve.PrintGraph(10);
    PolyCurve newpoly;
    CurvePresetTypes newtype = linearFall;
        selecPreset(newtype, newpoly, CurvePresets);
  
    return 0;
}


