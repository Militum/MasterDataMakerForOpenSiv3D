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

#ifndef MILITUM_MASTERDATARECORD_HPP_
#define MILITUM_MASTERDATARECORD_HPP_

#include <Siv3D.hpp>
#include "MasterDataException.hpp"

namespace Militum
{
	class MasterDataRecord
	{
	public:

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="data"></param>
		MasterDataRecord(const Array<String>& data)
			: maxIndex_(data.size())
			, values_(data)
		{
		}

		/// <summary>
		/// �o�C�i���������݂̍ہA��������w�肵���^�Ŏ擾���Ă��珑������
		/// </summary>
		template <class Type>
		Optional<Type> getOpt(const uint32 index) const
		{
			if (!isValidIndex(index))
			{
				throw MasterDataException(U"�ُ��index���w�肳��܂���");
			}

			return ParseOpt<Type>(values_.at(index));
		}

	private:

		/// <summary>
		/// �C���f�b�N�X���Ó�������
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		inline bool isValidIndex(const uint32 index) const
		{
			return 0 <= index && index < maxIndex_;
		}

	private:

		const size_t maxIndex_;

		const Array<String> values_;
	};
}

#endif // MILITUM_MASTERDATARECORD_HPP_