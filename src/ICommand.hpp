#pragma once

class IReceiver;
class ICommand
{
public:
	ICommand(IReceiver* rcvr) : m_pReceiver{ rcvr } {}
	virtual			~ICommand() {}
	virtual void		Execute() = 0;
protected:
	IReceiver* m_pReceiver;
};