#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../FrameworkLib/StateBase.hpp"


class StateBaseMock : public framework::StateBase
{
public:
    MOCK_METHOD1(handleEvent, void(sf::Event));
    MOCK_METHOD0(handleInput, void());
    MOCK_METHOD1(update, void(sf::Time));
    MOCK_METHOD1(fixedUpdate, void(sf::Time));
    MOCK_METHOD1(draw, void(sf::RenderTarget&));
};
