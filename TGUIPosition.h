#pragma once

class CTGUIPosition
{
public:
	static CTGUIPosition	m_NetInitPos[TNETFRAME_COUNT];
	static CTGUIPosition	m_ClientInitPos[TFRAME_COUNT];

protected:
	/// ��ġ Ÿ��
	TGUI_POS_TYPE	m_eType;
	
	/// X�� ���� ��ġ
	TGUI_XBASE		m_eBaseX;
	/// Y�� ���� ��ġ
	TGUI_YBASE		m_eBaseY;

	/**
		m_eType �� ���� �ٸ� �ǹ̸� ���Ѵ�.

		TGUI_POS_ABSOLUTE		: (int)		��ǥ��
		TGUI_POS_RELATIVE		: (float)	ȭ�� ���� �� (0 ~ 1)
		TGUI_POS_EXTEND			: �������	����.
		TGUI_POS_CENTER			:
		TGUI_POS_LEFT_CENTER	:
		TGUI_POS_RIGHT_CENTER	: (float)	������ġ�� ������ ������. ������. (-1 ~ 1)
	*/
	LPVOID			m_pParamX, m_pParamY;

protected:
	void Apply_ABS(TComponent* pComp);
	void Apply_REL(TComponent* pComp);
	void Apply_EXT(TComponent* pComp);
	void Apply_CET(TComponent* pComp);
	void Apply_LCT(TComponent* pComp);
	void Apply_RCT(TComponent* pComp);

	int ToAbsLeft(TComponent* pComp, int dwPos, TGUI_XBASE eBaseX);
	int ToAbsTop(TComponent* pComp, int dwPos, TGUI_YBASE eBaseY);

	CPoint GetScreen();

public:
	void Init( TGUI_POS_TYPE type,
			   TGUI_XBASE baseX, TGUI_YBASE baseY,
			   LPVOID pParamX, LPVOID pParamY );

	void Apply(TComponent* pComp);

public:
	static void InitNetFrame();

public:
	CTGUIPosition();
	~CTGUIPosition();
};