#pragma once
class BoardBehavior
{
public:
	virtual ~BoardBehavior() = default;
	virtual void begin() = 0;
	virtual void stop() = 0;
};

