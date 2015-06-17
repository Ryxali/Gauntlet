// Fill out your copyright notice in the Description page of Project Settings.

#include "Gauntlet.h"
#include "StateManager.h"

template<class T>
StateManager<T>::StateManager() : Current(), History()
{
}

template<class T>
StateManager<T>::~StateManager()
{
}

template<class T>
void StateManager<T>::EnterNewState(T newState)
{
	if (bIsCurrentValid)
	{
		History.push(current);
	}
	Current = newState;
}

template<class T>
void StateManager<T>::EnterPreviousState()
{
	if (!IsAtRoot())
	{
		Current = History.top();
		History.pop();
	}
}

template<class T>
bool StateManager<T>::IsAtRoot()
{
	return History.size() == 0;
}

template<class T>
bool StateManager<T>::HasCurrent()
{
	return Current != NULL;
}

template<class T>
TSubclassOf<T> StateManager<T>::GetCurrent()
{
	return Current;
}

