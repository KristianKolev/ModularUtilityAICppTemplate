#include <math.h>
#include <algorithm>
#include <iostream>
#include "ResponseCurves.h"
//#include "Math/UnrealMathUtility.h"

// Not exposed to the Editor
// Transforms the value from the knowledge map into a score from 0 to 1

/* // normalize and clamp input
void ResponseCurve::ResponseCurve(double input, CurveProperties& curveProperty) {
        double NormalizedInput = FMath::GetMappedRangeValueClamped 
        (FVector2D(curveProperty.lowerClamp, curveProperty.upperClamp), FVector2D(0.0f, 1.0f), input) 

}
*/

// prints curve points to terminal for debugging
void ResponseCurve::PrintGraph(int dataPoints, EResponseCurveType CurveType ) {

    // Consider a Function to build a graph in the UE editor
        std::cout << "Input" << '\t' << "Score" << '\n';
        for (double i = 0; i <= dataPoints; i++)
        {
            input =  i/dataPoints;
            switch (CurveType)
            {
              case Poly: 
                     std::cout << input << '\t' << CalculatePolyCurve() << '\n';
                     break;
              case Logistic: 
                     std::cout << input << '\t' << CalculateLogisticCurve() << '\n';
                     break;
              case Logit: 
                     std::cout << input << '\t' << CalculateLogitCurve() << '\n';
                     break;
            
              default:
                     std::cout << input << '\t' << CalculatePolyCurve() << '\n';
                     break;
            }
        }
};

void ResponseCurve::selectPreset(CurvePresetTypes CurvePresetType) {
       curveProperty = CurvePresets.at(CurvePresetType);
};

// Formula for linear/polynomial graph.
double ResponseCurve::CalculatePolyCurve() {
       
        score = curveProperty.slope * pow((input - curveProperty.xShift), curveProperty.exponent) + curveProperty.yShift;
        score = std::clamp(score, 0.0, 1.0);
        return score;
};

// Formula for logistic graph. A logistic curve is a common S-shaped curve (sigmoid curve).
// It might be worth it to look into the derivatives of the logistic function.
double ResponseCurve::CalculateLogisticCurve() {
        
        score = curveProperty.slope / (1 + exp(-10 * curveProperty.exponent * (input - 0.5 - curveProperty.xShift))) + curveProperty.yShift;
        score = std::clamp(score, 0.0, 1.0);
        return score;
};

// Formula for logit graph. Mathematically, the logit is the inverse of the standard logistic function
double ResponseCurve::CalculateLogitCurve() {
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
    ResponseCurve TestCurve (0.5, polySlowRise);
    TestCurve.PrintGraph(10, Poly);
  
    return 0;
}


