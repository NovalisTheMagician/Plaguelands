#ifndef SCRIPTENGINE_HPP_
#define SCRIPTENGINE_HPP_

#include "plague.hpp"

namespace Plague
{
	class ScriptEngine;

	typedef int(*ScriptFunction(const ScriptEngine &engine));

	struct ScriptEngineInfo
	{

	};

	class ScriptEngine
	{
	public:
		virtual ~ScriptEngine() = 0;

		virtual bool Init(const ScriptEngineInfo &info) = 0;
		virtual void Destroy() = 0;

		virtual bool LoadScript(const std::string &scriptName) = 0;
		virtual void ExecuteScript(const std::string &script) = 0;

		virtual void AddScriptFunction(ScriptFunction func, const std::string funcName) = 0;

	};
}

#endif
