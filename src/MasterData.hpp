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

#ifndef MILITUM_MASTERDATA_HPP_
#define MILITUM_MASTERDATA_HPP_

#include <Siv3D.hpp>
#include "MasterDataRecord.hpp"
#include "MasterDataException.hpp"

namespace Militum
{
	class MasterData : public CSVData
	{
		constexpr static uint32 COLUMNS_ROW_NUMBER = 0;
		constexpr static uint32 TYPES_ROW_NUMBER = 1;
		constexpr static uint32 VALUES_ROW_NUMBER = 2;
	public:

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="path"></param>
		MasterData(const FilePath& path)
			: CSVData(path)
		{
			initialize();
		}

		/// <summary>
		/// �J�������擾
		/// </summary>
		/// <returns></returns>
		inline Array<String> getColumns() const
		{
			return getRow(COLUMNS_ROW_NUMBER);
		}

		/// <summary>
		/// �^���擾
		/// </summary>
		/// <returns></returns>
		inline Array<String> getTypes() const
		{
			return getRow(TYPES_ROW_NUMBER);
		}

		/// <summary>
		/// �f�[�^���擾
		/// </summary>
		/// <returns></returns>
		inline Array<MasterDataRecord> getRecords() const
		{
			return values_;
		}

		/// <summary>
		/// ���R�[�h���擾
		/// </summary>
		/// <returns></returns>
		inline uint32 getRecordSize() const
		{
			return values_.size();
		}

	private:

		/// <summary>
		/// ������
		/// </summary>
		void initialize()
		{
			if (getColumns().size() != getTypes().size())
			{
				throw MasterDataException(U"�J�������ƌ^�̒�`�����قȂ�܂�");
			}

			// TODO: �����ɃR�����g�s�̉�͂�ǉ�����
			for (
				uint32 index = VALUES_ROW_NUMBER, maxIndex = rows() - VALUES_ROW_NUMBER;
				index <= maxIndex;
				++index
			)
			{
				values_.emplace_back(getRow(index));
			}
		}

		/// <summary>
		/// �C���f�b�N�X���Ó�������
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		inline bool isValidIndex(const uint32 index) const
		{
			return 0 <= index && index < values_.size();
		}

	private:

		// 2�s�ڈȍ~�����K�v�����邽�߈�U�ʕϐ���
		Array<MasterDataRecord> values_;
	};
}

#endif // MILITUM_MASTERDATA_HPP_