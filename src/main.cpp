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

std::vector<Rune> transform(std::vector<int> vec, Creature* holder, Map& map){
    std::vector<Rune> output;
    for(size_t i = 0; i < vec.size(); i++){
        switch(vec[i]){
            case 1: output.push_back(Sight(holder, map));            break;
            case 2: output.push_back(Choice(holder, map));           break;
            case 3: output.push_back(Rune("Harmony", holder, map));  break;
            case 4: output.push_back(Rune("Discord", holder, map));  break;
            case 5: output.push_back(Wind(holder, map));             break;
            case 6: output.push_back(Twist(holder, map));            break;
            case 7: output.push_back(Violence(holder, map));         break;
            case 8: output.push_back(Rune("Escape", holder, map));       break;
        }
    }
    return output;
}

const int windX = 1920;
const int windY = 1080;

std::vector<Creature> creVec;
int numGood = 0;
int numBad  = 0;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> intDist(0, 5);

bool createCreature(bool enemy, Map& map){
    int yheight = intDist(mt);
    if(enemy && map.occupied[11][yheight] == 0){
        creVec.push_back(Creature(11, yheight, 3, true, numBad * 2 + 1)); // health=3
        numBad++;
        return true;
    } else if(!enemy && map.occupied[0][yheight] == 0){
        creVec.push_back(Creature(0, yheight, 3, false, numGood * 2 + 2)); // health=3
        numGood++;
        return true;
    }
    return false;
}

int wave = 1;
int enemiesPerWave = 2;
int goodPerWave = 3;
int enemiesSpawned = 0;
int goodSpawned = 0;
float waveTimer = 0.f;
float spawnInterval = 5.f;   // seconds between spawns
float resolveTimer = 0.f;
const float RESOLVE_INTERVAL = 2.f;
bool waveActive = false;

int main(){
    sf::RenderWindow window(sf::VideoMode({windX, windY}), "Runes of CMD", sf::Style::Default);
    sf::Vector2u windowSize = window.getSize();
    auto [windX, windY] = windowSize;
    float windowX = (float)windX;
    float windowY = (float)windY;
    window.setFramerateLimit(60);

    sf::Clock clock;

    Map map(windowX, windowY);

    Player player(map);
    player.setSpeed(300);

    Animation playerWalk("assets/new_player", 8.f, true);
    Animation playerIdle("assets/new_player_idle", 4.f, true);
    playerWalk.setScale({ 9.f, 9.f });
    playerIdle.setScale({ 9.f, 9.f });

    Terminal terminal;
    Creature* selectedCreature = nullptr;

    // music mute button
    sf::RectangleShape muteButtonShape({80.f, 40.f});
    SimpleButton muteButton(&muteButtonShape);
    bool muted = false;

    sf::Font uiFont;
    if (!uiFont.openFromFile("ttf/Hack-Regular.ttf"))
        std::cerr << "Failed to load font\n";
    sf::Text muteLabel(uiFont);
    muteLabel.setString("MUTE");
    muteLabel.setCharacterSize(14);
    muteLabel.setFillColor(sf::Color::Black);
    auto mlb = muteLabel.getLocalBounds();
    muteLabel.setOrigin({mlb.size.x / 2.f, mlb.size.y / 2.f});

    float btnX = (1920.f * 0.3f) - 90.f;
    float btnY = 10.f;
    muteButtonShape.setOrigin({0.f, 0.f});
    muteButtonShape.setPosition({ btnX, btnY });
    muteLabel.setPosition({ btnX + 40.f, btnY + 20.f });

    bool spacePressed = false;

    // music
    sf::Music bgMusic;
    if (!bgMusic.openFromFile("assets/music/bluebossav1-blasterhacks2026.ogg"))
        std::cerr << "Failed to load music\n";
    bgMusic.setLooping(true);
    bgMusic.setVolume(0.f);
    bgMusic.play();

    creVec.reserve(100);
    Compiler::initialize(map);

    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>())
                window.close();
        }


        float dt = clock.restart().asSeconds();



        // player controls
        std::string dir = playerWalk.getCurrentDirection();
        bool moving = false;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){ player.moveBy(0,  1, dt); dir = "down";  moving = true; }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){ player.moveBy(0, -1, dt); dir = "up";    moving = true; }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){ player.moveBy( 1, 0, dt); dir = "right"; moving = true; }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){ player.moveBy(-1, 0, dt); dir = "left";  moving = true; }

        Animation& activeAnim = moving ? playerWalk : playerIdle;
        activeAnim.setDirection(dir, moving ? "assets/new_player" : "assets/new_player_idle");
        activeAnim.update(dt);
        activeAnim.setPosition(player.getPosition());

        bool spacePressedNow   = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
        bool spaceJustPressed  = spacePressedNow && !spacePressed;
        spacePressed           = spacePressedNow;

        if(spaceJustPressed){
            int targetX = player.getXTile();
            int targetY = player.getYTile();
            switch(player.getFacing()){
                case  1: targetX += 1; break;
                case -1: targetX -= 1; break;
                case  2: targetY += 1; break;
                case -2: targetY -= 1; break;
            }
            targetX = std::clamp(targetX, 0, 11);
            targetY = std::clamp(targetY, 0, 5);

            int occupantId = map.occupied[targetX][targetY];
            if(occupantId != 0){
                Creature* found = nullptr;
                for(auto& cr : creVec){
                    if(cr.getId() == occupantId){ found = &cr; break; }
                }
                if(found && found->getId() % 2 == 0){
                    selectedCreature = found;
                    std::vector<Rune> pickerRunes = transform({1,2,5,6,7,3,4,8}, selectedCreature, map);
                    terminal = Terminal(pickerRunes, selectedCreature, map);
                    terminal.setupTerminal(*selectedCreature);
                    if(!selectedCreature->getProgram().empty()){
                        std::vector<Rune> savedRunes = transform(
                            selectedCreature->getProgram(), selectedCreature, map);
                        terminal.loadProgram(savedRunes);
                    }
                }
            }
        }

        // mouse
        sf::Vector2i pixelPos    = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_position = window.mapPixelToCoords(pixelPos);

        if(selectedCreature){
            terminal.update(mouse_position, dt);
            if(terminal.isCompiled()){
                auto queue = terminal.getQueue();
                std::vector<Rune> runeVec;
                for(auto* r : queue) runeVec.push_back(*r);
                std::vector<int> program = Compiler::invTransform(runeVec);
                selectedCreature->setProgram(program);
                Compiler::setProgram(selectedCreature, program);
                terminal.resetCompile();
                selectedCreature = nullptr;
            }
        }
        if(terminal.isExitRequested()){
            terminal.resetExit();
            selectedCreature = nullptr;
        }

        // wave and spawn logic
        waveTimer += dt;
        if(!waveActive){
            // start wave after 3 seconds
            if(waveTimer > 3.f){
                waveActive = true;
                enemiesSpawned = 0;
                goodSpawned = 0;
                waveTimer = 0.f;
                std::cout << "Wave " << wave << " starting!\n";
            }
        }

        if(waveActive && waveTimer >= spawnInterval){
            waveTimer = 0.f;

            // fill occupied before spawning so we don't overlap
            map.clearOccupied();
            for(size_t i = 0; i < creVec.size(); i++)
                map.occupied[creVec[i].getXpos()][creVec[i].getYpos()] = creVec[i].getId();

            int targetEnemies = enemiesPerWave + (wave - 1);
            int targetGood    = goodPerWave    + (wave - 1);

            if(enemiesSpawned < targetEnemies){
                if(createCreature(true, map)){
                    enemiesSpawned++;
                    Creature* enemy = &creVec[creVec.size()-1];
                    Compiler::registerCreature(enemy);
                    Creature::registerCreature(enemy);
                    // fixed enemy program: if ally in front attack, else move
                    // {2,1,3,7,8,5} = Choice Sight Harmony Violence \n Wind
                    Compiler::setProgram(enemy, {2,1,3,7,8,5});
                    enemy->setProgram({2,1,3,7,8,5});
                }
            }

            if(goodSpawned < targetGood){
                if(createCreature(false, map)){
                    Compiler::registerCreature(&creVec[creVec.size()-1]);
                    Creature::registerCreature(&creVec[creVec.size()-1]);
                    goodSpawned++;
                }
            }

            // wave complete when all spawned and all enemies dead
            if(enemiesSpawned >= targetEnemies && goodSpawned >= targetGood){
                int enemiesAlive = 0;
                for(auto& c : creVec) if(c.getEnemy()) enemiesAlive++;
                if(enemiesAlive == 0){
                    waveActive = false;
                    wave++;
                    waveTimer = 0.f;
                    std::cout << "Wave " << wave-1 << " complete! Next wave in 3s\n";
                }
            }
        }

        // mute button
        muteButton.update(mouse_position);
        bool mutedNow = muteButton.getToggle();
        if(mutedNow != muted){
            muted = mutedNow;
            bgMusic.setVolume(muted ? 0.f : 20.f);
            muteLabel.setString(muted ? "UNMUTE" : "MUTE");
            auto lb = muteLabel.getLocalBounds();
            muteLabel.setOrigin({ lb.size.x / 2.f, lb.size.y / 2.f });
            muteLabel.setPosition({ btnX + 40.f, btnY + 20.f });
        }

        // pass 1: fill occupied without drawing
        map.clearOccupied();
        for(size_t i = 0; i < creVec.size(); i++)
            map.occupied[creVec[i].getXpos()][creVec[i].getYpos()] = creVec[i].getId();

        // resolve with occupied populated
        resolveTimer += dt;
        if(Compiler::hasCreatures() && resolveTimer >= RESOLVE_INTERVAL) {
            Compiler::resolve();
            resolveTimer = 0.f;
            Compiler::removeDeadCreatures();
            creVec.erase(
                std::remove_if(creVec.begin(), creVec.end(),
                    [](const Creature& c){ return c.isDead(); }),
                creVec.end()
            );
        }

        // check castle damage
        for(auto& c : creVec){
            if(c.getEnemy() && c.getXpos() ==0 ){
                map.damageCastle();
                c.takeDamage(99); // remove them
            }
        }

        // draw
        map.clearOccupied();
        window.clear();
        map.draw(window);

        for(size_t i = 0; i < creVec.size(); i++)
            creVec[i].drawCreature(window, map);

        window.draw(activeAnim.getSprite());

        if(selectedCreature){
            terminal.drawTerminal(window);
        } else {
            window.draw(muteButtonShape);
            window.draw(muteLabel);
        }
        if(map.castleDestroyed()){
            // simple game over text for now
            sf::Text gameOver(uiFont);
            gameOver.setString("CASTLE DESTROYED - GAME OVER");
            gameOver.setCharacterSize(48);
            gameOver.setFillColor(sf::Color::Red);
            gameOver.setPosition({400.f, 500.f});
            window.draw(gameOver);
        }

        window.display();
    }
}