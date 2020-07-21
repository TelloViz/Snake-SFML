#pragma once
#include <queue>
#include <map>
#include "IContext.hpp"
#include "ICommand.hpp"
#include <SFML/Graphics.hpp>

class IState
{
public:
	IState(IContext* ctx) : m_pContext{ ctx } {}
	virtual ~IState() {}
	virtual void ProcessInputQueue(std::queue< sf::Keyboard::Key>& inputQueue) = 0;
	virtual void UpdateState() = 0;
	virtual void RenderState(sf::RenderWindow& window) = 0;
	bool IsFinished() const { return m_isFinished; }

protected:
	IContext* m_pContext;
	std::map<sf::Keyboard::Key, ICommand*> m_cmdMap; // TODO: I think this needs to be removed
	bool m_isFinished;

	// ::::::::::::::: Context Requests::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	// :::: Use these to make requests of the context from the current state of operation::::::::::::::::::
	virtual void RequestStateTransition(IState* newState) { m_pContext->RequestStateTransition(newState); }
	virtual void RequestStatePushTransition(IState* newState) { m_pContext->RequestStatePushTransition(newState); }
	virtual bool RequestStatePopTransition() { return m_pContext->RequestStatePopTransition(); }

	virtual void RequestProgramTermination() { m_pContext->RequestProgramTermination(); }
	virtual void RequestWindowResize(sf::Vector2u size) { m_pContext->RequestWindowResize(size.x, size.y); }
	virtual void RequestWindowTranslation(int x_dir, int y_dir) { m_pContext->RequestWindowTranslation(x_dir, y_dir); }
	
	virtual void RequestPlayAgain() { m_pContext->RequestPlayAgain(); }

	virtual void RequestPause() { m_pContext->RequestPause(); }

	virtual void RequestGameOver(int score) { m_pContext->RequestGameOver(score); }

	virtual void RequestOptions() { m_pContext->RequestOptions(); }
	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
};