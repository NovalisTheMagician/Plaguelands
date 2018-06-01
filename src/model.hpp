#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "mesh.hpp"
#include "texture.hpp"

#include <glm\glm.hpp>

namespace Plague
{
	struct Tag
	{
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 up;
	};

	class Model
	{
	public:
		Model();
		~Model();

		bool Load(const byte *data, std::size_t size);

		void SetFrame(int frame);

		void Update();

		Tag GetTag(const std::string &tagName);
		Tag GetTagAtFrame(const std::string &tagName, int frame);

	private:
		Mesh mesh;
		std::map<std::string, std::map<int, Tag>> tags;

		bool loaded;

	};
}

#endif
