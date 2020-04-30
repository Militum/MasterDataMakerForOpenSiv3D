//-----------------------------------------------
//
// TableConveterForOpenSiv3D
//
// Copyright (c) 2019-2020 Militum
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//
//-----------------------------------------------

#include <Siv3D.hpp> // OpenSiv3D v0.4.2
#include "Constant.hpp"
#include "ConfigData.hpp"
#include "MasterData.hpp"
#include "AccessorExport.hpp"
#include "BinaryExport.hpp"
#include "MasterDataException.hpp"

void Main()
{
	using namespace Militum;
	using Config = ConfigFile<ConfigData>;

	const FilePath configPath = U"config.toml";
	Config config;

	try
	{
		// Config ファイルを読み込み
		config.reload(configPath);

		if (!FileSystem::IsDirectory(config.pathSetting_.csvDir))
		{
			return;
		}

		if (FileSystem::IsDirectory(config.pathSetting_.binaryDir))
		{
			FileSystem::Remove(config.pathSetting_.binaryDir);
		}
		FileSystem::CreateDirectories(config.pathSetting_.binaryDir);

		if (FileSystem::IsDirectory(config.pathSetting_.headerDir))
		{
			FileSystem::Remove(config.pathSetting_.headerDir);
		}
		FileSystem::CreateDirectories(config.pathSetting_.headerDir);


		Array<FilePath> contents = FileSystem::DirectoryContents(config.pathSetting_.csvDir);
		std::map<String, MasterData> masterDataMap;
		for (const String& content : contents)
		{
			if (!(FileSystem::IsFile(content)
				&& FileSystem::Extension(content).compare(CSV) == 0))
			{
				continue;
			}
			const String baseName = FileSystem::BaseName(content);
			MasterData data{ content };
			Print(baseName + U" Load...");
			data.initialize();
			masterDataMap.insert({ baseName, data });
		}

		for (const auto& masterData : masterDataMap)
		{
			const String baseName = masterData.first;
			Print(baseName + U" Export Accessor...");
			const FilePath accessorPath{ config.pathSetting_.headerDir + U"/" + baseName + EXTENSION_HPP };
			TextWriter accessorWriter(accessorPath);
			Accessor::execute(accessorWriter, masterData.second, config);

			Print(baseName + U" Export Binary...");
			const FilePath binaryPath{ config.pathSetting_.binaryDir + U"/" + baseName + EXTENSION_BIN };
			Serializer<BinaryWriter> binaryWriter(binaryPath);
			Binary::execute(binaryWriter, masterData.second);

			Print(baseName + U" Successed...");
		}
	}
	catch (const ConfigError& error)
	{
		error.show();
		return;
	}
	catch (MasterDataException exception)
	{
		exception.show(); // どこまで成功したか表示するため、早期returnなし
	}
	catch (...)
	{
		System::ShowMessageBox(U"Error", U"原因不明のエラーが発生...", MessageBoxStyle::Error);
	}

	System::SetTerminationTriggers(UserAction::AnyKeyDown);
	Print(U"Please Press Any Key...");
	while (System::Update())
	{
	}
}
