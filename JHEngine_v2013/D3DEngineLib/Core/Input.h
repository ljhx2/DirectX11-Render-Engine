#pragma once

#ifndef _INPUT_H_
#define _INPUT_H_

#include <Windows.h>

const int MAX_KEY_COUNT = 256;

class Input
{
public:
	static bool GetKeyDown(int vKey)
	{
		if (!GetFocus()
			|| vKey < 0 || vKey >(MAX_KEY_COUNT - 1))
		{
			return false;
		}

		if ((GetAsyncKeyState(vKey) & 0x8000) && !kDown[vKey])
		{
			kDown[vKey] = true;
			return true;
		}
		else if (!GetAsyncKeyState(vKey) && kDown[vKey])
		{
			kDown[vKey] = false;
			return false;
		}

		return false;
	}

	static bool GetKeyUp(int vKey)
	{
		if (!GetFocus()
			|| vKey < 0 || vKey >(MAX_KEY_COUNT - 1))
		{
			return false;
		}

		if ((GetAsyncKeyState(vKey) & 0x8000) && !kUp[vKey])
		{
			kUp[vKey] = true;
			return false;
		}
		else if (!GetAsyncKeyState(vKey) && kUp[vKey])
		{
			kUp[vKey] = false;
			return true;
		}

		return false;
	}

	static bool GetKey(int vKey)
	{
		if (!GetFocus())
		{
			return false;
		}

		if (GetAsyncKeyState(vKey) & 0x8000)
		{
			return true;
		}

		return false;
	}

private:
	Input();
	~Input();

private:
	static bool kDown[MAX_KEY_COUNT];
	static bool kUp[MAX_KEY_COUNT];
};

#endif	// _INPUT_H_