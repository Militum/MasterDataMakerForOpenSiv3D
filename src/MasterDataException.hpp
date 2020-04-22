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

#ifndef MILITUM_MASTERDATA_EXCEPTION_HPP_
#define MILITUM_MASTERDATA_EXCEPTION_HPP_

#include <Siv3D.hpp>

namespace Militum
{

	class MasterDataException
	{
	private:

		String m_what;

	public:

		MasterDataException() = default;

		MasterDataException(const String& what)
			: m_what(what) {}

		const String& what() const
		{
			return m_what;
		}

		void show() const
		{
			System::ShowMessageBox(U"MasterDataException", what(), MessageBoxStyle::Error);
		}

		void print() const
		{
			Print << U"MasterDataException: " << what();
		}
	};

}

#endif //MILITUM_MASTERDATA_EXCEPTION_HPP_