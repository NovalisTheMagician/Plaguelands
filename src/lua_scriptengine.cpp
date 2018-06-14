#include "lua_scriptengine.hpp"

#include <assert.h>

namespace Plague
{
	using std::string;

	LuaScriptEngine::LuaScriptEngine()
		: luaState(nullptr)
	{

	}

	LuaScriptEngine::~LuaScriptEngine()
	{

	}

	bool LuaScriptEngine::Init(const ScriptEngineInfo &info)
	{
		if (luaState != nullptr)
			lua_close(luaState);

		luaState = luaL_newstate();

		basePath = info.assetBasePath;

		return true;
	}

	void LuaScriptEngine::Destroy()
	{
		if(luaState != nullptr)
			lua_close(luaState);
		luaState = nullptr;
	}

	bool LuaScriptEngine::LoadScript(const std::string &scriptName) const
	{
		return luaL_loadfile(luaState, scriptName.c_str()) == LUA_OK;
	}

	void LuaScriptEngine::ExecuteString(const std::string &script) const
	{
		luaL_dostring(luaState, script.c_str());
	}

	void LuaScriptEngine::AddScriptFunction(lua_CFunction func, const std::string funcName) const
	{
		lua_register(luaState, funcName.c_str(), func);
	}
}
