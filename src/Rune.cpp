#include "Rune.hpp"

// Map rune names to placeholder colors
static sf::Color colorForType(const std::string& t) {
    if (t == "Sight")     return { 100, 200, 255 };  // sky blue
    if (t == "Choice")    return { 200, 100, 255 };  // purple
    if (t == "Harmony")   return { 100, 255, 150 };  // mint
    if (t == "Discord")   return { 255,  80,  80 };  // red
    if (t == "Wind")      return { 200, 230, 255 };  // pale blue
    if (t == "Twist")     return { 255, 180,  50 };  // amber
    if (t == "Violence")  return { 255,  60,  60 };  // crimson
    return { 180, 180, 180 };                         // gray fallback
}

//Types can only be: "Sight", "Choice", "Harmony", "Discord", "Wind", "Twist", "Violence" "\n"
Rune::Rune(std::string t, Creature* h, Map& m)
    : type(t), holder(h), map(m) {
}

int Rune::activate(std::vector<Rune*> r){
    //base class implementation of activate, can be overridden by derived classes
    return 0;
}

void Rune::initSprite() {
    sprite.setSize({ 64.f, 64.f });
    sprite.setFillColor(colorForType(type));
    sprite.setOutlineColor(sf::Color::White);
    sprite.setOutlineThickness(2.f);
}