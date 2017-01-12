#include "pch.h"
#include "SList.h"

SList::SList(int data):
	m_iData(data)
{

}

int SList::GetData()
{
	return m_iData;
}
