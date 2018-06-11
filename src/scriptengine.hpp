#ifndef SCRIPTENGINE_HPP_
#define SCRIPTENGINE_HPP_

#include <lua.h>

namespace Plague
{
	class ScriptEngine
	{
	public:
		ScriptEngine();
		~ScriptEngine();

		bool Init();
		void Destroy();

	private:
		lua_State *luaState;

	};
}

#endif
