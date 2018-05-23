#ifndef FILESYSTEM_HPP_
#define FILESYSTEM_HPP_

#include <string>
#include <vector>
#include <map>

#include "miniz.h"

namespace Plague
{
	class Filesystem
	{
	public:
		Filesystem(const std::string &rootFolder, bool isDebug = false);
		~Filesystem();

		void AddModDirectory(const std::string &modName);

		const char * ReadFile(const std::string &path, size_t *size);
		void DestroyFile(const char * file);

	private:
		void LoadZip(const std::string &zipFile, const std::string &modName);
		void LoadLoose(const std::string &path, const std::string &virtPath);

	private:
		bool isDebug;
		std::string rootFolder;

		std::vector<mz_zip_archive*> zipArchives;
		std::map<std::string, mz_zip_archive*> archiveMapping;
		std::map<std::string, std::string> index;

	};
}

#endif
