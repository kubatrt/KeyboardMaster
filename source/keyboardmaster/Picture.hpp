#pragma	once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Misc.hpp"
#include "PictureElement.hpp"
#include "Dictionary.hpp"
#include <memory>

namespace km
{

class Picture
{
public:
    Picture(const sf::Texture& texture, uint width, uint height, uint rows, uint cols);
    ~Picture() = default;

    void init();

    bool getVisible() const { return visible_; }
    void setVisible(bool visible) { visible_ = visible; }

    void update(sf::Time deltaTime);
    void draw(sf::RenderTarget& renderer);

    void typedWord(std::wstring word);
    bool isComplete();
    uint elementsCount() const { return elements_.size(); }

    // TODO:
    // corectness()
    // totalTime()

private:
    bool visible_ = false;
    sf::Texture texture_;
    sf::Sprite sprite_;

    uint typedWords_ = 0;
    uint elementsInRow_;
    uint elementsInCol_;
    uint elementsTotal_;

    bool isComplete_;
    uint activeIndex_;
    std::vector<int> indexesLeft;

    Dictionary dictionary_;

    std::vector<std::shared_ptr<PictureElement>> elements_;
};

}