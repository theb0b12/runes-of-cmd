#include "Rune.hpp"
#include <iostream>

// distinct, readable colors for each rune type
static sf::Color colorForType(const std::string& t) {
    if (t == "Sight")    return {  50, 180, 255 };  // bright blue
    if (t == "Choice")   return { 180,  50, 255 };  // vivid purple
    if (t == "Harmony")  return {  50, 220, 100 };  // strong green
    if (t == "Discord")  return { 255, 140,   0 };  // orange — distinct from Violence
    if (t == "Wind")     return { 180, 230, 255 };  // pale cyan
    if (t == "Twist")    return { 255, 220,  30 };  // yellow
    if (t == "Violence") return { 220,  30,  30 };  // red
    if (t == "\n")   return { 255, 100, 200 };  // pink — distinct and visible
    return { 140, 140, 140 };                       // gray fallback
}

//Types can only be: "Sight", "Choice", "Harmony", "Discord", "Wind", "Twist", "Violence" "\n"
Rune::Rune(std::string t, Creature* h, Map& m)
    : type(t), holder(h), map(m)
{
    // call initSprite here so every rune has a color from construction
    initSprite();
}

int Rune::activate(std::vector<Rune*> r) {
    // base class — overridden by derived classes
    std::cout << "basic rune" << std::endl;
    return 0;
}

void Rune::initSprite() {
    sprite.setSize({ 64.f, 64.f });
    sprite.setFillColor(colorForType(type));
    sprite.setOutlineColor({ 255, 255, 255, 80 });
    sprite.setOutlineThickness(2.f);
}