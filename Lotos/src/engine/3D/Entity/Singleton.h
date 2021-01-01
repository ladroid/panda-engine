#pragma once

#include <string>
#include <memory>

class Singleton
{
private:
	std::string file = "";
	static Singleton* _singleton;
public:
	static Singleton* getInstance()
	{
		if (!_singleton)
		{
			_singleton = new Singleton;
		}
		return _singleton;
	}
	void setModel(std::string filename)
	{
		this->file = filename;
	}

	std::string getModel()
	{
		return this->file;
	}
};