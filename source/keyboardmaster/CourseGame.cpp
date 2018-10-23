#pragma once

#include "CourseGame.hpp"
#include "../FrameworkLib/ResourceManager/ResourceHolder.hpp"

namespace km
{

namespace
{
constexpr int gameAreaWidth = 1024;
constexpr int gameAreaHeight = 640;
constexpr int courseAreaWidth = 1024;
constexpr int courseAreaHeight = 400;
constexpr int fontSize = 18;
constexpr int textLineVerticalOffset = 2;
}

CourseGame::SoundPlayer::SoundPlayer()
{
    // framework::ResourceHolder::get().audio.get
    sounds_["keytype"] = fw::ResourceHolder::get().sounds.get("keytype");
    sounds_["mistake"] = fw::ResourceHolder::get().sounds.get("mistake");
    sounds_["newline"] = fw::ResourceHolder::get().sounds.get("newline");
    sounds_["bell"] = fw::ResourceHolder::get().sounds.get("bell");
}

void CourseGame::SoundPlayer::play(const std::string sound)
{
    if (sounds_.count(sound))
    {
        sound_.setBuffer(sounds_[sound]);
        sound_.play();
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////

CourseGame::CourseGame(fw::GameBase& game, std::string filePath)
    : StateBase(game)
    , dictionary_(filePath)
    , vkb_(game.getWindow().getSize())
    , kb_()
    , gameOver_(false)
{
    timer_.restart();
    mainFont_ = fw::ResourceHolder::get().fonts.get("CourierNew");
    backgroundSpriteUI_.setTexture(fw::ResourceHolder::get().textures.get("deep-blue-space"));

    nextLetterTextUI_.setFont(mainFont_);
    nextLetterTextUI_.setString("");
    nextLetterTextUI_.setCharacterSize(32);
    nextLetterTextUI_.setFillColor(sf::Color::Yellow);
    nextLetterTextUI_.setStyle(sf::Text::Bold);
    nextLetterTextUI_.setPosition(980, 30);

    debugTextUI_.setFont(mainFont_);
    debugTextUI_.setString("Debug:");
    debugTextUI_.setCharacterSize(16);
    debugTextUI_.setFillColor(sf::Color::Red);
    debugTextUI_.setStyle(sf::Text::Bold);
    debugTextUI_.setPosition(780, 500);

    prepareTextFields();
    nextLetter_ = dictionary_.getLines()[currentLine_][0];
    vkb_.highlightLetter(static_cast<int>(nextLetter_));
}

CourseGame::~CourseGame()
{
    std::wcout << L"Program finished after " << timer_.getElapsedTime().asSeconds() << std::endl;
    std::wcout << L"KPM: " << kb_.getKPM() << ", KPW: " << kb_.getKPW() << std::endl;
}

void CourseGame::prepareTextFields()
{
    // create lines of text for this course
    for (uint i = 0; i < dictionary_.getLines().size(); ++i)
    {
        sf::Text textField;
        textField.setFont(mainFont_);
        textField.setString(dictionary_.getLines()[i]);   // must be 'L'
        textField.setCharacterSize(fontSize);
        textField.setFillColor(sf::Color::White);
        textField.setStyle(sf::Text::Bold);
        textField.setPosition(4.f, static_cast<float>(i * (fontSize * 2.f) + textLineVerticalOffset));
        courseTextUI_.push_back(textField);
    }
    // same for user input text, but empty
    for (uint i = 0; i < dictionary_.getLines().size(); ++i)
    {
        sf::Text textField;
        textField.setFont(mainFont_);
        textField.setCharacterSize(fontSize);
        textField.setFillColor(sf::Color::Cyan);
        textField.setStyle(sf::Text::Bold);
        textField.setPosition(4.f, static_cast<float>(i * (fontSize * 2.f) + textLineVerticalOffset + fontSize));
        courseInputTextUI_.push_back(textField);
    }
}

void CourseGame::newLine()
{
    typingTextLine_.clear();
    currentLine_++;
    currentletterInLine_ = 0;
    soundPlayer_.play("newline");
}

void CourseGame::handleEvents(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::Resized:
        break;
    case sf::Event::LostFocus:
        break;
    case sf::Event::GainedFocus:
        break;

    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape)
        {
            game_.popState();
        }
        else if (event.key.code == sf::Keyboard::F12)
        {
            game_.toggleFullscreen();
        }
        else if (event.key.code == sf::Keyboard::Return)
        {
            if (gameOver_)
            {
                game_.popState();
            }
        }
        break;
    case sf::Event::TextEntered:
            std::wcout << L"debug ASCII character typed: " << static_cast<int>(event.text.unicode) << std::endl;
            textEnteredEvent(static_cast<wchar_t>(event.text.unicode));
        break;
    default:
        break;
    }
}



void CourseGame::textEnteredEvent(wchar_t typedLetter)
{
    if(gameOver_) 
        return;

    kb_.textEnteredEvent(typedLetter, typedLetter == nextLetter_, currentletterInLine_);

    if (static_cast<int>(typedLetter) == KeyCode::Backspace)
    {
        if (currentletterInLine_ > 0)
        {
            currentletterInLine_--;
            typingTextLine_.pop_back();
            std::wcout << "BACKSPACE" << std::endl;
        }
    }
    else if (static_cast<int>(typedLetter) == KeyCode::Enter)
    {
        if (currentLine_ < dictionary_.getLines().size() - 1) // can we go down?
        {
            int omittedLetters = dictionary_.getLines()[currentLine_].size() - currentletterInLine_;
            kb_.omit(omittedLetters);
            newLine();
            soundPlayer_.play("newline");
            std::wcout << "NEWLINE OMIT" << std::endl;
        }
        else
        {
            std::wcout << "(END 1) that was last line" << std::endl;
            gameOver_ = true;
        }
    }
    else // any other letter
    {
        // if current letter is not last in current line?
        if (currentletterInLine_ < dictionary_.getLines()[currentLine_].size())
        {
            if (typedLetter == nextLetter_)
            {
                soundPlayer_.play("keytype");
            }
            else
            {
                soundPlayer_.play("mistake");
            }

            typingTextLine_.push_back(typedLetter);
            currentletterInLine_++;

            std::wcout << "typedLetter: " << static_cast<int>(typedLetter) << std::endl;
            std::wcout << "nextLetter: " << static_cast<int>(nextLetter_) << std::endl;
        }
        else
        {
            // and its last line
            if (currentLine_ == dictionary_.getLines().size() - 1)
            {
                std::wcout << "(END 2) that was last letter in line" << std::endl;
                gameOver_ = true;
            }
            else
            {
                soundPlayer_.play("mistake");
                newLine();
                // that was last letter, go to new line this means that was last letter in 
                // last line in course and it's incorrect, but dont count mistake
            }
        }
    }

    // HACK
    if (currentLine_ >= dictionary_.getLines().size())
    {
        std::wcerr << "HACK" << std::endl;
        currentLine_ = dictionary_.getLines().size() - 1;
    }
        

    nextLetter_ = dictionary_.getLines()[currentLine_][currentletterInLine_];
    if (static_cast<int>(nextLetter_) == 0 || static_cast<int>(nextLetter_) == KeyCode::Enter)
        nextLetterTextUI_.setString("NL");
    else if (static_cast<int>(nextLetter_) == KeyCode::Space)
        nextLetterTextUI_.setString("_");
    else
        nextLetterTextUI_.setString(nextLetter_);

    courseInputTextUI_[currentLine_].setString(typingTextLine_);
    vkb_.highlightLetter(static_cast<int>(nextLetter_));
}

/*uint CourseGame::inpenultimateLineNumber()
{ 
    return dictionary_.getLines().size() - 1; 
};

uint CourseGame::currentLineLength()
{
    return dictionary_.getLines()[currentLine_].size(); // - 1
}*/



void CourseGame::update(sf::Time deltaTime)
{
    if (gameOver_)
        return;

    vkb_.update(deltaTime);
    kb_.update(deltaTime);

    std::wstringstream wss;
    wss << L"Time: " << timer_.getElapsedTime().asSeconds()
        << L"\nLetter: " << currentletterInLine_ << L" Line: " << currentLine_
        << L"\nCorrect: " << kb_.getCorrectLetters() << L" Miss: " << kb_.getMistakes()
        << L"\nOmitt: " << kb_.getOmittedLetters() << L" TypedKeys: " << kb_.getTypedKeys()
        << L"\nKPM: " << kb_.getKPM()
        << L"\nCorrectness: " << kb_.correctnessPercentage(dictionary_.getLettersCount());
    debugTextUI_.setString(wss.str());

    if (static_cast<int>(nextLetter_) == 0 || static_cast<int>(nextLetter_) == KeyCode::Enter)
        nextLetterTextUI_.setString("NL");
    else if (static_cast<int>(nextLetter_) == KeyCode::Space)
        nextLetterTextUI_.setString("_");
    else
        nextLetterTextUI_.setString(nextLetter_);
}

void CourseGame::draw(sf::RenderTarget& renderer)
{
    renderer.draw(backgroundSpriteUI_);
    vkb_.draw(renderer);

    for (sf::Text text : courseTextUI_)
        renderer.draw(text);
    
    for (sf::Text text : courseInputTextUI_)
        renderer.draw(text);
   
    renderer.draw(nextLetterTextUI_);
    renderer.draw(debugTextUI_);
}

}
