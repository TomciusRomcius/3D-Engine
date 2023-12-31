#pragma once
class IWindow
{
public:
	virtual void Initialize(std::function<void()> start, std::function<void()> update) = 0;
};

