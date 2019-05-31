#pragma once

#ifndef _STRING_HELPER_H_
#define _STRING_HELPER_H_

#include <Windows.h>
#include <string>
#include <algorithm>

#include <atlconv.h>
#pragma comment (lib, "atls.lib")

class CStringHelper
{
public:
	CStringHelper();
	~CStringHelper();

public:
	//wchar_t 에서 char 로의 형변환 함수 (미리 메모리 공간 확보를 해야함)
	static void ConvertWCtoC(IN wchar_t* str, OUT char* dst)
	{
		//입력받은 wchar_t 변수의 길이를 구함
		int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		//형 변환 
		WideCharToMultiByte(CP_ACP, 0, str, -1, dst, strSize, 0, 0);
	}
	//char 에서 wchar_t 로의 형변환 함수 (미리 메모리 공간 확보를 해야함)
	static void ConverCtoWC(IN char* str, OUT wchar_t* dst)
	{
		//멀티 바이트 크기 계산 길이 반환
		int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
		//형 변환
		MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, dst, strSize);
	}

	std::wstring strconv(const std::string& _src)
	{
		USES_CONVERSION;
		return std::wstring(A2W(_src.c_str()));
	};

	std::string strconv(const std::wstring& _src)
	{
		USES_CONVERSION;
		return std::string(W2A(_src.c_str()));
	};


	//wstring 에서 string 으로의 형변환 함수
	static void WStringToString(IN const std::wstring& in, OUT std::string& out)
	{
		//out.clear();
		//
		//size_t inSize = in.size();
		//for (size_t i = 0; i < inSize; i++)
		//{
		//	out.insert(out.end(), 1, static_cast<const char>(in.at(i) & 0xFF));
		//}

		USES_CONVERSION;
		out.assign(W2A(in.c_str()));
	}
	//string 에서 wstring 으로의 형변환 함수
	static void StringToWString(IN const std::string& in, OUT std::wstring& out)
	{
		//out.clear();
		//
		//size_t inSize = in.size();
		//for (size_t i = 0; i < inSize; i++)
		//{
		//	out.insert(out.end(), 1, static_cast<const wchar_t>(in.at(i)));
		//}

		USES_CONVERSION;
		out.assign(A2W(in.c_str()));
	}

	//풀경로에서 파일이름 추출
	static std::wstring PickFileNameFromFullPath(std::wstring fullpath)
	{
		std::wstring separate = L"/";

		std::wstring::iterator iter;
		iter = std::find_end(fullpath.begin(), fullpath.end(), separate.begin(), separate.end());

		if (iter == fullpath.end())
		{
			separate = L"\\";
			iter = std::find_end(fullpath.begin(), fullpath.end(), separate.begin(), separate.end());

			if (iter == fullpath.end())
			{
				return fullpath;
			}
			
			std::wstring fileName(iter + 1, fullpath.end());
			return fileName;
		}

		std::wstring fileName(iter + 1, fullpath.end());

		return fileName;
	}
	//확장자 제거
	static std::wstring PickNameFromFileName(std::wstring filename)
	{
		int find = filename.find(L'.');
		std::wstring name(filename.begin(), filename.begin() + find);

		return name;
	}
	//확장자 추출
	static std::wstring PickFormatFromFileName(std::wstring filename)
	{
		int find = filename.find(L'.');
		std::wstring format(filename.begin() + find + 1, filename.end());

		return format;
	}
	//풀경로에서 파일경로 추출(파일명 제외한 나머지)
	static std::wstring PickPathFromFullPath(std::wstring fullpath)
	{
		std::wstring separate = L"/";
		std::wstring::iterator iter;
		iter = std::find_end(fullpath.begin(), fullpath.end(), separate.begin(), separate.end());

		if (iter == fullpath.end())
		{
			separate = L"\\";
			iter = std::find_end(fullpath.begin(), fullpath.end(), separate.begin(), separate.end());

			if (iter == fullpath.end())
			{
				return fullpath;
			}

			std::wstring pathName(fullpath.begin(), iter);
			pathName += L"\\";
			return pathName;

		}

		std::wstring pathName(fullpath.begin(), iter);

		pathName += L"\\";

		return pathName;
	}
};

#endif // !_STRING_HELPER_H_
