#include <iostream>
#include <vector>

// Exposed to the editor
//UPROPERTY(BlueprintReadWrite)
// enum is to be replaced by the user with their own set of custom enums

// What factors do I need to consider?
enum Considerations {                           // replaced by user, values are placeholder examples
        DistanceToTarget, 
        TargetsInRange, 
        TimeSinceLastMeal
};    

// See ResponseCruves.cpp
enum ResponseCurveType { Poly, Logistic, Logit };

// The consideration together with data needed to score it
struct Axis {
    Considerations consideration {};
    ResponseCurveType CurveType {};  
    double upperClamp {};                       // consider a lowerClamp?? What could be a use case?
    double Mslope {};
    double Kexponent {};
    double Xshift {};
    double Yshift {};
};

// What are the actions I can take?
enum Actions {                                  // replaced by user, values are placeholder examples
    Attack,
    Sneak,
    Flee
};                               

// Implemented as an array. 
// What is my behaviour based on the set of actions I can choose from?
struct Behaviour {                              // this could be a map
    Actions action {};
    std::vector<Axis> axes {};
};

// The different types of behaviour I can exhibit.
enum BehaviourPatterns {                        // replaced by user, values are placeholder examples
    Satietad,
    Content,
    Hangry
};                     

struct BehaviourSet {                           // this could be a map
    BehaviourPatterns behaviourPattern {};
    std::vector<Behaviour> behaviours {};
};

/* 
This could be a good spot for the knowledge map. Need to consider how to implement it as it is 
mostly define by the use case and hard to generalize. Each game will have it's own method and data set
that need to be aggregated and monitored.
*/
