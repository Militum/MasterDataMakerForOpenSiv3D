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

#ifndef MILITUM_BINARY_EXPORT_HPP_
#define MILITUM_BINARY_EXPORT_HPP_

#include <Siv3D.hpp>
#include "MasterData.hpp"

namespace Militum
{
	namespace Binary
	{
		extern void execute(Serializer<BinaryWriter>& writer, const MasterData& data);
	}
}

#endif // MILITUM_BINARY_EXPORT_HPP_