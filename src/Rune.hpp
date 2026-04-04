#ifndef RUNE_HPP
#define RUNE_HPP
#include <string>
#include <vector>


class Rune{
    public:
        Rune(std::string);
        std::string getType() const { return type; }
        virtual int  activate(std::vector<Rune*>); //pure virtual function to be implemented by derived classes
    private:
        std::string type;
};

#endif
