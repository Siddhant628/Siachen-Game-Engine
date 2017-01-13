#pragma once

namespace SiachenGameEngine
{
	class SList
	{
	public:
		SList(int data);

		int GetData();
	private:
		int m_iData;
	};
}