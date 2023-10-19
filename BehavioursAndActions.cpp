#include <iostream>


// What factors do I need to consider?
enum Considerations {};                         // user populated

// See ResponseCruves.cpp
enum ResponseCurveType { Poly, Logistic, Logit };

// The consideration together with data needed to score it
struct Axis {
    Considerations consideration;
    ResponseCurveType CurveType {};  
    double upperClamp {};
    double Mslope {};
    double Kexponent {};
    double Xshift {};
    double Yshift {};
};

// What are the actions I can take?
enum Actions {};                                // user populated

// Implemented as an array. 
// What is my behaviour based on the set of actions I can choose from?
struct Behaviour {                              // user populated
    Actions action {};
    Axis axis[5];
};

// The different types of behaviour I can exhibit.
enum BehaviourPatterns {};                      // user populated

struct BehaviourSet {
    BehaviourPatterns behaviourPattern {};
    Behaviour behaviour[5];
};

int main() {
    
    return 0;
}
