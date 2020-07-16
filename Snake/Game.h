#pragma once
#include <memory>
#include <stack>
#include <iostream>
#include "SFML/System/Clock.hpp"
#include "IState.hpp"
#include "Menu_State.hpp"
#include "Play_State.hpp"
#include "Pause_State.hpp"
#include "Game_Over_State.hpp"
#include "IContext.hpp"


class Snake_Engine : public IContext
{
public:
	Snake_Engine();

	void Run();

	

private: // private methods


    ///////////////////////////////////////////////////////////
    /// \brief Monitors event queue of window and 
    ///	passes all keyboard input to current state
    /// input:  none
    /// output: none
    ////////////////////////////////////////////////////////////
	void Input(); 

	///////////////////////////////////////////////////////////
    /// \brief Calls update method of current state to enact any pending changes
    /// input:  none
    /// output: none
    ////////////////////////////////////////////////////////////
	void Update();

	///////////////////////////////////////////////////////////
    /// \brief Calls on the current state to Render itself to the game window 
    /// input:  none
    /// output: none
    ////////////////////////////////////////////////////////////
	void Render();

     ///////////////////////////////////////////////////////////
    /// \brief State callback for when a state wants to transition to a new state
    ///	(Old state is disposed of properly and new state is activated)
    /// input:  newState : IState* 
    /// output: bSuccessful : bool
    ////////////////////////////////////////////////////////////
	virtual bool RequestStateTransition(IState* newState);

	///////////////////////////////////////////////////////////
    /// \brief State callback for when a state wants to transition but 
    ///	isn't done with it's job, this method allows a transition with the ability to return once done
    /// input:  newState : IState*
    /// output: none
    ////////////////////////////////////////////////////////////
	virtual void RequestStatePushTransition(IState* newState);

	///////////////////////////////////////////////////////////
    /// \brief State callback for when a state wants to transition back
    ///	to a state that was most recently pushed
    /// input:  none
    /// output: none
    ////////////////////////////////////////////////////////////
	virtual bool RequestStatePopTransition();

     ///////////////////////////////////////////////////////////
    /// \brief The sub-procedure that handles the actual state transitioning
    /// input:  none
    /// output: none
    ////////////////////////////////////////////////////////////
	void TransitionState();


     ///////////////////////////////////////////////////////////
    /// \brief State callback for when a state wants to terminate the game
    ///   (useful for a state that has a quit option, ex: menu)
    /// input:  none
    /// output: none
    ////////////////////////////////////////////////////////////
	virtual void RequestProgramTermination();

     ///////////////////////////////////////////////////////////
    /// \brief State callback for when a state wants to resize the RenderWindow
    /// input:  x_dim : u_int
    /// input:  y_dim : u_int
    /// output: none
    ////////////////////////////////////////////////////////////
	virtual void RequestWindowResize(unsigned x_dim, unsigned y_dim);

     ///////////////////////////////////////////////////////////
    /// \brief State callback for when a state wants to move the window
    /// input:  x_dir : int
    /// input:  y_dir : int
    /// output: none
    ////////////////////////////////////////////////////////////
	virtual void RequestWindowTranslation(int x_dir, int y_dir);

     virtual void RequestPlayAgain();

     virtual void RequestPause();

     virtual void RequestGameOver(int);



	virtual sf::VideoMode RequestVideoMode() const {
		return m_vMode;
	}



private: // private data
	std::unique_ptr<IState> m_pCurrent_State;
	std::unique_ptr<IState> m_pNext_State;
	std::shared_ptr<sf::RenderWindow> m_pWindow;
	std::queue<sf::Keyboard::Key> keyQueue;
	std::stack<IState*> m_pStateStack;
	bool m_bShouldTerminate{ false };
	sf::VideoMode m_vMode{ 600, 600 };
	sf::Time m_uptime;

     int m_score;

};

