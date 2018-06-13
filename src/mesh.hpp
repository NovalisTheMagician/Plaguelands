#ifndef MESH_HPP_
#define MESH_HPP_

#include "plague.hpp"

#include <glm\glm.hpp>

namespace Plague
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoord;
	};

	class VertexFormat
	{
	public:
		VertexFormat();
		~VertexFormat();

		void Use() const;

	private:


	};

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		void SetVertices(const std::vector<Vertex> &vertices, int frame);
		void SetIndices(const std::vector<ushort> &indices);

		void Draw(int frame);

		bool HasAnimation();

	private:

	};
}

#endif
