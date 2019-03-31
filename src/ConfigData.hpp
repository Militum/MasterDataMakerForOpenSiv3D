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
		/// ���o�͐ݒ�
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
		/// ���͂���CSV�t�@�C���Ɋւ���ݒ�
		/// </summary>
		struct CsvSetting
		{
			void reload(const TOMLReader& /*toml*/)
			{
				// none TODO: �R�����g�s�L���t���O��ǉ�����
			}
		} csvSetting_;

		/// <summary>
		/// �o�͂���w�b�_�t�@�C���Ɋւ���ݒ�
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