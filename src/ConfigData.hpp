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

#ifndef MILITUM_CONFIG_DATA_HPP_
#define MILITUM_CONFIG_DATA_HPP_

#include <Siv3D.hpp>
#include "ConfigFile.hpp"

namespace Militum
{
	struct ConfigData
	{
	public:
		void reload(const TOMLReader& toml)
		{
			S3DCFG_RELOAD_SECTION(pathSetting_);
			S3DCFG_RELOAD_SECTION(csvSetting_);
			S3DCFG_RELOAD_SECTION(accessorSetting_);
		}

		/// <summary>
		/// 入出力設定
		/// </summary>
		struct PathSetting
		{
			void reload(const TOMLReader& toml)
			{
				S3DCFG_LOAD_SECTION(U"PathSetting");
				S3DCFG_LOAD_VALUE(csvDir);
				S3DCFG_LOAD_VALUE(binaryDir);
				S3DCFG_LOAD_VALUE(headerDir);
			}

			String csvDir;
			String binaryDir;
			String headerDir;

		} pathSetting_;

		/// <summary>
		/// 入力するCSVファイルに関する設定
		/// </summary>
		struct CsvSetting
		{
			void reload(const TOMLReader& /*toml*/)
			{
				// none TODO: コメント行有効フラグを追加する
			}
		} csvSetting_;

		/// <summary>
		/// 出力するヘッダファイルに関する設定
		/// </summary>
		struct AccessorSetting
		{
			void reload(const TOMLReader& toml)
			{
				S3DCFG_LOAD_SECTION(U"AccessorSetting");
				S3DCFG_LOAD_VALUE(namespaceValue);
				S3DCFG_LOAD_VALUE(loadBinaryDir);
			}

			String namespaceValue;
			String loadBinaryDir;

		} accessorSetting_;
	};
}

#endif // MILITUM_CONFIG_DATA_HPP_