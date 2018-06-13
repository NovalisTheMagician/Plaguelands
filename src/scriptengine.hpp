#ifndef SCRIPTENGINE_HPP_
#define SCRIPTENGINE_HPP_

namespace Plague
{
	struct ScriptEngineInfo
	{

	};

	class ScriptEngine
	{
	public:
		virtual ~ScriptEngine() = 0;

		virtual bool Init(const ScriptEngineInfo &info) = 0;
		virtual void Destroy() = 0;

	};
}

#endif
