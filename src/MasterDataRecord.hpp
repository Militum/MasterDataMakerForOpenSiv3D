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
		/// コンストラクタ
		/// </summary>
		/// <param name="data"></param>
		MasterDataRecord(const Array<String>& data)
			: maxIndex_(data.size())
			, values_(data)
		{
		}

		/// <summary>
		/// バイナリ書き込みの際、文字列を指定した型で取得してから書き込む
		/// </summary>
		template <class Type>
		Optional<Type> getOpt(const uint32 index) const
		{
			if (!isValidIndex(index))
			{
				throw MasterDataException(U"異常なindexが指定されました");
			}
			const String value = values_.at(index);
			if (value.isEmpty())
			{
				// 空文字の場合は予期せぬデータを混入させないために例外にしておく
				throw MasterDataException(U"文字列以外は空文字禁止です");
			}
			return ParseOpt<Type>(value);
		}

		/// <summary>
		/// バイナリ書き込みの際、文字列を指定した型で取得してから書き込む
		/// </summary>
		template <>
		Optional<String> getOpt(const uint32 index) const
		{
			if (!isValidIndex(index))
			{
				throw MasterDataException(U"異常なindexが指定されました");
			}

			return values_.at(index);
		}

	private:

		/// <summary>
		/// インデックスが妥当か判定
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