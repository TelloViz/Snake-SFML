#include "Game.h"
#include <assert.h>

Snake_Engine::Snake_Engine() : m_uptime{}
{
     m_pWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(600, 600), "Snake!", sf::Style::Titlebar | sf::Style::Close);
    
     m_pWindow->setKeyRepeatEnabled(false);
     m_pWindow->setMouseCursorVisible(false);


     //TODO make actual frame limiter
     m_pWindow->setFramerateLimit(10);
}

void Snake_Engine::Run()
{
     m_pCurrent_State.reset(new Menu_State(this)); // moved this here from CTOR move again if there is a better place for it
     // TODO limit the timestep
     while (m_pWindow->isOpen())
     {
          Input();
          Update();                  
          Render();
     }
}

void Snake_Engine::Input()
{
     sf::Event event;
     while (m_pWindow->pollEvent(event))
     {
          if (event.type == sf::Event::Closed)
               RequestProgramTermination();
          if (event.type == sf::Event::KeyPressed)
               keyQueue.push(event.key.code);
     }    

     if(!keyQueue.empty())
          m_pCurrent_State->ProcessInputQueue(keyQueue);
}

void Snake_Engine::Update()
{
     m_pCurrent_State->UpdateState();

     // Check if any state flags are set
     if (m_bShouldTerminate) m_pWindow->close(); // TODO instead iniatiate shutdown procedure to properly end game
     if (m_pNext_State.get()) TransitionState(); // If the next state ptr is loaded then transition to it

     
}

void Snake_Engine::Render()
{
     m_pCurrent_State->RenderState(*m_pWindow);
}

bool Snake_Engine::RequestStateTransition(IState* newState)
{
     if (m_pNext_State.get()) return false; // if the next state is already loaded and pending transition... then fail
     m_pNext_State.reset(newState); // hold this until we actually do the transition
     return true;
}

void Snake_Engine::RequestStatePushTransition(IState* newState)
{
     m_pStateStack.push(m_pCurrent_State.release()); // push current state onto state stack (which now owns the state)
     m_pCurrent_State.reset(newState);
}

bool Snake_Engine::RequestStatePopTransition()
{
     if (m_pStateStack.empty()) return false; // if the state stack is empty report fail

     IState* tempPtr = m_pStateStack.top();
     m_pStateStack.pop();
     m_pCurrent_State.reset(tempPtr); // calls deleter of the former m_pCurrent_State value
     return true;
}

void Snake_Engine::TransitionState()
{
     m_pCurrent_State.swap(m_pNext_State);

     IState* tempPtr = m_pNext_State.release();

     assert(m_pNext_State.get() == nullptr);
     delete tempPtr;
}

void Snake_Engine::RequestProgramTermination()
{
     m_bShouldTerminate = true;
}

void Snake_Engine::RequestWindowResize(unsigned x_dim, unsigned y_dim)
{
     m_pWindow->setSize(sf::Vector2u{ x_dim, y_dim });
}

void Snake_Engine::RequestWindowTranslation(int x_dir, int y_dir)
{
     sf::Vector2i currentPos{ m_pWindow->getPosition() };
     sf::Vector2i newPos{ currentPos.x + x_dir, currentPos.y + y_dir };
     m_pWindow->setPosition(newPos);
}

void Snake_Engine::RequestPlayAgain()
{
     RequestStateTransition(new Play_State{ this });
}

void Snake_Engine::RequestPause()
{
     RequestStatePushTransition(new Pause_State(this));
}

void Snake_Engine::RequestGameOver(int score)
{
     RequestStateTransition(new Game_Over_State{ this, score });

}

void Snake_Engine::RequestOptions()
{
     RequestStatePushTransition(new Options_State(this));
}
