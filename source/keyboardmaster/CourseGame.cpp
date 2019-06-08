#include <iomanip>
#include "CourseGame.hpp"


namespace km
{

namespace
{
//constexpr uint GameAreaWidth = 1024;
//constexpr uint GameAreaHeight = 640;
constexpr uint CourseAreaWidth = 1024;
constexpr uint CourseAreaHeight = 400;
constexpr uint fontSize = 18;
constexpr uint textLineVerticalOffset = 2;
constexpr uint metronomeStep = 10;
sf::Vector2f nextLetterUI_position { 880, 520 };
sf::Vector2f panelUI_position { 776, 500 };
constexpr uint metronomeDefaultBpm = 80;
}


CourseGame::CourseGame(fw::GameBase& game, std::string dictionaryFilePath)
    : StateBase(game)
    , dictionary_(dictionaryFilePath)
    , vkb_(game.getWindow().getSize())
    , kb_()
    , gameOver_(false)
	, metronome_(metronomeDefaultBpm)
{
    timer_.restart();
    mainFont_ = fw::ResourceHolder::get().fonts.get("CourierNew");
    backgroundSpriteUI_.setTexture(fw::ResourceHolder::get().textures.get("deep-blue-space"));


    nextLetterTextUI_.setFont(mainFont_);
    nextLetterTextUI_.setString("");
    nextLetterTextUI_.setCharacterSize(48);
    nextLetterTextUI_.setFillColor(sf::Color::Red);
    nextLetterTextUI_.setStyle(sf::Text::Bold);
    nextLetterTextUI_.setPosition(880, 520);

    panelRectUI_.setTexture(fw::ResourceHolder::get().textures.get("panel"));
    panelRectUI_.setPosition(776, 500);

    statusTextUI_.setFont(mainFont_);
    statusTextUI_.setString("Debug:");
    statusTextUI_.setCharacterSize(14);
    statusTextUI_.setFillColor(sf::Color::Black);
    statusTextUI_.setStyle(sf::Text::Bold);
    statusTextUI_.setPosition(800, 600);

    prepareTextFields();

    nextLetter_ = dictionary_.getLines()[currentLine_][0];
    vkb_.highlightLetter(static_cast<int>(nextLetter_));

    LOG_DEBUG("CourseGame CTOR " << dictionaryFilePath.c_str());
}

CourseGame::~CourseGame()
{
	LOG_DEBUG(L"CourseGame DTOR. Finished time: " << timer_.getElapsedTime().asSeconds())
    LOG_INFO(L"Keys per minute KPM: " << kb_.getKPM() << ", words per minute WPM: " << kb_.getWPM())
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

void CourseGame::handleEvents(sf::Event event)
{
    switch (event.type)
    {
    /*
    case sf::Event::Resized:
        break;
    case sf::Event::LostFocus:
        break;
    case sf::Event::GainedFocus:
        break;
     */
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
			metronome_.setBPM(metronome_.getBPM() - metronomeStep);
		}
        else if (event.key.code == sf::Keyboard::F3)
		{
        	metronome_.setBPM(metronome_.getBPM() + metronomeStep);
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
            LOG_DEBUG(L"debug ASCII character typed: " << static_cast<int>(event.text.unicode) );
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
        }
    }
    else if (static_cast<int>(typedLetter) == KeyCode::Enter)
    {
        if (currentLine_ < dictionary_.getLines().size() - 1) // can we go down?
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

            LOG_DEBUG("typedLetter: " << static_cast<int>(typedLetter));
            LOG_DEBUG("nextLetter: " << static_cast<int>(nextLetter_));
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
                // that was last letter, go to new line this means that was last letter in 
                // last line in course and it's incorrect, but dont count mistake
            }
        }
    }

    // FIXME: HACK! currentLine_ = dictionary_.getLines().size() - 1
    if (currentLine_ >= dictionary_.getLines().size())
    {
        LOG_INFO("HACK!!!")
        currentLine_ = dictionary_.getLines().size() - 1;
    }
        

    setNextLetter();

    courseInputTextUI_[currentLine_].setString(typingTextLine_);
    vkb_.highlightLetter(static_cast<int>(nextLetter_));
}

void CourseGame::newLine()
{
    typingTextLine_.clear();
    currentLine_++;
    currentletterInLine_ = 0;
    SoundPlayer::getInstance()->play("newline");
}


void CourseGame::setNextLetter()
{
    nextLetter_ = dictionary_.getLines()[currentLine_][currentletterInLine_];
    if (static_cast<int>(nextLetter_) == 0 || static_cast<int>(nextLetter_) == KeyCode::Enter)
        nextLetterTextUI_.setString("NL");
    else if (static_cast<int>(nextLetter_) == KeyCode::Space)
        nextLetterTextUI_.setString("_");
    else
        nextLetterTextUI_.setString(nextLetter_);
}

std::wstring CourseGame::prepareStatusString()
{
	std::wstringstream wss;
	wss << L"Czas: " << static_cast<int>(timer_.getElapsedTime().asSeconds())
		<< L"\nLitera: " << currentletterInLine_ << L" Linia: " << currentLine_
		<< L"\nPoprawne: " << kb_.getCorrectLetters() << L" Pomyłek: " << kb_.getMistakes()
		<< L"\nPominiętych: " << kb_.getOmittedLetters()
		<< L"\nKlawisze na minute: " << kb_.getKPM()
		<< L"\nWyrazy na minute: " << kb_.getWPM()
		<< L"\nPoprawność: " << kb_.correctnessPercentage(dictionary_.getLettersCount())
		<< L"\nMetronom: " << metronome_.getBPM();

	return wss.str();
}



void CourseGame::update(sf::Time deltaTime)
{
    if (gameOver_)
        return;

    metronome_.update(deltaTime);
    vkb_.update(deltaTime);
    kb_.update(deltaTime);

    std::wstring status = prepareStatusString();
    statusTextUI_.setString(status);

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
    renderer.draw(panelRectUI_);
    vkb_.draw(renderer);

    // original text
    for (sf::Text text : courseTextUI_)
        renderer.draw(text);
    // text written by user
    for (sf::Text text : courseInputTextUI_)
        renderer.draw(text);
   
    renderer.draw(nextLetterTextUI_);
    renderer.draw(statusTextUI_);
}

}
