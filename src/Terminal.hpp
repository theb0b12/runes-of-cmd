#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <optional>
#include <memory>
#include "Rune.hpp"
#include "Creature.hpp"
#include "Map.hpp"
#include "SimpleButton.hpp"

class Terminal {
public:
    Terminal() = default;
    Terminal(std::vector<Rune> runeArr, Creature* creature, Map& m);
    void setupTerminal(Creature& creature);
    void update(sf::Vector2f mousePos);
    void drawTerminal(sf::RenderWindow& window);

    std::vector<Rune*> getQueue() const { return _program; }
    bool isCompiled() const { return _compiled; }
    void resetCompile() { _compiled = false; _program.clear(); rebuildEditor(); }
    bool isExitRequested() const { return _exitRequested; }
    void resetExit() { _exitRequested = false; }

    void loadProgram(std::vector<Rune> runes);

private:
    // layout constants
    static constexpr float PANEL_W      = 1920 * 0.85f;
    static constexpr float PANEL_H      = 1080 * 0.85f;
    static constexpr float PAD          = 10.f;
    static constexpr float TILE         = 68.f;
    static constexpr int   COLS         = 8;
    static constexpr int   MAX_LINES    = 4;
    static constexpr int   MAX_PER_LINE = 4;
    static constexpr int   BIG_PRIME    = 104729;

    // split: editor = top 55%, picker = bottom 38%, header ~4%
    static constexpr float HEADER_H    = 36.f;
    static constexpr float EDITOR_FRAC = 0.55f;
    static constexpr float PICKER_FRAC = 0.38f;

    // helpers
    sf::Vector2f panelOrigin() const;
    void rebuildEditor();
    void rebuildPickerHighlights();

    // panels
    sf::RectangleShape _bgPanel;
    sf::RectangleShape _editorBg;
    sf::RectangleShape _pickerBg;

    // header
    std::optional<sf::Text> _titleText;

    // editor area
    // _lines[i] = rune pointers on line i (Wind rune ends a line visually)
    std::vector<std::vector<Rune*>>      _lines;
    // flat visual tokens: one shape + button + label per placed rune
    std::vector<sf::RectangleShape>              _tokenShapes;
    std::vector<std::unique_ptr<SimpleButton>>   _tokenButtons;
    std::vector<bool>                            _prevTokenState;
    // line number gutter
    std::vector<sf::RectangleShape>      _lineNumberBgs;
    std::vector<std::optional<sf::Text>> _lineNumbers;
    // cursor: which line the next rune goes on
    int _cursorLine = 0;

    // picker area
    std::vector<sf::RectangleShape>              _pickerCardShapes;
    std::vector<std::unique_ptr<SimpleButton>>   _pickerButtons;
    std::vector<std::optional<sf::Text>>         _pickerLabels;
    std::vector<bool>                            _prevPickerState;

    // compile button
    sf::RectangleShape              _compileBtnShape;
    std::unique_ptr<SimpleButton>   _compileBtnWidget;
    std::optional<sf::Text>         _compileLabel;
    bool                            _prevCompileState = false;

    // exit button
    sf::RectangleShape              _exitBtnShape;
    std::unique_ptr<SimpleButton>   _exitBtnWidget;
    std::optional<sf::Text>         _exitLabel;
    bool                            _prevExitState = false;

    sf::Font _font;

    // data
    std::vector<Rune>  runeArr;
    std::vector<Rune*> _program;  // flat output in click order
    Creature*          creature  = nullptr;
    Map*               mapPtr    = nullptr;
    bool               _compiled = false;
    bool               _exitRequested = false;
};