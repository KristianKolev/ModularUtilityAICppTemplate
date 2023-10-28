#include "UtilityAIComponent.h"
#include <algorithm>

//UFUONCTION(BlueprintReadWrite)
bool UtilityAIComponent::SwitchBehaviour(EBehaviourPatterns InBehaviour) {
    bool bBehaviourChanged = false;

    for (auto& i : AllBehaviours) 
    {
        if ( i.behaviourPattern == InBehaviour)
        {
            ActiveBehaviour = i;
            bBehaviourChanged = true;
            return bBehaviourChanged;
        }
    }
    return bBehaviourChanged;
}

double UtilityAIComponent::CompensationFactorActionScore(double InScore, int NumberOfActions)
{
    if (InScore == 0)
    {
        return 0;
    }
    else
    {
        InScore = (((1 - (1.0/NumberOfActions)) * (1.0 - InScore)) * InScore) + InScore;
        return InScore;
    }
    return InScore;
}

double UtilityAIComponent::TransformInputToScore(std::map<EConsiderations, double> InputMap, Axis Axis)
{
    //Consider whether to put this here or inside ResponseCurve Constructor
    // this gets replaced by FMath::GetMappedRangeValueClamped in UE
    double ClampedInput = std::clamp(InputMap.at(Axis.Consideration), Axis.CurveProperty.lowerClamp, Axis.CurveProperty.upperClamp);
    double NormalizedInput = ClampedInput/Axis.CurveProperty.upperClamp;
    if (Axis.bUsePresetCurve == true)
    {
        ResponseCurve TransformCurve{ NormalizedInput, Axis.CurvePropertiesPerest };
    }
    else 
    {
        ResponseCurve TransformCurve{ NormalizedInput, Axis.CurveProperty };
    }/*
    switch (Axis.CurveType)
    {
        case Poly:
            return TransformCurve.CalculatePolyCurve();
        case Logistic:
            return TransformCurve.CalculateLogisticCurve();
        case Logit:
            return TransformCurve.CalculateLogitCurve();    
        default:
            return TransformCurve.CalculatePolyCurve();
    }*/
}
//UFUONCTION(BlueprintReadWrite)
double UtilityAIComponent::ScoreActions(std::map<EConsiderations, double> KnowledgeMap, Behaviour )
{
    for (auto& ObservedAction : ActiveBehaviour.Actions)
    {
        for (auto& ObservedConsideration : ObservedAction.Axes)
        {
            double TransformInputToScore(std::map<EConsiderations, double> InputMap, Axis Axis);
        }
    }
    return 0;
}


int main () 
{
    
    return 0;
}
