#pragma once
#ifndef _UTILITY_H
#define _UTILITY_H

template<typename T>
inline static bool IsValid(T* Object)
{
	return Object != nullptr;
}

inline static void PrintToConsole(const char* Message)
{
	std::cout << Message << std::endl;
}

#endif


