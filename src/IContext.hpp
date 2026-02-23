#pragma once

class IState;
namespace sm
{
	class IContext
	{
	public:
		virtual ~IContext() {}

	protected:
		friend class IState;

		///////////////////////////////////////////////////////////
	    /// \brief State callback for when a state wants to transition to a new state
	    ///	(Old state is disposed of properly and new state is activated)
	    /// input:  newState : IState* 
	    /// output: bSuccessful : bool
	    ////////////////////////////////////////////////////////////
		virtual bool RequestStateTransition(IState* newState) = 0;

		///////////////////////////////////////////////////////////
	    /// \brief State callback for when a state wants to transition but 
	    ///	isn't done with it's job, this method allows a transition with the ability to return once done
	    /// input:  newState : IState*
	    /// output: none
	    ////////////////////////////////////////////////////////////
		virtual void RequestStatePushTransition(IState* newState) = 0;

		///////////////////////////////////////////////////////////
	    /// \brief State callback for when a state wants to transition back
	    ///	to a state that was most recently pushed
	    /// input:  none
	    /// output: none
	    ////////////////////////////////////////////////////////////
		virtual bool RequestStatePopTransition() = 0;

		///////////////////////////////////////////////////////////
	    /// \brief State callback for when a state wants to terminate the game
	    ///   (useful for a state that has a quit option, ex: menu)
	    /// input:  none
	    /// output: none
	    ////////////////////////////////////////////////////////////
		virtual void RequestProgramTermination() = 0;

		///////////////////////////////////////////////////////////
	    /// \brief State callback for when a state wants to resize the RenderWindow
	    /// input:  x_dim : u_int
	    /// input:  y_dim : u_int
	    /// output: none
	    ////////////////////////////////////////////////////////////
		virtual void RequestWindowResize(unsigned x_dim, unsigned y_dim) = 0;

		///////////////////////////////////////////////////////////
	    /// \brief State callback for when a state wants to move the window
	    /// input:  x_dir : int
	    /// input:  y_dir : int
	    /// output: none
	    ////////////////////////////////////////////////////////////
		virtual void RequestWindowTranslation(int x_dir, int y_dir) = 0;

		virtual void RequestPlayAgain() {}

		virtual void RequestPause() {}

		virtual void RequestGameOver(int score) {}

		virtual void RequestOptions() {}

		virtual void RequestMute() {}
		virtual bool RequestMuteStatus() { return false; }

	};
}