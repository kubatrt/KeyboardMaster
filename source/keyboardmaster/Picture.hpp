#pragma	once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Misc.hpp"
#include "PictureElement.hpp"
#include "Dictionary.hpp"
#include <memory>

namespace km
{

// Represents picture object made up from smaller pieces
class Picture
{
public:
    Picture(uint width, uint height, uint rows, uint cols);
    ~Picture() = default;

    void initialize();
    void wordTyped(std::wstring word);
    void update(sf::Time deltaTime);
    void draw(sf::RenderTarget& renderer);

    bool getVisible() const { return visible_; }
    void setVisible(bool visible) { visible_ = visible; }
    uint elementsCount() const { return elements_.size(); }
    bool isComplete();

    // TODO:
    // corectness()
    // totalTime()

private:
    Dictionary dictionary_;
    sf::Texture texture_;
    sf::Sprite sprite_;

    bool visible_ = false;
    uint typedWords_ = 0;
    uint elementsInRow_;
    uint elementsInCol_;
    uint elementsTotal_;

    //bool isComplete_;
    uint activeIndex_;
    std::vector<int> indexesLeft;



    std::vector<std::shared_ptr<PictureElement>> elements_;	// <- SHARED_PTR ???
};

}
