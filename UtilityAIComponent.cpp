#include "UtilityAIComponent.h"
#include <algorithm>
#include <vector>
// Exposed to the editor
// UOBJECT - Component
//UFUONCTION(BlueprintReadWrite)
bool UtilityAIComponent::SwitchBehaviour(EBehaviourPatterns InBehaviour) {
    bool bBehaviourChanged = false;

    for (auto& ObservedBehaviour : AllBehaviours) 
    {
        if ( ObservedBehaviour.behaviourPattern == InBehaviour)
        {
            ActiveBehaviour = ObservedBehaviour;
            bBehaviourChanged = true;
            return bBehaviourChanged;
        }
    }
    return bBehaviourChanged;
}

double UtilityAIComponent::CompensationFactorActionScore(double InScore, int NumberOfConsiderations)
{
    // moving this check outside of funtion will reduce calls
    if (InScore == 0)
    {
        return 0;
    }
    else
    {
        InScore = (((1 - (1.0/NumberOfConsiderations)) * (1.0 - InScore)) * InScore) + InScore;
        return InScore;
    }
    return InScore;
}

double UtilityAIComponent::TransformInputToScore(std::map<EConsiderations, double> InputMap, Axis Axis)
{
    //Consider whether to put this here or inside ResponseCurve Constructor
    // this gets replaced by FMath::GetMappedRangeValueClamped in UE
    double ClampedInput = std::clamp(InputMap.at(Axis.Consideration), Axis.CurveProperty.LowerClamp, Axis.CurveProperty.UpperClamp);
    double NormalizedInput = ClampedInput/Axis.CurveProperty.UpperClamp;
    ResponseCurve TransformCurve { NormalizedInput };
    if (Axis.bUsePresetCurve == true)
    {
        TransformCurve.setCurveProperties(Axis.CurvePropertiesPerest);
    }
    else 
    {
        TransformCurve.setCurveProperties(Axis.CurveProperty);
    }
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
    }
}
//UFUONCTION(BlueprintReadWrite)
double UtilityAIComponent::ScoreAction()
{
    std::vector<double> AllActionScores {};
    
    for (auto& ObservedAction : ActiveBehaviour.Actions)
    {
        double AdjustedActionScore {1.0};
        double ActionScore {1.0};
        for (auto& ObservedConsideration : ObservedAction.Axes)
        {
            ActionScore *= TransformInputToScore(KnowledgeMap, ObservedConsideration);
            if (ActionScore == 0)
                break;;
        }
        if (ActionScore != 0)
        {
            int NumberOfConsiderations = static_cast<int> (ObservedAction.Axes.size());
            AdjustedActionScore = CompensationFactorActionScore(ActionScore, NumberOfConsiderations);
        }
        AllActionScores.push_back(AdjustedActionScore);

    }
    return AllActionScores;
}
EActions UtilityAIComponent::PickBestAction()
{

}
void UtilityAIComponent::ExecuteAction()
{

}
int main () 
{
    
    return 0;
}
