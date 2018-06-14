#include "filesystem.hpp"

#include <filesystem>
#include <fstream>

#include <system_error>

namespace Plague
{
	using std::string;
	using std::vector;
	using std::map;
	using std::fstream;
	using std::error_code;

	namespace fs = std::filesystem;

	Filesystem::Filesystem(const string &rootFolder, bool isDebug)
		: rootFolder(rootFolder), isDebug(isDebug)
	{

	}

	Filesystem::~Filesystem()
	{
		for (zip_t* archive : zipArchives)
		{
			zip_close(archive);
		}

		zipArchives.clear();
	}

	void Filesystem::AddModDirectory(const string &modName)
	{
		error_code ec;

		string filePath = rootFolder + modName + "\\";
		for (auto & file : fs::directory_iterator(filePath, ec))
		{
			if (file.is_regular_file())
			{
				string fileName = file.path().filename().string();
				string extension = file.path().extension().string();
				string relFilePath = file.path().relative_path().string();

				if (!isDebug && extension.compare(".zip") == 0)
				{
					LoadZip(relFilePath, modName);
				}
				else if(isDebug)
				{
					string virtualFilePath = "/" + fileName;
					index[virtualFilePath] = relFilePath;
				}
			}
			else if (isDebug && file.is_directory())
			{
				string virtPath = file.path().filename().string();
				LoadLoose(file.path().relative_path().string(), virtPath);
			}
		}

		if (ec)
		{
			//print it somewhere
		}
	}

	void Filesystem::LoadLoose(const string &path, const string &virtPath)
	{
		for (auto & file : fs::directory_iterator(path))
		{
			string filePath = file.path().relative_path().string();
			string fileName = file.path().filename().string();

			if (file.is_regular_file())
			{
				string virtualFilePath = "/" + virtPath + "/" + fileName;
				index[virtualFilePath] = filePath;
			}
			else if (file.is_directory())
			{
				string newVirtPath = virtPath + "/" + fileName;
				LoadLoose(filePath, newVirtPath);
			}
		}
	}

	void Filesystem::LoadZip(const string &zipFile, const string &modName)
	{
		const char * zipFileName = zipFile.c_str();

		int error;
		zip_t *archive = zip_open(zipFileName, ZIP_RDONLY, &error);
		if (!archive)
		{
			char buf[100];
			zip_error_to_str(buf, sizeof buf, error, errno);
			return;
		}

		zipArchives.push_back(archive);

		string zipName = zipFile.substr(zipFile.find_last_of('\\'));
		zipName = zipName.substr(0, zipName.find_last_of('.'));
		string archiveID = "@" + modName + ":" + zipName;

		archiveMapping[archiveID] = archive;

		zip_int64_t numFiles = zip_get_num_entries(archive, 0);
		for (zip_int64_t i = 0; i < numFiles; ++i)
		{
			zip_stat_t fileStat;
			if (zip_stat_index(archive, i, 0, &fileStat) != 0)
				continue;

			string fileName = fileStat.name;

			if (IsDirectory(fileName))
				continue;

			index[fileName] = archiveID + "/" + fileName;
		}
	}

	bool Filesystem::IsDirectory(const string &path)
	{
		size_t pos = path.find_last_of('/');
		return pos == path.size() - 1;
	}

	const byte * Filesystem::ReadFile(const string &path, size_t *size) const
	{
		string indexPath = index.at(path);
		if (indexPath[0] == '@')
		{
			string archiveID = indexPath.substr(0, indexPath.find_first_of('/'));
			zip_t *archive = archiveMapping.at(archiveID);
			string fileName = indexPath.substr(indexPath.find_first_of('/'));

			zip_int64_t index = zip_name_locate(archive, fileName.c_str(), 0);
			zip_stat_t fileStat;
			if (zip_stat_index(archive, index, 0, &fileStat) == 0)
			{
				size_t fileSize = static_cast<size_t>(fileStat.size);
				byte *buffer = new byte[fileSize];

				zip_file_t *zipFile;
				zipFile = zip_fopen_index(archive, index, 0);
				zip_int64_t len = zip_fread(zipFile, buffer, fileSize);
				if (len == fileSize)
				{
					*size = fileSize;
					return buffer;
				}
				zip_fclose(zipFile);
			}
		}
		else
		{
			fstream file(indexPath, std::ios::in | std::ios::binary | std::ios::ate);
			if (file.is_open())
			{
				size_t fileSize = static_cast<size_t>(file.tellg());
				byte *buffer = new byte[fileSize];
				file.read(reinterpret_cast<char*>(buffer), fileSize);

				*size = fileSize;
				return buffer;
			}
		}
		return nullptr;
	}
}
