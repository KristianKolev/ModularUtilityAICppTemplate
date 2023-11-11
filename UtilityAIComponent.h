#pragma once    
#include "ResponseCurves.h"
#include "BehavioursAndActions.h"
#include "CurveProperties.h"

//get reference to this from project. Exists here for testing purposes
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
private:
    // UPROPERTY(BlueprintReadWrite)
    std::vector<Behaviour> AllBehaviours {};
    Behaviour ActiveBehaviour {};

public:
    /* 
    Need to consider how to implement it as it is mostly defined by the use case and hard to generalize. 
    Each game will have it's own method and data set that need to be aggregated and monitored.
    Values of the map should be updated before ScoreActions() is called
    */
    // UPROPERTY(BlueprintReadWrite)
    std::map<EConsiderations, double> KnowledgeMap {}; 
    //Runs the input from the knowledge map trough a response curve to generate a score
    double TransformInputToScore(std::map<EConsiderations, double> InputMap, Axis Axis);
    //To remove the penalty from multiplying many fractional values together
    double CompensationFactorActionScore(double InScore, int NumberOfActions);
    // Multiplies the scores for all considerations inside an action and apply a compensation factor
    double ScoreConsiderations(std::vector<Axis> InConsiderations);
    // modify to work with targets - same action evaluated multiple times for each target (external array of possible targets)
    // maybe trough if statement that checks target == NULL?
    //Collects the adjusted scores for all actions
    std::vector<double> ScoreActions();
    //Picks the highest scoring action from the array of all actions.
    EActions PickBestAction(std::vector<double> AllScores);
    //calls function logic on the npc controller
    void ExecuteAction(NPCController InController, EActions InAction);
    //Combines the other methods together 
    void ScorePickAndExecuteAction(NPCController InController);
    bool SwitchBehaviour(EBehaviourPatterns InBehaviour);                           //Logic and conditions to switch are implementation dependant.
};
