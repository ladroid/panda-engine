#include "Singleton.h"

Singleton* Singleton::_singleton = 0;
extern std::unique_ptr<Singleton> singleton (Singleton::getInstance());