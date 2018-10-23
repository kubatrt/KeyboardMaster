#include "WritingGame.hpp"

namespace km
{

namespace
{
constexpr int fontSize = 16;
constexpr int textLineVerticalOffset = 2;
}

WritingGame::WritingGame(fw::GameBase& game, std::string dictionaryFile)
    : StateBase(game)
    , dictionary_(dictionaryFile)
    , kb_()
{
    timer_.restart();
    mainFont_ = fw::ResourceHolder::get().fonts.get("CourierNew");

    debugTextUI_.setFont(mainFont_);
    debugTextUI_.setCharacterSize(16);
    debugTextUI_.setFillColor(sf::Color::Red);
    debugTextUI_.setStyle(sf::Text::Bold);
    debugTextUI_.setPosition(780, 500);
    
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

    nextLetter_ = dictionary_.getLines()[currentLine_][0];
}

void WritingGame::handleEvents(sf::Event e)
{
    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
            
        {
            game_.popState();
        }
        else if (e.key.code == sf::Keyboard::F12)
        {
            game_.toggleFullscreen();
        }
        else if (e.key.code == sf::Keyboard::Return)
        {
            if(gameOver_)
                game_.popState();
        }
        break;
    case sf::Event::TextEntered:
        textEnteredEvent(static_cast<wchar_t>(e.text.unicode));
        break;
    default:
        break;
    }
}

void WritingGame::newLine()
{
    typingTextLine_.clear();
    currentLine_++;
    currentletterInLine_ = 0;
}

void WritingGame::textEnteredEvent(wchar_t typedLetter)
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
        }
    }
    else if (static_cast<int>(typedLetter) == KeyCode::Enter)
    {
        if(currentLine_ < dictionary_.getLines().size() - 1) // can we go down?
        {
            kb_.omit(dictionary_.getLines()[currentLine_].size() - currentletterInLine_);
            newLine();
        }
        else
        {
            gameOver_ = true;
        }
    }
    else
    {
        if (currentletterInLine_ < dictionary_.getLines()[currentLine_].size())
        {
            typingTextLine_.push_back(typedLetter);
            currentletterInLine_++;
        }
        else
        {
            if (currentLine_ == dictionary_.getLines().size() - 1)
            {
                gameOver_ = true;
            }
            else
            {
                newLine();
            }
        }
    }

    nextLetter_ = dictionary_.getLines()[currentLine_][currentletterInLine_];
    courseInputTextUI_[currentLine_].setString(typingTextLine_);
}

void WritingGame::update(sf::Time deltaTime)
{
    
    kb_.update(deltaTime);

    std::wstringstream wss;
    wss << L"Time: " << timer_.getElapsedTime().asSeconds()
        << L"\nLetter: " << currentletterInLine_ << L" Line: " << currentLine_
        << L"\nCorrect: " << kb_.getCorrectLetters() << L" Miss: " << kb_.getMistakes()
        << L"\nOmitt: " << kb_.getOmittedLetters() << L" TypedKeys: " << kb_.getTypedKeys()
        << L"\nKPM: " << kb_.getKPM()
        << L"\nCorrectness: " << kb_.correctnessPercentage(dictionary_.getLettersCount());
    debugTextUI_.setString(wss.str());
    
}

void WritingGame::draw(sf::RenderTarget& renderer)
{
    renderer.draw(debugTextUI_);
    for (sf::Text text : courseTextUI_)
        renderer.draw(text);

    for (sf::Text text : courseInputTextUI_)
        renderer.draw(text);
}

}
