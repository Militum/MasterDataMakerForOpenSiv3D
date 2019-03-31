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
		/// コンストラクタ
		/// </summary>
		/// <param name="path"></param>
		MasterData(const FilePath& path)
			: CSVData(path)
		{
			initialize();
		}

		/// <summary>
		/// カラム情報取得
		/// </summary>
		/// <returns></returns>
		inline Array<String> getColumns() const
		{
			return getRow(COLUMNS_ROW_NUMBER);
		}

		/// <summary>
		/// 型情報取得
		/// </summary>
		/// <returns></returns>
		inline Array<String> getTypes() const
		{
			return getRow(TYPES_ROW_NUMBER);
		}

		/// <summary>
		/// データ情報取得
		/// </summary>
		/// <returns></returns>
		inline Array<MasterDataRecord> getRecords() const
		{
			return values_;
		}

		/// <summary>
		/// レコード数取得
		/// </summary>
		/// <returns></returns>
		inline uint32 getRecordSize() const
		{
			return values_.size();
		}

	private:

		/// <summary>
		/// 初期化
		/// </summary>
		void initialize()
		{
			if (getColumns().size() != getTypes().size())
			{
				throw MasterDataException(U"カラム数と型の定義数が異なります");
			}

			// TODO: ここにコメント行の解析を追加する
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
		/// インデックスが妥当か判定
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		inline bool isValidIndex(const uint32 index) const
		{
			return 0 <= index && index < values_.size();
		}

	private:

		// 2行目以降を取る必要があるため一旦別変数化
		Array<MasterDataRecord> values_;
	};
}

#endif // MILITUM_MASTERDATA_HPP_