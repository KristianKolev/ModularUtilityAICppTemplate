#pragma once    
#include "ResponseCurves.h"
#include "BehavioursAndActions.h"
#include "CurveProperties.h"
// UOBJECT
// Component
// UPROPERTY(BlueprintReadWrite)
std::vector<Behaviour> AllBehaviours {};
Behaviour ActiveBehaviour {};

/* 
Need to consider how to implement it as it is mostly defined by the use case and hard to generalize. 
Each game will have it's own method and data set that need to be aggregated and monitored.
Values of the map should be updated before ScoreActions() is called
*/
// UPROPERTY(BlueprintReadWrite)
std::map<EConsiderations, double> KnowledgeMap {}; 
double ActionScore {};
double CompensatedScore {};

double TransformToScore (std::map<EConsiderations, double> InputMap, Axis Axis);
double ScoreActions (std::map<EConsiderations, double>, Behaviour); // remove input parameters
bool SwitchBehaviour (EBehaviourPatterns InBehaviour);
double CompensationFactorActionScore (double InScore, int NumberOfActions);

