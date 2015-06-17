// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <stack>
/**
 * 
 */
template<class T>
class GAUNTLET_API StateManager
{
public:
	StateManager();
	~StateManager();

	void EnterNewState(T newState);
	void EnterPreviousState();
	bool IsAtRoot();
	bool HasCurrent();
	TSubclassOf<T> GetCurrent();
private:
	TSubclassOf<T> Current;
	bool bIsCurrentValid;
	std::stack<TSubclassOf<T>> History;
};
