#include "Rune.hpp"
class Choice :public Rune{
    public:
        Choice(std::string);
        int activate(Rune*) override; //override the pure virtual function from the base class
};
