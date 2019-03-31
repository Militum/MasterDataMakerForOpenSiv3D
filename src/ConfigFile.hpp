//-----------------------------------------------
//
//	Copyright (c) 2018 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.3.1

namespace s3d
{
	class ConfigError
	{
	private:

		String m_what;

	public:

		ConfigError() = default;

		ConfigError(const String& what)
			: m_what(what) {}

		const String& what() const
		{
			return m_what;
		}

		void show() const
		{
			System::ShowMessageBox(U"ConfigError", what(), MessageBoxStyle::Error);
		}

		void print() const
		{
			Print << U"ConfigError: " << what();
		}
	};

	template <class ConfigData>
	class ConfigFile : public ConfigData
	{
	private:

		FilePath m_fullPath;

		DirectoryWatcher m_watcher;

	public:

		bool hasChanged() const
		{
			for (const auto& change : m_watcher.retrieveChanges())
			{
				if (change.first == m_fullPath
					&& change.second == FileAction::Modified)
				{
					return true;
				}
			}

			return false;
		}

		void reload(const FilePath& path)
		{
			m_fullPath = FileSystem::FullPath(path);

			m_watcher = DirectoryWatcher(FileSystem::ParentPath(m_fullPath));

			if (!FileSystem::Exists(path))
			{
				throw ConfigError(U"Runtime Error: Config file `{} does not exist`"_fmt(path));
			}

			const TOMLReader toml(path);

			ConfigData::reload(toml);
		}
	};

	template <class Type>
	inline void LoadValueFromConfig(const TOMLReader& toml, const String& name, Type& value)
	{
		if (const auto opt = toml[name].getOpt<Type>())
		{
			value = opt.value();
		}
		else
		{
			throw ConfigError(U"Runtime Error: Config item `{}` is invalid"_fmt(name));
		}
	}

	template <class Type>
	inline void LoadArrayFromConfig(const TOMLReader& toml, const String& name, Array<Type>& values)
	{
		const auto tomlValue = toml[name];

		tomlValue.getType();

		if (!tomlValue.isArray())
		{
			throw ConfigError(U"Runtime Error: Config item `{}` is not an array"_fmt(name));
		}

		Array<Type> results;

		for (const auto& value : tomlValue.arrayView())
		{
			if (const auto opt = value.getOpt<Type>())
			{
				results << opt.value();
			}
			else
			{
				throw ConfigError(U"Runtime Error: Config item `{}` is invalid"_fmt(name));
			}
		}

		values.swap(results);
	}

# define S3DCFG_CONCAT2(X, Y) X##Y
# define S3DCFG_CONCAT(X, Y) S3DCFG_CONCAT2(X, Y)
# define S3DCFG_STRINGIFY2(X) #X
# define S3DCFG_STRINGIFY(X) S3DCFG_STRINGIFY2(X)
# define S3DCFG_WIDEN(X) S3DCFG_CONCAT(U, S3DCFG_STRINGIFY(X))
# define S3DCFG_RELOAD_SECTION(x) x##.reload(toml)
# define S3DCFG_LOAD_SECTION(sectionName) const s3d::String sectionPrefix = sectionName + s3d::String(U".")
# define S3DCFG_LOAD_VALUE(valueName) s3d::LoadValueFromConfig(toml, sectionPrefix + S3DCFG_WIDEN(valueName), valueName)
# define S3DCFG_LOAD_ARRAY(valueName) s3d::LoadArrayFromConfig(toml, sectionPrefix + S3DCFG_WIDEN(valueName), valueName)
}
