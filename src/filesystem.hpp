#ifndef FILESYSTEM_HPP_
#define FILESYSTEM_HPP_

#include <string>
#include <vector>
#include <map>

#include "plague.hpp"

#include <zip.h>

namespace Plague
{
	class Filesystem
	{
	public:
		Filesystem(const std::string &rootFolder, bool isDebug = false);
		~Filesystem();

		void AddModDirectory(const std::string &modName);

		const byte * ReadFile(const std::string &path, size_t *size);
		void DestroyFile(const char * file);

	private:
		void LoadZip(const std::string &zipFile, const std::string &modName);
		void LoadLoose(const std::string &path, const std::string &virtPath);

		bool IsDirectory(const std::string &path);

	private:
		bool isDebug;
		std::string rootFolder;

		std::vector<zip_t*> zipArchives;
		std::map<std::string, zip_t*> archiveMapping;
		std::map<std::string, std::string> index;

	};
}

#endif
