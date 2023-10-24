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

void ResponseCurve::selectPreset(CurvePresetTypes CurvePresetType) {
       curveProperty = CurvePresets.at(CurvePresetType);
}

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
        // to avoid log10(0)
        if (input == 0.0 && curveProperty.slope == 1.0)
               return 0.0; 
        else if (input == 0.0 && curveProperty.slope == -1.0)
               return 1.0; 
        else
        // to avoid 1/0
        if (input == 1.0 && curveProperty.slope == 1.0)
               return 1.0;
        else if (input == 1.0 && curveProperty.slope == -1.0)
               return 0.0; 
        else

        score = (curveProperty.slope * log10 ((input - curveProperty.xShift)/(1 - (input - curveProperty.xShift)))) / 5 + 0.5 + curveProperty.yShift;
        score = std::clamp(score, 0.0, 1.0);
        return score;
};

int main ()
{
    PolyCurve TestCurve (0.5, polySlowFall);
    TestCurve.PrintGraph(10);
  
    return 0;
}


