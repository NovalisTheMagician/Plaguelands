#ifndef LUA_SCRIPTENGINE_HPP_
#define LUA_SCRIPTENGINE_HPP_

#include "plague.hpp"

namespace Plague
{
	struct ScriptEngineInfo
	{
		std::string assetBasePath;
	};

	class LuaScriptEngine
	{
	public:
		LuaScriptEngine();
		~LuaScriptEngine();

		bool Init(const ScriptEngineInfo &info);
		void Destroy();

		bool LoadScript(const std::string &scriptName) const;
		void ExecuteString(const std::string &script) const;

		void AddScriptFunction(lua_CFunction func, const std::string funcName) const;

	private:
		lua_State *luaState;
		std::string basePath;

	};
}

#endif
