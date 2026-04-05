#include "Terminal.hpp"
#include <iostream>

// helpers

sf::Vector2f Terminal::panelOrigin() const {
    return { (1920.f - PANEL_W) / 2.f, (1080.f - PANEL_H) / 2.f };
}

// constructors 

Terminal::Terminal(std::vector<Rune> arr, Creature* c, Map& m)
    : runeArr(arr), creature(c), mapPtr(&m) {}

// setup

void Terminal::setupTerminal(Creature& c) {
    creature = &c;

    if (!_font.openFromFile("ttf/Hack-Regular.ttf"))
        std::cerr << "Terminal: failed to load font\n";

    const sf::Vector2f o = panelOrigin();

    // main background
    _bgPanel.setSize({ PANEL_W, PANEL_H });
    _bgPanel.setPosition(o);
    _bgPanel.setFillColor({ 18, 18, 22, 245 });
    _bgPanel.setOutlineColor({ 60, 60, 80 });
    _bgPanel.setOutlineThickness(2.f);

    // title bar
    _titleText = sf::Text(_font);
    _titleText->setString(
        "  runes-of-cmd  //  unit:" +
        std::to_string(c.getId() * BIG_PRIME%1000));
    _titleText->setCharacterSize(14);
    _titleText->setFillColor({ 120, 180, 120 });
    _titleText->setPosition({ o.x + PAD, o.y + PAD });

    // editor panel (top portion)
    float editorH = PANEL_H * EDITOR_FRAC;
    float editorY = o.y + HEADER_H;
    _editorBg.setSize({ PANEL_W, editorH });
    _editorBg.setPosition({ o.x, editorY });
    _editorBg.setFillColor({ 22, 22, 28, 255 });

    // line number gutters
    float lineH    = editorH / MAX_LINES;
    float gutterW  = 48.f;
    _lineNumberBgs.clear();
    _lineNumbers.clear();
    for (int i = 0; i < MAX_LINES; i++) {
        float ly = editorY + i * lineH;

        sf::RectangleShape gutterBg({ gutterW, lineH });
        gutterBg.setPosition({ o.x, ly });
        gutterBg.setFillColor({ 28, 28, 36 });
        _lineNumberBgs.push_back(gutterBg);

        _lineNumbers.push_back(sf::Text(_font));
        _lineNumbers.back()->setString(std::to_string(i + 1));
        _lineNumbers.back()->setCharacterSize(13);
        _lineNumbers.back()->setFillColor({ 80, 80, 100 });
        _lineNumbers.back()->setPosition({ o.x + 10.f, ly + lineH / 2.f - 8.f });
    }
    // initialise empty lines
    _lines.assign(MAX_LINES, {});
    _cursorLine = 0;

    



    // picker panel (bottom portion)
    float pickerH = PANEL_H * PICKER_FRAC;
    float pickerY = o.y + PANEL_H - pickerH;
    _pickerBg.setSize({ PANEL_W, pickerH });
    _pickerBg.setPosition({ o.x, pickerY });
    _pickerBg.setFillColor({ 14, 14, 18, 255 });
    _pickerBg.setOutlineColor({ 50, 50, 70 });
    _pickerBg.setOutlineThickness(1.f);

    
    // picker cards
    _pickerCardShapes.clear();
    _pickerButtons.clear();
    _pickerLabels.clear();

    _pickerCardShapes.reserve(runeArr.size());


    float cardStartX = o.x + PAD * 2;
    float cardY      = pickerY + PAD * 2;
    for (int i = 0; i < (int)runeArr.size(); i++) {
        int   col = i % COLS;
        int   row = i / COLS;
        float cx  = cardStartX + col * (TILE + PAD);
        float cy  = cardY      + row * (TILE + PAD + 18.f);

        sf::RectangleShape card({ TILE, TILE });
        card.setPosition({ cx, cy });
        card.setFillColor(runeArr[i].getSprite().getFillColor());
        card.setOutlineColor({ 60, 60, 80 });
        card.setOutlineThickness(1.5f);
        _pickerCardShapes.push_back(card);
        _pickerButtons.push_back(std::make_unique<SimpleButton>(&_pickerCardShapes.back()));

        bool isNullTerminator = (runeArr[i].getType() == "\n");
        _pickerLabels.push_back(sf::Text(_font));
        _pickerLabels.back()->setString(isNullTerminator ? "\\n" : runeArr[i].getType());
        _pickerLabels.back()->setCharacterSize(11);
        _pickerLabels.back()->setFillColor(isNullTerminator ? sf::Color{ 180, 230, 255 } : sf::Color::White);
        _pickerLabels.back()->setPosition({ cx, cy + TILE + 2.f });
    }
    _prevPickerState.assign(_pickerButtons.size(), false);

    _prevPickerState.assign(_pickerButtons.size(), false);
    _prevCompileState = false;
    _prevExitState    = false;
    _compiled         = false;
    _exitRequested    = false;
    _program.clear();
    _lines.assign(MAX_LINES, {});
    _cursorLine = 0;

    // compile button
    float btnW = 160.f, btnH = 40.f;
    float btnX = o.x + PANEL_W - btnW - PAD * 2;
    float btnY = pickerY + (PANEL_H * PICKER_FRAC - btnH) / 2.f;
    _compileBtnShape.setSize({ btnW, btnH });
    _compileBtnShape.setPosition({ btnX, btnY });
    _compileBtnShape.setFillColor({ 30, 80, 30 });
    _compileBtnShape.setOutlineColor({ 80, 200, 80 });
    _compileBtnShape.setOutlineThickness(2.f);
    _compileBtnWidget = std::make_unique<SimpleButton>(&_compileBtnShape);

    _compileLabel = sf::Text(_font);
    _compileLabel->setString(">> COMPILE");
    _compileLabel->setCharacterSize(16);
    _compileLabel->setFillColor({ 80, 220, 80 });
    auto lb = _compileLabel->getLocalBounds();
    _compileLabel->setOrigin({ lb.size.x / 2.f, lb.size.y / 2.f });
    _compileLabel->setPosition({ btnX + btnW / 2.f, btnY + btnH / 2.f });

    // exit button (top-right of panel)
    float exitW = 36.f, exitH = 26.f;
    _exitBtnShape.setSize({ exitW, exitH });
    _exitBtnShape.setPosition({ o.x + PANEL_W - exitW - PAD, o.y + PAD - 2.f });
    _exitBtnShape.setFillColor({ 120, 30, 30 });
    _exitBtnShape.setOutlineColor({ 220, 60, 60 });
    _exitBtnShape.setOutlineThickness(1.5f);
    _exitBtnWidget = std::make_unique<SimpleButton>(&_exitBtnShape);

    _exitLabel = sf::Text(_font);
    _exitLabel->setString("x");
    _exitLabel->setCharacterSize(14);
    _exitLabel->setFillColor({ 255, 100, 100 });
    auto elb = _exitLabel->getLocalBounds();
    _exitLabel->setOrigin({ elb.size.x / 2.f, elb.size.y / 2.f });
    _exitLabel->setPosition({
        o.x + PANEL_W - exitW / 2.f - PAD,
        o.y + PAD + exitH / 2.f - 4.f
    });
}

// rebuild editor tokens

void Terminal::rebuildEditor() {
    if (_lines.empty()) return;
    _tokenShapes.clear();
    _tokenButtons.clear();
    _prevTokenState.clear();

    const sf::Vector2f o      = panelOrigin();
    float editorH  = PANEL_H * EDITOR_FRAC;
    float lineH    = editorH / MAX_LINES;
    float gutterW  = 48.f;
    float tokenH   = lineH * 0.60f;
    float tokenPad = 6.f;

    _tokenShapes.reserve(/* max possible tokens */MAX_LINES * MAX_PER_LINE);

    for (int li = 0; li < (int)_lines.size(); li++) {
        float ly     = o.y + HEADER_H + li * lineH;
        float tokenY = ly + (lineH - tokenH) / 2.f;
        float tokenX = o.x + gutterW + tokenPad;

        for (int ti = 0; ti < (int)_lines[li].size(); ti++) {
            Rune* r     = _lines[li][ti];
            for (int ti = 0; ti < (int)_lines[li].size(); ti++) {
                Rune* r = _lines[li][ti];
                bool isNullTerminator = (r->getType() == "\n");
            }
            bool isNullTerminator = (r->getType() == "\n");
            float tokenW = isNullTerminator ? tokenH : (TILE * 0.85f);

            sf::RectangleShape tok({ tokenW, tokenH });
            tok.setPosition({ tokenX, tokenY });
            tok.setFillColor(r->getSprite().getFillColor());
            tok.setOutlineColor({ 255, 255, 255, 60 });
            tok.setOutlineThickness(1.f);
            _tokenShapes.push_back(tok);
            _tokenButtons.push_back(
                std::make_unique<SimpleButton>(&_tokenShapes.back())
            );
            _prevTokenState.push_back(false);

            // _tokenLabels.push_back(sf::Text(_font));
            // _tokenLabels.back()->setString(isWind ? u8"\u21b5" : r->getType().substr(0, 4));
            // _tokenLabels.back()->setCharacterSize(10);
            // _tokenLabels.back()->setFillColor(sf::Color::White);
            // _tokenLabels.back()->setPosition({ tokenX + 3.f, tokenY + tokenH / 2.f - 7.f });

            tokenX += tokenW + tokenPad;
        }
    }
}

void Terminal::rebuildPickerHighlights() {}

// update

void Terminal::update(sf::Vector2f mouse) {
    // escape key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        _exitRequested = true;
        return;
    }

    // update all buttons every frame so flash animates
    _exitBtnWidget->update(mouse);
    _compileBtnWidget->update(mouse);
    for (auto& b : _pickerButtons) b->update(mouse);
    for (auto& b : _tokenButtons)  b->update(mouse);

    // exit button — rising edge
    bool exitNow = _exitBtnWidget->getToggle();
    if (exitNow && !_prevExitState) _exitRequested = true;
    _prevExitState = exitNow;

    // picker cards — rising edge on each
    for (int i = 0; i < (int)_pickerButtons.size(); i++) {
        bool cur = _pickerButtons[i]->getToggle();
        if (cur != _prevPickerState[i]) {
            _prevPickerState[i] = cur;
            Rune* r = &runeArr[i];
            bool isNullTerminator = (r->getType() == "\n");

            if (_cursorLine < MAX_LINES) {
                if (isNullTerminator) {
                    // only allow one newline per line, and don't allow newline on last line
                    bool alreadyHasNewline = !_lines[_cursorLine].empty() && 
                                            _lines[_cursorLine].back()->getType() == "\n";
                    if (!alreadyHasNewline && _cursorLine < MAX_LINES - 1) {
                        _lines[_cursorLine].push_back(r);
                        _program.push_back(r);
                        rebuildEditor();
                        _cursorLine++;
                    }
                } else {
                    if ((int)_lines[_cursorLine].size() < 3) {
                        _lines[_cursorLine].push_back(r);
                        _program.push_back(r);
                        rebuildEditor();
                    }
                }
            }
        }
    }

    // token removal — rising edge on each
    for (int i = 0; i < (int)_tokenButtons.size(); i++) {
        bool cur = _tokenButtons[i]->getToggle();
        if (cur != _prevTokenState[i]) {
            _prevTokenState[i] = cur;
            // find line/col for this flat index and remove
            int idx = 0;
            for (int li = 0; li < (int)_lines.size(); li++) {
                for (int ti = 0; ti < (int)_lines[li].size(); ti++) {
                    if (idx == i) {
                        int flat = 0;
                        for (int ll = 0; ll < li; ll++)
                            flat += (int)_lines[ll].size();
                        flat += ti;
                        if (flat < (int)_program.size())
                            _program.erase(_program.begin() + flat);
                        _lines[li].erase(_lines[li].begin() + ti);
                        // recompute cursor
                        _cursorLine = 0;
                        for (int ll = 0; ll < MAX_LINES; ll++)
                            if (!_lines[ll].empty()) _cursorLine = ll;
                        rebuildEditor();
                        return;
                    }
                    idx++;
                }
            }
        }
    }

    // compile button — rising edge
    bool compileNow = _compileBtnWidget->getToggle();
    if (compileNow && !_prevCompileState && !_program.empty())
        _compiled = true;
        
    _prevCompileState = compileNow;
}

// draw

void Terminal::drawTerminal(sf::RenderWindow& window) {
    if (_lines.empty()) return;
    window.draw(_bgPanel);
    window.draw(_editorBg);

    // line gutters and numbers
    for (auto& bg  : _lineNumberBgs) window.draw(bg);
    for (auto& num : _lineNumbers)   window.draw(*num);

    // line separators
    const sf::Vector2f o  = panelOrigin();
    float editorH = PANEL_H * EDITOR_FRAC;
    float lineH   = editorH / MAX_LINES;
    for (int i = 1; i < MAX_LINES; i++) {
        sf::RectangleShape sep({ PANEL_W, 1.f });
        sep.setPosition({ o.x, o.y + HEADER_H + i * lineH });
        sep.setFillColor({ 40, 40, 55 });
        window.draw(sep);
    }

    // cursor line highlight
    if (_cursorLine < MAX_LINES) {
        sf::RectangleShape cursorHL({ PANEL_W, lineH });
        cursorHL.setPosition({ o.x, o.y + HEADER_H + _cursorLine * lineH });
        cursorHL.setFillColor({ 40, 60, 40, 60 });
        window.draw(cursorHL);
    }

    // tokens
    for (auto& tok : _tokenShapes) window.draw(tok);

    // picker
    window.draw(_pickerBg);
    for (auto& card : _pickerCardShapes) window.draw(card);
    for (auto& lbl  : _pickerLabels)     window.draw(*lbl);

    // compile and exit buttons
    window.draw(_compileBtnShape);
    window.draw(*_compileLabel);
    window.draw(_exitBtnShape);
    window.draw(*_exitLabel);

    // title drawn last so it's on top
    window.draw(*_titleText);
}

void Terminal::loadProgram(std::vector<Rune> runes) {
    _lines.assign(MAX_LINES, {});
    _cursorLine = 0;
    _program.clear();

    // find matching runes in runeArr by type to get stable pointers
    for (auto& r : runes) {
        if (_cursorLine >= MAX_LINES) break;
        bool isNull = (r.getType() == "\n");
        if (isNull) {
            // find \n in runeArr
            for (auto& pr : runeArr) {
                if (pr.getType() == "\n") {
                    if ((int)_lines[_cursorLine].size() < MAX_PER_LINE)
                        _lines[_cursorLine].push_back(&pr);
                    _program.push_back(&pr);
                    if (_cursorLine < MAX_LINES - 1) _cursorLine++;
                    break;
                }
            }
        } else {
            // find matching type in runeArr
            for (auto& pr : runeArr) {
                if (pr.getType() == r.getType()) {
                    if ((int)_lines[_cursorLine].size() < 3) {
                        _lines[_cursorLine].push_back(&pr);
                        _program.push_back(&pr);
                    }
                    break;
                }
            }
        }
    }
    rebuildEditor();
}