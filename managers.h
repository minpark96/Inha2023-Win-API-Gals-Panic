#pragma once
class Managers
{
private:
	Managers() { instance = *this; };
	static Managers instance;
public:
	static Managers& getInstance() { return instance; };
	Managers(const Managers&) = delete;
	Managers& operator=(const Managers&) = delete;
	Managers(Managers&&) = delete;
	Managers& operator=(Managers&&) = delete;
};

