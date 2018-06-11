#include "scriptengine.hpp"

#include <lauxlib.h>

namespace Plague
{
	ScriptEngine::ScriptEngine()
		: luaState(nullptr)
	{

	}

	ScriptEngine::~ScriptEngine()
	{

	}

	bool ScriptEngine::Init()
	{
		luaState = luaL_newstate();
	}

	void ScriptEngine::Destroy()
	{
		lua_close(luaState);
	}
}
