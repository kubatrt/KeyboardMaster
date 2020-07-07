#ifndef FRAMEWORK_TOGGLEKEY_H
#define FRAMEWORK_TOGGLEKEY_H


namespace framework {

class ToggleKey {
  public:
    ToggleKey(sf::Keyboard::Key key);

    bool isKeyPressed();


  private:
    sf::Keyboard::Key m_key;

    sf::Clock delayTimer_;

};

} // namespace framework
#endif
