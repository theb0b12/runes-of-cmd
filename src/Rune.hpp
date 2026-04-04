#ifndef RUNE_HPP
#define RUNE_HPP

#include <string>


class Rune{
    public:
        Rune(std::string);
        virtual void activate() = 0; //pure virtual function to be implemented by derived classes
    private:
        std::string type;
};

#endif
