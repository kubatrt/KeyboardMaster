#include "WritingGame.hpp"
#include "SoundPlayer.hpp"

namespace km
{

namespace
{
constexpr uint FontSize = 16;
constexpr uint TextLineVerticalOffset = 2;
constexpr uint MetronomeStep = 10;
}

WritingGame::WritingGame(fw::GameBase& game, std::string dictionaryFile) // @suppress("Class members should be properly initialized")
    : StateBase(game)
    , dictionary_(dictionaryFile)
    , kb_()
	, gameOver_(false)
	, metronome_(80)
	, panelRectUI_({124.f, 768.f})
{
    gameTime_ = sf::Time::Zero;
    mainFont_ = fw::ResourceHolder::get().fonts.get("CourierNew");
    backgroundSpriteUI_.setTexture(fw::ResourceHolder::get().textures.get("deep-blue-space"));
    backgroundSpriteUI_.setColor(sf::Color(200.f, 200.f, 200.f));

    panelRectUI_.setFillColor(sf::Color(220,220,220));
    panelRectUI_.setPosition(900,0);

    nextLetter_ = dictionary_.getLines()[currentLine_][0];
    nextLetterTextUI_.setString(nextLetter_);
	nextLetterTextUI_.setFont(mainFont_);
    nextLetterTextUI_.setCharacterSize(48);
    nextLetterTextUI_.setFillColor(sf::Color::Red);
    nextLetterTextUI_.setStyle(sf::Text::Bold);
    nextLetterTextUI_.setPosition(945, 20);

    statusTextUI_.setFont(mainFont_);
    statusTextUI_.setCharacterSize(FontSize);
    statusTextUI_.setFillColor(sf::Color::Black);
    statusTextUI_.setStyle(sf::Text::Bold);
    statusTextUI_.setPosition(905, 100);
    statusTextUI_.setString("A");
    
    // Create lines of text for this course
    for (uint i = 0; i < dictionary_.getLines().size(); ++i)
    {
        sf::Text textField;
        textField.setFont(mainFont_);
        textField.setString(dictionary_.getLines()[i]);   // must be 'L'
        textField.setCharacterSize(FontSize);
        textField.setFillColor(sf::Color::White);
        textField.setStyle(sf::Text::Bold);
        textField.setPosition(4.f, static_cast<float>(i * (FontSize * 2.f) + TextLineVerticalOffset));
        courseTextUI_.push_back(textField);
    }
    // Do the same for user input text, but empty
    for (uint i = 0; i < dictionary_.getLines().size(); ++i)
    {
        sf::Text textField;
        textField.setFont(mainFont_);
        textField.setCharacterSize(FontSize);
        textField.setFillColor(sf::Color::Cyan);
        textField.setStyle(sf::Text::Bold);
        textField.setPosition(4.f, static_cast<float>(i * (FontSize * 2.f) + TextLineVerticalOffset + FontSize));
        courseInputTextUI_.push_back(textField);
    }

    nextLetter_ = dictionary_.getLines()[currentLine_][0];
    LOG_DEBUG("WritingGame CTOR " << dictionaryFile.c_str() <<  ", nextLetter: " << nextLetter_);
}

void WritingGame::handleEvents(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape)
        {
            game_.popState();
        }
        else if (event.key.code == sf::Keyboard::F12)
        {
            game_.toggleFullscreen();
        }
        else if (event.key.code == sf::Keyboard::F1)
		{
        	metronome_.toggle();
		}
        else if (event.key.code == sf::Keyboard::F2)
		{
			metronome_.setBPM(metronome_.getBPM() - MetronomeStep);
		}
        else if (event.key.code == sf::Keyboard::F3)
		{
        	metronome_.setBPM(metronome_.getBPM() + MetronomeStep);
		}
        else if (event.key.code == sf::Keyboard::Return)
        {
            if(gameOver_)
                game_.popState();
        }
        break;
    case sf::Event::TextEntered:
        textEnteredEvent(static_cast<wchar_t>(event.text.unicode));
        break;
    default:
        break;
    }
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
            SoundPlayer::getInstance()->play("newline");
        }
        else
        {
        	LOG_CRITICAL("(END 1) that was last line");
            gameOver_ = true;
        }
    }
    else // any other character
    {
    	// if current character is not last in current line?
        if (currentletterInLine_ < dictionary_.getLines()[currentLine_].size())
        {
            if (typedLetter == nextLetter_)
            {
            	SoundPlayer::getInstance()->play("keytype");
            }
            else
            {
            	SoundPlayer::getInstance()->play("mistake");
            }

            typingTextLine_.push_back(typedLetter);
            currentletterInLine_++;
        }
        else
        {
        	// and its last line
            if (currentLine_ == dictionary_.getLines().size() - 1)
            {
            	LOG_CRITICAL("(END 2) that was last letter in line");
                gameOver_ = true;
            }
            else
            {
            	SoundPlayer::getInstance()->play("mistake");
                newLine();
            }
        }

    }

    setNextLetter();
    courseInputTextUI_[currentLine_].setString(typingTextLine_);
    LOG_DEBUG("Next letter: " << nextLetter_);
    LOG_DEBUG("Typing: " << typingTextLine_);
}

void WritingGame::newLine()
{
    typingTextLine_.clear();
    currentLine_++;
    currentletterInLine_ = 0;
    SoundPlayer::getInstance()->play("newline");
}

void WritingGame::setNextLetter()
{
    nextLetter_ = dictionary_.getLines()[currentLine_][currentletterInLine_];
    if (static_cast<int>(nextLetter_) == 0 || static_cast<int>(nextLetter_) == KeyCode::Enter)
        nextLetterTextUI_.setString("NL");
    else if (static_cast<int>(nextLetter_) == KeyCode::Space)
        nextLetterTextUI_.setString("_");
    else
        nextLetterTextUI_.setString(nextLetter_);
}

std::wstring WritingGame::prepareStatusString()
{
	std::wstringstream wss;
	wss << L"Czas: \n" << (int)gameTime_.asSeconds()

		<< L"\n\nLinia: \n" << currentLine_
		<< L"\nPoprawnych: \n" << kb_.getCorrectLetters()
		<< L"\nPomyłek: \n" << kb_.getMistakes()
		<< L"\nPominięte: \n" << kb_.getOmittedLetters()
		<< L"\nKPM: \n" << kb_.getKPM()
		<< L"\nWMP: \n" << kb_.getWPM()
		<< L"\nPoprawność: \n" << kb_.correctnessPercentage(dictionary_.getLettersCount())
		<< L"\n\nMetronom: \n" << metronome_.getBPM();
	return wss.str();
}



void WritingGame::update(sf::Time deltaTime)
{
	gameTime_ += deltaTime;
    metronome_.update(deltaTime);
    kb_.update(deltaTime);

    std::wstring status = prepareStatusString();
    statusTextUI_.setString(status);
}

void WritingGame::draw(sf::RenderTarget& renderer)
{
	renderer.draw(backgroundSpriteUI_);
	renderer.draw(panelRectUI_);

    for (sf::Text text : courseTextUI_)
        renderer.draw(text);

    for (sf::Text text : courseInputTextUI_)
        renderer.draw(text);

    renderer.draw(nextLetterTextUI_);
    renderer.draw(statusTextUI_);
}

}
