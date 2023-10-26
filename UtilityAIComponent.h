#ifndef UTILITYAICOMPONENT_H
#define UTILITYAICOMPONENT_H
#include "ResponseCurves.h"
#include "BehavioursAndActions.h"

double ScoreActions (std::map<EConsiderations, double>, Behaviour);
bool SwitchBehaviour (EBehaviourPatterns InBehaviour);

#endif
