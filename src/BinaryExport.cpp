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

#include "Constant.hpp"
#include "BinaryExport.hpp"
#include <map>

namespace Militum
{
	enum class WriteType
	{
		Unknown,	// 書き込まない
		Int32,
		UInt32,
		Int64,
		UInt64,
		Float,
		Double,
		String,
	};

	using WriteMap = std::unordered_map<String, WriteType>;

	WriteMap getTypeMap()
	{
		WriteMap typeMap;
		typeMap.insert(std::make_pair<String, WriteType>(U"int32", WriteType::Int32));
		typeMap.insert(std::make_pair<String, WriteType>(U"int32_t", WriteType::Int32));
		typeMap.insert(std::make_pair<String, WriteType>(U"int", WriteType::Int32));
		typeMap.insert(std::make_pair<String, WriteType>(U"int64", WriteType::Int64));
		typeMap.insert(std::make_pair<String, WriteType>(U"int64_t", WriteType::Int64));

		// 符号なし整数型
		typeMap.insert(std::make_pair<String, WriteType>(U"uint", WriteType::UInt32));
		typeMap.insert(std::make_pair<String, WriteType>(U"uint32", WriteType::UInt32));
		typeMap.insert(std::make_pair<String, WriteType>(U"uint32_t", WriteType::UInt32));
		typeMap.insert(std::make_pair<String, WriteType>(U"uint64", WriteType::UInt64));
		typeMap.insert(std::make_pair<String, WriteType>(U"uint64_t", WriteType::UInt64));

		// 小数点
		typeMap.insert(std::make_pair<String, WriteType>(U"float", WriteType::Float));
		typeMap.insert(std::make_pair<String, WriteType>(U"double", WriteType::Double));

		// 文字列
		typeMap.insert(std::make_pair<String, WriteType>(U"String", WriteType::String));

		return std::move(typeMap);
	}

	void writeBinary(Serializer<BinaryWriter>& binaryWriter, const WriteType writeType, const MasterDataRecord& record, const uint32 index)
	{
		switch (writeType)
		{
		case WriteType::Int32:
			binaryWriter(record.getOpt<int32>(index).value());
			break;
		case WriteType::UInt32:
			binaryWriter(record.getOpt<uint32>(index).value());
			break;
		case WriteType::Int64:
			binaryWriter(record.getOpt<int64>(index).value());
			break;
		case WriteType::UInt64:
			binaryWriter(record.getOpt<uint64>(index).value());
			break;
		case WriteType::Float:
			binaryWriter(record.getOpt<float>(index).value());
			break;
		case WriteType::Double:
			binaryWriter(record.getOpt<double>(index).value());
			break;
		case WriteType::String:
			binaryWriter(record.getOpt<String>(index).value());
			break;
		default:
			throw MasterDataException(U"非対応の型を使用しています");
		}
	}

	namespace Binary
	{
		void execute(Serializer<BinaryWriter>& binaryWriter, const MasterData& masterData)
		{
			if (!binaryWriter.getWriter().isOpened())
			{
				throw MasterDataException(U"バイナリファイルが開けていません");
			}

			const size_t columnSize = masterData.getColumns().size();
			auto types = masterData.getTypes();
			auto records = masterData.getRecords();

			WriteMap typeMap = getTypeMap();
			binaryWriter(masterData.getRecordSize());
			for (auto& record : records)
			{
				for (uint32 index = 0; index < columnSize; ++index)
				{
					const String type = types.at(index);
					if (typeMap.count(type) == 0)
					{
						throw MasterDataException(U"Unknown type : " + type);
					}
					writeBinary(binaryWriter, typeMap[type], record, index);
				}
			}
		}
	}
}