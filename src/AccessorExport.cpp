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
#include "AccessorExport.hpp"

namespace Militum
{
	/// <summary>
	/// ヘッダーファイルの署名
	/// </summary>
	/// <param name="writer"></param>
	/// <param name="filename"></param>
	void exportSignatureCode(TextWriter& writer, const String& filename)
	{
		writer.writeln(U"/**");
		writer.writeln(U"* @file " + filename + EXTENSION_HPP);
		writer.writeln(U"*");
		writer.writeln(U"* @brief This source was made by auto MasterData source code generate tool.");
		writer.writeln(U"*");
		writer.writeln(U"* @author MasterDataMakerForOpenSiv3D");
		writer.writeln(U"*/");
		writer.writeln();
	}

	/// <summary>
	/// インクルードガード名作成
	/// </summary>
	/// <param name="keyword"></param>
	/// <param name="classname"></param>
	/// <returns></returns>
	const String createIncludeGuardName(const String& keyword, const String& classname)
	{
		return keyword.uppercased() + U"_MASTERDATA_" + classname.uppercased() + U"_" + HPP.uppercased() + U"_";
	}

	/// <summary>
	/// インクルードガード開始
	/// </summary>
	/// <param name="writer"></param>
	/// <param name="keyword"></param>
	/// <param name="classname"></param>
	/// <returns></returns>
	void exportIncludeGuardBegin(TextWriter& writer, const String& keyword, const String& classname)
	{
		const String guardName = createIncludeGuardName(keyword, classname);
		writer.writeln(U"#ifndef " + guardName);
		writer.writeln(U"#define " + guardName);
		writer.writeln();
	}

	/// <summary>
	/// インクルードガード終了
	/// </summary>
	/// <param name="writer"></param>
	/// <param name="keyword"></param>
	/// <param name="classname"></param>
	/// <returns></returns>
	void exportIncludeGuardEnd(TextWriter& writer, const String& keyword, const String& classname)
	{
		writer.writeln(U"#endif // " + createIncludeGuardName(keyword, classname));
	}

	/// <summary>
	/// 名前空間開始
	/// </summary>
	/// <param name="writer"></param>
	/// <param name="name"></param>
	/// <returns></returns>
	void exportNameSpaceBegin(TextWriter& writer, const String& name)
	{
		writer.writeln(U"namespace " + name);
		writer.writeln(U"{");
		writer.writeln();
	}

	/// <summary>
	/// 名前空間終了
	/// </summary>
	/// <param name="writer"></param>
	/// <param name="name"></param>
	/// <returns></returns>
	void exportNameSpaceEnd(TextWriter& writer, const String& name)
	{
		writer.writeln(U"} // namespace " + name);
		writer.writeln();
	}

	/// <summary>
	/// Include 記述
	/// </summary>
	/// <param name="writer"></param>
	/// <returns></returns>
	void exportIncludePath(TextWriter& writer, const String& parentClassPath)
	{
		writer.writeln(U"#include <Siv3d.hpp>");
		writer.writeln(U"#include \"" + parentClassPath + U"MasterData.hpp\"");
		writer.writeln();
	}

	/// <summary>
	/// Accessorクラス書き出し
	/// </summary>
	/// <param name="writer"></param>
	/// <param name="baseName"></param>
	/// <param name="header"></param>
	/// <param name="labelIndex"></param>
	/// <returns></returns>
	void exportAccessor(TextWriter& writer, const String& baseName, const MasterData& masterData, const String& loadBinaryDirectory)
	{
		// 必要な時に初期化を行うとAccessorクラスを眺めた時に可読性が落ちるため、敢えて最初に初期化する
		const Array<String> columns = masterData.getColumns();
		const Array<String> types = masterData.getTypes();
		const uint32 columnSize = columns.size();
		const String structName = baseName + U"Record";
		const String accessorName = baseName + U"Accessor";

		writer.writeln(U"\t/// <summary>");
		writer.writeln(U"\t/// MasterData " + structName);
		writer.writeln(U"\t/// </summary>");
		writer.writeln(U"\tstruct " + structName);
		writer.writeln(U"\t{");
		writer.writeln(U"\t\ttemplate <class Archive>");
		writer.writeln(U"\t\tvoid SIV3D_SERIALIZE(Archive& archive)");
		writer.writeln(U"\t\t{");
		writer.writeln(U"\t\t\tarchive(");
		writer.writeln(U"\t\t\t\t" + columns.join(U",\n\t\t\t\t", U"", U""));
		writer.writeln(U"\t\t\t);");
		writer.writeln(U"\t\t}");
		writer.writeln();
		writer.writeln(U"\t\t" + *types.begin() + U" getKey() const");
		writer.writeln(U"\t\t{");
		writer.writeln(U"\t\t\treturn " + *columns.begin() + U";");
		writer.writeln(U"\t\t}");
		writer.writeln();
		writer.writeln(U"\t\t// variables");
		for (uint32_t i = 0; i < columnSize; ++i)
		{
			writer.writeln(U"\t\t" + types.at(i) + U" " + columns.at(i) + U";");
		}
		writer.writeln(U"\t};");
		writer.writeln();
		writer.writeln(U"\t/// <summary>");
		writer.writeln(U"\t/// MasterData " + accessorName);
		writer.writeln(U"\t/// </summary>");
		writer.writeln(U"\tclass " + accessorName + U" : public MasterData<" + *types.begin() + U", " + structName + U">");
		writer.writeln(U"\t{");
		writer.writeln(U"\tpublic:");
		writer.writeln(U"\t\t" + accessorName + U"()");
		writer.writeln(U"\t\t\t: MasterData(U\"" + loadBinaryDirectory + U"/" + baseName + EXTENSION_BIN + U"\")");
		writer.writeln(U"\t\t{");
		writer.writeln(U"\t\t}");
		writer.writeln(U"\t\tvirtual ~" + accessorName + U"()");
		writer.writeln(U"\t\t{");
		writer.writeln(U"\t\t}");
		writer.writeln(U"\t};");
		writer.writeln();
	}

	namespace Accessor
	{
		void execute(TextWriter& accessorWriter, const MasterData& masterData, const ConfigFile<ConfigData>& config)
		{
			if (!accessorWriter.isOpened())
			{
				throw MasterDataException(U"テキストファイルが開けていません");
			}
			const String className = FileSystem::BaseName(accessorWriter.path());
			const String namespaceValue = config.accessorSetting_.namespaceValue;
			const String loadBinaryDirectory = config.accessorSetting_.loadBinaryDir;
			const String parentClassPath = config.accessorSetting_.parentClassPath;
			exportSignatureCode(accessorWriter, className);
			exportIncludeGuardBegin(accessorWriter, namespaceValue, className);
			exportIncludePath(accessorWriter, parentClassPath);
			exportNameSpaceBegin(accessorWriter, namespaceValue);
			exportAccessor(accessorWriter, className, masterData, loadBinaryDirectory);
			exportNameSpaceEnd(accessorWriter, namespaceValue);
			exportIncludeGuardEnd(accessorWriter, namespaceValue, className);
		}
	}
}