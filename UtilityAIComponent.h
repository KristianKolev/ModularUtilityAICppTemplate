#pragma once    
#include "ResponseCurves.h"
#include "BehavioursAndActions.h"
#include "CurveProperties.h"

//get reference to this from project
//NPCController = AAIController ;

class NPCController
{
public:
    std::string Name = "MyNPC";
    void RunActionAttack();
    void RunActionSneak();
    void RunActionFlee();
    void RunActionIdle();
};

// Exposed to the editor
// UOBJECT - Component
class UtilityAIComponent 
{
    // UPROPERTY(BlueprintReadWrite)
    std::vector<Behaviour> AllBehaviours {};
    Behaviour ActiveBehaviour {};

    /* 
    Need to consider how to implement it as it is mostly defined by the use case and hard to generalize. 
    Each game will have it's own method and data set that need to be aggregated and monitored.
    Values of the map should be updated before ScoreAction() is called
    */
    // UPROPERTY(BlueprintReadWrite)
    std::map<EConsiderations, double> KnowledgeMap {}; 

    double TransformInputToScore(std::map<EConsiderations, double> InputMap, Axis Axis);
    // modify to work with targets - same action evaluated multiple times for each target (external array of possible targets)
    // maybe trough if statement that checks target == NULL?
    std::vector<double> ScoreAction();
    EActions PickBestAction(std::vector<double> AllScores);
    // 
    void ExecuteAction(NPCController InController, EActions InAction);
    void ScorePickAndExecuteAction(NPCController InController);
    bool SwitchBehaviour(EBehaviourPatterns InBehaviour);                           //Logic and conditions to switch are implementation dependant. Should be added inside this component.
    double CompensationFactorActionScore(double InScore, int NumberOfActions);
};

