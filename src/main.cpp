#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cmath>
#include <random>
#include <iostream>
#include <algorithm>

#include "Rune.hpp"
#include "rune-types/TwistRune.hpp"
#include "rune-types/SightRune.hpp"
#include "rune-types/ChoiceRune.hpp"
#include "rune-types/WindRune.hpp"
#include "rune-types/ViolenceRune.hpp"
#include "LockButton.hpp"
#include "Creature.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Terminal.hpp"
#include "Animation.hpp"
#include "Compiler.hpp"



const int windX = 1920;
const int windY = 1080;

std::vector <Creature> creVec;
int numGood = 0;
int numBad = 0;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> intDist(0,5);

bool createCreature(bool enemy, Map& map){
    int yheight = intDist(mt);
    if(enemy && map.occupied[11][yheight] == 0){
        creVec.push_back(Creature(11,yheight, 3,  true, numBad * 2 + 1));
        numBad++;
        return true;
    } else if (map.occupied[0][yheight] == 0) {
        creVec.push_back(Creature(0,yheight, 3, false, numGood * 2 + 2));
        numGood++;
        return true;
    }
    return false;
}



int spawnTimer = 0;


int main(){
    sf::RenderWindow window(sf::VideoMode({windX, windY}), "Runes of CMD",sf::Style::Default/*,sf::State::Fullscreen*/);
    sf::Vector2u windowSize = window.getSize();
    auto [windX, windY] = windowSize;
    float windowX = (float)windX;
    float windowY = (float)windY; 
    // frame rate set as not to have it hardware limited
    window.setFramerateLimit(60);

    // clock instantiation
    sf::Clock clock;


    Map map(windowX, windowY);
    
    Player player(map);
    player.setSpeed(300);

    Animation playerWalk("assets/new_player", 8.f, true);
    Animation playerIdle("assets/new_player_idle", 4.f, true); // slower for idle
    playerWalk.setScale({ 9.f, 9.f });
    playerIdle.setScale({ 9.f, 9.f });

    //Creature Feature featuring the creature
    Creature C1(3,4,-2,true,2);

    std::vector<int> runeIds = {1, 2, 5, 6, 7, 4, 8};
    std::vector<Rune> c1Runes = Compiler::transform(runeIds, &C1, map);


    Terminal terminal;
    Creature* selectedCreature = nullptr;
    
    
    // create the terminal open button
    sf::RectangleShape myButton({200.f, 100.f});
    myButton.setOrigin(myButton.getGeometricCenter());
    myButton.setPosition({400.f, 300.f});


    // music mute button
    sf::RectangleShape muteButtonShape({80.f, 40.f});
    SimpleButton muteButton(&muteButtonShape);
    bool muted = false;

    sf::Font uiFont;
    uiFont.openFromFile("ttf/Hack-Regular.ttf");
    sf::Text muteLabel(uiFont);
    muteLabel.setString("MUTE");
    muteLabel.setCharacterSize(14);
    muteLabel.setFillColor(sf::Color::Black);
    auto mlb = muteLabel.getLocalBounds();
    muteLabel.setOrigin({mlb.size.x / 2.f, mlb.size.y / 2.f});


    // position the button
    float btnX = (1920.f * 0.3f) - 90.f; // 10px from right edge of castle
    float btnY = 10.f;
    muteButtonShape.setOrigin({0.f, 0.f}); // remove origin offset to make math easier
    muteButtonShape.setPosition({ btnX, btnY });

    // center label on button
    muteLabel.setPosition({
        btnX + 40.f, // half of button width (80/2)
        btnY + 20.f  // half of button height (40/2)
    });

    LockButton guiButton(&myButton);

    bool spacePressed = false;

    // music stuff
    sf::Music bgMusic;
    if (!bgMusic.openFromFile("assets/music/bluebossav1-blasterhacks2026.ogg")) {
        std::cerr << "Failed to load music\n";
    }
    bgMusic.setLooping(true);
    bgMusic.setVolume(0.f);
    // CHANGE THIS BEFORE LAUNCH, FOR TESTING ONLY
    bgMusic.play();

    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>())
                window.close();
        }
        float dt = clock.restart().asSeconds();

        // player controls
        std::string dir = playerWalk.getCurrentDirection();
        bool moving = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            player.moveBy(0, 1, dt);  dir = "down";  moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            player.moveBy(0, -1, dt); dir = "up";    moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            player.moveBy(1, 0, dt);  dir = "right"; moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            player.moveBy(-1, 0, dt); dir = "left";  moving = true;
        }

        Animation& activeAnim = moving ? playerWalk : playerIdle;
        activeAnim.setDirection(dir, moving ? "assets/new_player" : "assets/new_player_idle");
        activeAnim.update(dt);
        activeAnim.setPosition(player.getPosition());

        bool spacePressedNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
        bool spaceJustPressed = spacePressedNow && !spacePressed;
        spacePressed = spacePressedNow;

        if (spaceJustPressed) {
            int targetX = player.getXTile();
            int targetY = player.getYTile();

            switch (player.getFacing()) {
                case  1: targetX += 1; break;
                case -1: targetX -= 1; break;
                case  2: targetY += 1; break;
                case -2: targetY -= 1; break;
            }

            targetX = std::clamp(targetX, 0, 11);
            targetY = std::clamp(targetY, 0, 5);

            int occupantId = map.occupied[targetX][targetY];
            if (occupantId != 0) {
                Creature* found = nullptr;
                if (C1.getId() == occupantId) {
                    found = &C1;
                } else {
                    for (auto& cr : creVec) {
                        if (cr.getId() == occupantId) {
                            found = &cr;
                            break;
                        }
                    }
                }

                if (found && found->getId() % 2 != 1) {
                    selectedCreature = found;
                    // picker always gets the full rune set
                    std::vector<Rune> pickerRunes = Compiler::transform({1, 2, 5, 6, 7, 4, 8}, selectedCreature, map);
                    terminal = Terminal(pickerRunes, selectedCreature, map);
                    terminal.setupTerminal(*selectedCreature);
                    // pre-load saved program separately
                    if (!selectedCreature->getProgram().empty()) {
                        std::vector<Rune> savedRunes = Compiler::transform(
                            selectedCreature->getProgram(), selectedCreature, map);
                        terminal.loadProgram(savedRunes);
                    }
                    guiButton.setToggle(true);
                }
            }
        }

        // mouse position
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_position = window.mapPixelToCoords(pixelPos);

        bool wasToggled = guiButton.getToggle();
        guiButton.update(mouse_position);
        bool justToggled = !wasToggled && guiButton.getToggle();

        if (guiButton.getToggle() && selectedCreature) {
            terminal.update(mouse_position);
            if (terminal.isCompiled()) {
                auto queue = terminal.getQueue();
                std::vector<Rune> runeVec;
                for (auto* r : queue) runeVec.push_back(*r);
                Compiler::initiallize(map);
                Compiler::createInstructions(runeVec);
                selectedCreature->setProgram(Compiler::invTransform(runeVec));
                terminal.resetCompile();
                guiButton.setToggle(false);
                selectedCreature = nullptr;
            }
        }
        if (terminal.isExitRequested()) {
            guiButton.setToggle(false);
            terminal.resetExit();
            selectedCreature = nullptr;
        }

        //spawn tests
        spawnTimer--;
        if(spawnTimer < 0){
            if(createCreature(true, map)){
                Compiler::newCreature(&creVec[creVec.size() - 1]);
            }
            if(createCreature(false, map)){
                Compiler::newCreature(&creVec[creVec.size() - 1]);
            }
            spawnTimer = 100;
        }
        
        muteButton.update(mouse_position);
        bool mutedNow = muteButton.getToggle();
        if (mutedNow != muted) {
            muted = mutedNow;
            bgMusic.setVolume(muted ? 0.f : 20.f);
            muteLabel.setString(muted ? "UNMUTE" : "MUTE");
            // re-center label after string change
            auto lb = muteLabel.getLocalBounds();
            muteLabel.setOrigin({ lb.size.x / 2.f, lb.size.y / 2.f });
            muteLabel.setPosition({ btnX + 40.f, btnY + 20.f });
        }

        // displaying stuff
        map.clearOccupied();

        window.clear();

        map.draw(window);

        Compiler::resolve();
        for(int i = 0; i < creVec.size(); i++){
            creVec[i].drawCreature(window,map);
        }
        C1.drawCreature(window,map);

        window.draw(activeAnim.getSprite());

        if (guiButton.getToggle() && !justToggled && selectedCreature) {
            terminal.drawTerminal(window);
        } else {
            window.draw(myButton);
            window.draw(muteButtonShape);
            window.draw(muteLabel);
        }
        

        window.display();

    }
}