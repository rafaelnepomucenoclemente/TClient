#pragma once


class CTClientQuest
{
public:
	static LPTTERM FindTTerm(
		LPTQUEST pTQUEST,
		DWORD dwTermID,
		BYTE bTermType);

public:
	LPTQUEST m_pTQUEST;
	VTTERM m_vTTERM;

	DWORD m_dwTick;
	BYTE m_bTimmer;

	BOOL m_bCheckShowRight; // ȭ�� ������ ���̴� ����ǥ�ÿ���

public:
	CTClientTerm *FindTTerm( LPTTERM pTTERM);
	CTClientTerm *FindTTerm(
		DWORD dwTermID,
		BYTE bTermType);

	BYTE GetResult();

public:
	CTClientQuest();
	virtual ~CTClientQuest();
};
