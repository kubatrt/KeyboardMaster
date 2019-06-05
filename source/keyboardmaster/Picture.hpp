#pragma	once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Misc.hpp"
#include "PictureElement.hpp"
#include "Dictionary.hpp"
#include "frameworkLib/Utilities.hpp"
#include "frameworkLib/IGameComponent.hpp"


namespace km
{

namespace fw = framework;

// Represents picture game object made up from smaller pieces (picture elements)
class Picture
{
public:
    Picture(uint width, uint height, uint rows, uint cols, AssetName picture);
    ~Picture() = default;

    void update(sf::Time deltaTime);
    void draw(sf::RenderTarget& renderer);

    void wordTyped(std::wstring word);
    bool isComplete();

    bool getVisible() const { return visible_; }
    void setVisible(bool visible) { visible_ = visible; }
    uint elementsCount() const { return elements_.size(); }
    sf::Vector2f getSize() const { return size_; }

    // TODO: is needed?
    // getCorectness()
    // getTotalTime()

private:
    void initialize();

    Dictionary dictionary_;
    sf::Texture texture_;
    sf::Sprite sprite_;
    sf::Vector2f size_;

    bool visible_ = false;
    //uint typedWords_ = 0;
    uint elementsInRow_;
    uint elementsInCol_;
    uint elementsTotal_;

    uint activeIndex_;
    std::vector<int> indexesLeft;

    std::vector<std::shared_ptr<PictureElement>> elements_;	// TODO: unique_ptr?
};

}
