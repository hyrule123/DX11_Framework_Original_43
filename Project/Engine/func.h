#pragma once


template<typename T, UINT Size>
void Safe_Del_Array(T* (&arr)[Size])
{
	for (UINT i = 0; i < Size; ++i)
	{
		if (nullptr != arr[i])
			delete arr[i];
	}	
}

