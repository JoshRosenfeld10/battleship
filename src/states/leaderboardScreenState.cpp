#include "leaderboardScreenState.hpp"
#include "menuScreenState.hpp"

#include <iostream>

std::vector<sf::Sprite*> LeaderboardScreenState::sprites;
std::vector<Button*> LeaderboardScreenState::buttons;

enum stats {
    TotalWins,
    TotalGamesPlayed
};

LeaderboardScreenState::LeaderboardScreenState(StateManager& stateManager, sf::RenderWindow& window)
: State( stateManager, window ) {

    // Initialize sprites if not already initialized
    if (LeaderboardScreenState::sprites.empty()) {
        LeaderboardScreenState::sprites.push_back(initializeSprite(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::LeaderboardBackgroundTexture]),
            sf::Vector2f(0,0),
            sf::Vector2f(4,4)
        ));
    }

    // Initialize buttons if not already initialized
    if (LeaderboardScreenState::buttons.empty()) {
        buttons.push_back(initializeButton(
            sf::Vector2f(0, 0),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::BackButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::BackButtonActiveTexture]),
            m_window
        ));

        buttons.push_back(initializeButton(
            sf::Vector2f(220*4, 150*4),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::YourStatsButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::YourStatsButtonActiveTexture]),
            m_window
        ));
    }

    // Initialize user stat bars
    int startWidth = 30 * 4;
    int startHeight = 40 * 4;
    for (int i = 0; i < 5; i++) {
        m_userStatBars.push_back(new UserStatBar(
            sf::Vector2f(startWidth, startHeight + i * (20 * 4)),
            sf::Vector2f(4, 4),
            i,  // ranking number
            i,  // user icon colour
            "testUser",  // username
            stats::TotalWins,  // stat to display
            5,  // number to display
            m_window,
            i == 4 && !m_stateManager.m_user->getIsGuest() ? true : false
        ));
    }

    std::cout << "LeaderboardScreenState Initialized\n";
}

LeaderboardScreenState::~LeaderboardScreenState() {
    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Arrow);
    m_window.setMouseCursor(cursor);

    deleteUserStatBars();

    std::cout << "LeaderboardScreenState Destroyed\n";
}

void LeaderboardScreenState::deleteUserStatBars() {
    for (int i = 0; i < m_userStatBars.size(); i++) {
        delete m_userStatBars[i];
        m_userStatBars[i] = nullptr;
        m_userStatBars.pop_back();
    }
}

void LeaderboardScreenState::processEvents() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_stateManager.quit();
                break;
            case sf::Event::MouseButtonReleased: {
                
                if (event.mouseButton.button == sf::Mouse::Left
                 && LeaderboardScreenState::buttons[m_buttonNames::BackButton]->getButtonState()) {
                    playSound("buttonSelect.wav");
                    std::unique_ptr<State> menuScreenState(new MenuScreenState(m_stateManager, m_window));
                    m_stateManager.changeState(std::move(menuScreenState));
                    return;
                }
                return;
            }
            default:
                break;
        }
    }
}

void LeaderboardScreenState::update() {
    sf::Vector2f mousePosition = LeaderboardScreenState::getMousePosition();
    buttons[m_buttonNames::BackButton]->updateButtonState(mousePosition);
    buttons[m_buttonNames::YourStatsButton]->updateButtonState(mousePosition);
}

void LeaderboardScreenState::draw() {
    m_window.clear();

    for (sf::Sprite* sprite : LeaderboardScreenState::sprites) {
        m_window.draw(*sprite);
    }
    for (Button* button : LeaderboardScreenState::buttons) {
        button->render();
    }
    for (UserStatBar* userStatBar : LeaderboardScreenState::m_userStatBars) {
        userStatBar->render(m_window);
    }

    m_window.display();
}
