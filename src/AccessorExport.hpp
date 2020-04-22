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

#ifndef MILITUM_ACCESSOR_EXPORT_HPP_
#define MILITUM_ACCESSOR_EXPORT_HPP_

#include <Siv3D.hpp>
#include "MasterData.hpp"
#include "ConfigData.hpp"

namespace Militum
{
	namespace Accessor
	{
		extern void execute(
			TextWriter& path,
			const MasterData& data,
			const ConfigFile<ConfigData>& config
			);
	}
}

#endif // MILITUM_ACCESSOR_EXPORT_HPP_