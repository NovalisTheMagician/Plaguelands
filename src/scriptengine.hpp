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
		virtual void ExecuteString(const std::string &script) = 0;

		virtual bool GetParameter(int *value, int paraIdx) = 0;
		virtual bool GetParameter(float *value, int paraIdx) = 0;
		virtual bool GetParameter(std::string *value, int paraIdx) = 0;
		virtual bool GetParameter(bool *value, int paraIdx) = 0;

		virtual void PushResult(int value) = 0;
		virtual void PushResult(float value) = 0;
		virtual void PushResult(std::string value) = 0;
		virtual void PushResult(bool value) = 0;

		virtual void AddScriptFunction(ScriptFunction func, const std::string funcName) = 0;

	};
}

#endif
