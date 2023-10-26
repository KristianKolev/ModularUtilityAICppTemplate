#include "UtilityAIComponent.h"

bool SwitchBehaviour (EBehaviourPatterns InBehaviour) {
    bool bBehaviourChanged = false;

    for (auto& i : AllBehaviours) {
        if ( i.behaviourPattern == InBehaviour)
        ActiveBehaviour = i;
        bBehaviourChanged = true;
        return bBehaviourChanged;
    }
    return bBehaviourChanged;
}

double ScoreActions (std::map<EConsiderations, double>, Behaviour){

    return 0;
}

int main () {
    
    return 0;
}
