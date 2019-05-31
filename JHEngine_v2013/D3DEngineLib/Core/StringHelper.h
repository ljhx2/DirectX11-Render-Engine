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
	//wchar_t ���� char ���� ����ȯ �Լ� (�̸� �޸� ���� Ȯ���� �ؾ���)
	static void ConvertWCtoC(IN wchar_t* str, OUT char* dst)
	{
		//�Է¹��� wchar_t ������ ���̸� ����
		int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		//�� ��ȯ 
		WideCharToMultiByte(CP_ACP, 0, str, -1, dst, strSize, 0, 0);
	}
	//char ���� wchar_t ���� ����ȯ �Լ� (�̸� �޸� ���� Ȯ���� �ؾ���)
	static void ConverCtoWC(IN char* str, OUT wchar_t* dst)
	{
		//��Ƽ ����Ʈ ũ�� ��� ���� ��ȯ
		int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
		//�� ��ȯ
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


	//wstring ���� string ������ ����ȯ �Լ�
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
	//string ���� wstring ������ ����ȯ �Լ�
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

	//Ǯ��ο��� �����̸� ����
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
	//Ȯ���� ����
	static std::wstring PickNameFromFileName(std::wstring filename)
	{
		int find = filename.find(L'.');
		std::wstring name(filename.begin(), filename.begin() + find);

		return name;
	}
	//Ȯ���� ����
	static std::wstring PickFormatFromFileName(std::wstring filename)
	{
		int find = filename.find(L'.');
		std::wstring format(filename.begin() + find + 1, filename.end());

		return format;
	}
	//Ǯ��ο��� ���ϰ�� ����(���ϸ� ������ ������)
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
