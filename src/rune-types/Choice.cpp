#include "../Rune.hpp"
class Choice :public Rune{
    public:
        Choice();
        int activate(Rune*) override; //override the pure virtual function from the base class
};

Choice::Choice() : Rune("Choice"){}

int Choice::activate(Rune* r){
    if(r == nullptr || r->getType() != "Sight"){
        //if no follow-up rune is provided, or it is not a valid rune, return error code
        return -1;
    } 
    return 0; //return a value indicating the result of the activation
}