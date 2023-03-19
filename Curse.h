#pragma once

/**
	���忡�� ��Ӿ ã�� ���� Ŭ�����̴�.
	
	1. �˻��� binary search �� �����.
	2. ��Ӿ� ����Ʈ�� �ܾ��� ���� �� �ܾ��� ���ڱ��̰� ����� ���� �˻��ð��� ������.
	3. CONVERT_STRING �� ��Ӿ� �˻��� ��ü�ϰ��� �ϴ� ���ڸ� ���� �� �� ����.
*/
class CCurse
{
public:
	static CString CONVERT_STRING;
	static CHAR CONVERT_CHAR;

private:
	static int				m_nMaxLen;
	static vector<CString>	m_vStrCurse;	

private:
	static DWORD ReadString(CHAR* pDATA, CString& outSTR);

public:
	/**
		�ؽ�Ʈ ������ ���ҽ��� ���� ��Ӿ� ����Ÿ�� �ε��ؿ´�.
		��Ӿ� �˻��� �ݵ�� ȣ���� �־�� �Ѵ�.
	*/
	static void Load(HINSTANCE hInstance, DWORD dwResID, CString strResGrp);	

	/**
		�־��� ���忡 ��Ӿ �ִ��� �˻��Ѵ�.
	*/
	static bool IsCurse(const CString& str);					

	/**
		�־��� ���忡�� ��Ӿ ã�� ������ ���ڿ��� ġȯ�Ѵ�.
	*/
	static const CString& ConvertString( const CString& str, BYTE bCheckHeader);

	/**
		�ε�� ��� �����͸� �޸𸮿��� �����Ѵ�.
	*/
	static void Release() { m_vStrCurse.clear(); m_nMaxLen = 0; }
};
