#include "filesystem.hpp"

#include <filesystem>
#include <fstream>

namespace Plague
{
	using std::string;
	using std::vector;
	using std::map;
	using std::fstream;

	namespace fs = std::filesystem;

	Filesystem::Filesystem(const string &rootFolder, bool isDebug)
		: rootFolder(rootFolder), isDebug(isDebug)
	{

	}

	Filesystem::~Filesystem()
	{
		for (mz_zip_archive* archive : zipArchives)
		{
			mz_zip_reader_end(archive);
			delete archive;
		}

		zipArchives.clear();

	}

	void Filesystem::AddModDirectory(const string &modName)
	{
		for (auto & file : fs::directory_iterator(rootFolder + modName + "\\"))
		{
			if (file.is_regular_file())
			{
				if (!isDebug && file.path().extension().string().compare(".zip"))
				{
					LoadZip(file.path().string(), modName);
				}
				else if(isDebug)
				{
					string fileName = file.path().filename().string();
					string virtualFilePath = "/" + fileName;
					string filePath = file.path().relative_path().string();
					index[virtualFilePath] = filePath;
				}
			}
			else if (isDebug && file.is_directory())
			{
				string virtPath = file.path().filename().string();
				LoadLoose(file.path().relative_path().string(), virtPath);
			}
		}
	}

	void Filesystem::LoadLoose(const string &path, const string &virtPath)
	{
		for (auto & file : fs::directory_iterator(path))
		{
			if (file.is_regular_file())
			{
				string fileName = file.path().filename().string();
				string virtualFilePath = "/" + virtPath + "/" + fileName;
				string filePath = file.path().relative_path().string();
				index[virtualFilePath] = filePath;
			}
			else if (file.is_directory())
			{
				string virtPath = virtPath + "/" + file.path().filename().string();
				LoadLoose(file.path().relative_path().string(), virtPath);
			}
		}
	}

	void Filesystem::LoadZip(const string &zipFile, const string &modName)
	{
		const char * zipFileName = zipFile.c_str();
		mz_zip_archive *archive = new mz_zip_archive;
		mz_bool status = mz_zip_reader_init_file(archive, zipFileName, 0);
		if (!status)
		{
			return;
		}

		zipArchives.push_back(archive);

		string zipName = zipFile.substr(zipFile.find_last_of('\\'));
		zipName = zipName.substr(0, zipName.find_last_of('.'));
		string archiveID = "@" + modName + ":" + zipName;

		archiveMapping[archiveID] = archive;

		size_t numFiles = mz_zip_reader_get_num_files(archive);
		for (int i = 0; i < numFiles; ++i)
		{
			mz_zip_archive_file_stat fileStat;
			if (!mz_zip_reader_file_stat(archive, i, &fileStat))
				continue;

			if (mz_zip_reader_is_file_a_directory(archive, i))
				continue;

			string fileName = fileStat.m_filename;
			index[fileName] = archiveID + "/" + fileName;
		}
	}

	const char * Filesystem::ReadFile(const string &path, size_t *size)
	{
		string indexPath = index[path];
		if (indexPath[0] == '@')
		{
			string archiveID = indexPath.substr(0, indexPath.find_first_of('/'));
			mz_zip_archive *archive = archiveMapping[archiveID];
			string fileName = indexPath.substr(indexPath.find_first_of('/'));
			int index = mz_zip_reader_locate_file(archive, fileName.c_str(), nullptr, 0);
			if (index >= 0)
			{
				mz_zip_archive_file_stat fileStat;
				mz_zip_reader_file_stat(archive, index, &fileStat);

				size_t fileSize = fileStat.m_uncomp_size;
				char *buffer = new char[fileSize];
				mz_bool res = mz_zip_reader_extract_file_to_mem(archive, fileName.c_str(), buffer, fileSize, 0);
				if (res)
				{
					*size = fileSize;
					return buffer;
				}
			}
		}
		else
		{
			fstream file(indexPath, std::ios::in | std::ios::binary | std::ios::ate);
			if (file.is_open())
			{
				size_t fileSize = file.tellg();
				char *buffer = new char[fileSize];
				file.read(buffer, fileSize);

				*size = fileSize;
				return buffer;
			}
		}

		return nullptr;
	}

	void Filesystem::DestroyFile(const char* file)
	{
		delete[] file;
	}
}
