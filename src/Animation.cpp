#include "Animation.hpp"
#include <filesystem>
#include <iostream>
#include <algorithm>

namespace fs = std::filesystem;

// Constructor: loads animation frames from folder and sets playback speed
Animation::Animation(const std::string& baseFolderPath, float speed){
    loadFromFolder(baseFolderPath);
    setSpeed(speed);
}

// Constructor: loads directional animation from subfolder
Animation::Animation(const std::string& baseFolderPath, float speed, bool moves){
    setSpeed(speed);
    loadFromFolder(baseFolderPath + "/" + _currentDirection);
}

// Loads all image files from folder into frame array
void Animation::loadFromFolder(const std::string& folderPath) {
    // save current transform before wiping sprite
    sf::Vector2f prevScale  = _sprite ? _sprite->getScale()    : sf::Vector2f{1.f, 1.f};
    sf::Vector2f prevPos    = _sprite ? _sprite->getPosition()  : sf::Vector2f{0.f, 0.f};
    sf::Angle    prevRot    = _sprite ? _sprite->getRotation()  : sf::degrees(0.f);

    _frames.clear();
    _sprite.reset();

    std::vector<fs::path> imageFiles;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            auto ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            if (ext == ".png" || ext == ".jpg" || ext == ".jpeg")
                imageFiles.push_back(entry.path());
        }
    }

    if (imageFiles.empty()) {
        std::cerr << "No image files found in folder: " << folderPath << "\n";
        return;
    }

    std::sort(imageFiles.begin(), imageFiles.end()); // ensure correct frame order

    for (const auto& path : imageFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile(path.string())) {
            std::cerr << "Failed to load texture: " << path << "\n";
            continue;
        }
        _frames.push_back(std::move(texture));
    }

    if (!_frames.empty()) {
        _sprite = std::make_unique<sf::Sprite>(_frames[0]);

        sf::Vector2u texSize = _frames[0].getSize();
        // reapply saved transform
        _sprite->setScale(prevScale);
        _sprite->setPosition(prevPos);
        _sprite->setRotation(prevRot);
    }
}

// Changes animation direction and reloads frames from corresponding subfolder
void Animation::setDirection(const std::string& newDirection, const std::string& baseFolderPath){
    if (newDirection == _currentDirection) return; // no change
    _currentDirection = newDirection;
    loadFromFolder(baseFolderPath + "/" + _currentDirection);
}

// Sets frames per second, clamps to minimum 1.0 fps
void Animation::setSpeed(float speed){
    _frameTime = 1.f / speed;
}

// Advances animation based on elapsed time and updates sprite texture
void Animation::update(float deltaTime){
    if (_frames.empty() || !_sprite) return;
    _elapsedTime += deltaTime;
    if (_elapsedTime >= _frameTime){
        _elapsedTime = 0.f;
        _currentFrame = (_currentFrame + 1) % _frames.size();
        _sprite->setTexture(_frames[_currentFrame]);
    }
}

// Returns reference to current animation sprite
const sf::Sprite& Animation::getSprite() const{
    return *_sprite;
}

// Returns current direction string
const std::string& Animation::getCurrentDirection() const{
    return _currentDirection;
}

// Sets sprite position in 2D space
void Animation::setPosition(const sf::Vector2f& pos){
    if (_sprite) _sprite->setPosition(pos);
}

// Sets sprite scale
void Animation::setScale(const sf::Vector2f& scale){
    if (_sprite) _sprite->setScale(scale);
}

// Sets sprite rotation in degrees
void Animation::setRotation(float angle){
    if (_sprite) _sprite->setRotation(sf::degrees(angle));
}