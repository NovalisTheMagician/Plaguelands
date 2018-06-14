#ifndef LUA_SCRIPTENGINE_HPP_
#define LUA_SCRIPTENGINE_HPP_

#include "plague.hpp"
#include "scriptengine.hpp"

namespace Plague
{
	class LuaScriptEngine : public ScriptEngine
	{
	public:
		LuaScriptEngine();
		~LuaScriptEngine();

		bool Init(const ScriptEngineInfo &info);
		void Destroy();

		bool LoadScript(const std::string &scriptName);
		void ExecuteScript(const std::string &script);

		void AddScriptFunction(ScriptFunction func, const std::string funcName);

	private:
		lua_State *luaState;

	};
}

#endif
