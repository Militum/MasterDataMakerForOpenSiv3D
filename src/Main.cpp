//-----------------------------------------------
//
// TableConveterForOpenSiv3D
//
// Copyright (c) 2019 Militum
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//
//-----------------------------------------------

#include <Siv3D.hpp> // OpenSiv3D v0.3.2
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
		for (const String& content : contents)
		{
			if (!(FileSystem::IsFile(content)
				&& FileSystem::Extension(content).compare(CSV) == 0))
			{
				continue;
			}
			const String baseName = FileSystem::BaseName(content);
			MasterData data{ content };

			Print(baseName + U" Start...");

			const FilePath accessorPath{ config.pathSetting_.headerDir + U"/" + baseName + EXTENSION_HPP };
			TextWriter accessorWriter(accessorPath);
			Accessor::execute(accessorWriter, data, config);

			const FilePath binaryPath{ config.pathSetting_.binaryDir + U"/" + baseName + EXTENSION_BIN };
			Serializer<BinaryWriter> binaryWriter(binaryPath);
			Binary::execute(binaryWriter, data);

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

	System::SetExitEvent(WindowEvent::AnyKey);
	Print(U"Please Press Any Key...");
	while (System::Update())
	{
	}
}
