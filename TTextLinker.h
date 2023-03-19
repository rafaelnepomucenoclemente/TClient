#pragma once

class CTTextLinker
{
public:
	static const CString	LINK_DEF_TOK;

	static const CHAR		LINK_STR_START;
	static const CHAR		LINK_STR_END;
	static const DWORD		LINK_DATA_POOL_SIZE;
	static const DWORD		LINK_QUEST_COLOR;

protected:
	DWORD			m_nTextLinkDataPos;
	CTTextLinkData*	m_pTextLinkDataPool;

public:
	/// ���ο� �ؽ�Ʈ ��ũ ����Ÿ �ν��Ͻ��� ��´�.
	DWORD NewTextLinkData(CTTextLinkData** pOut);
	/// �־��� ���̵��� �ؽ�Ʈ ��ũ ����Ÿ�� ��´�.
	CTTextLinkData* GetTextLinkData(DWORD nPos) const;

public:
	/// �־��� �����Ϳ� ����Ʈ������ ���� ��ũ�� �����Ѵ�.
	void InsertLinkTextToEdit(TEdit* pEdit, LPTQUEST pQuest);
	/// �־��� �����Ϳ� ������������ ���� ��ũ�� �����Ѵ�.
	void InsertLinkTextToEdit(TEdit* pEdit, LPTITEM pItem, CTClientItem* pClientItem);

	/// �־��� ������ ���ڿ� ���˿� ���߾� ��ũ �ؽ�Ʈ�� ��Ʈ��ũ ���� ������ ���·� �����.
	CString MakeItemNetText(const CString& strFormat, const VECTORDWORD& vItemID);

	/// �������� ��ũ �ؽ�Ʈ�� ��Ʈ��ũ ���� ������ ���·� �����.
	CString MakeLinkToNetText(TEdit* pEdit, BOOL bLengthSafety=FALSE, INT nMaxLength=0); 
	/// ��Ʈ��ũ ���� Ÿ�� �ؽ�Ʈ�� ��ũ Ÿ������ �����.
	CString MakeNetToSimpleLinkText(TComponent* pTxtSettingComp, const CString& strNetMsg);
	CString MakeNetToLinkText(TComponent* pTxtSettingComp, const CString& strNetMsg);

	/// �־��� ���ڿ��� ���๮�� ������ ������.
	CString SplitTextByCrLf(const CString& strMSG, const CString& strTOK, INT& nPos, BOOL bTrimCrLf=TRUE);
	/// �־��� ���ڿ��� �ش� ��Ʈ���� �ʺ� ���� ���ϵ��� �����ٷ� ������.
	CString SplitTextByComp(TComponent* pComp, LONG nSize, const CString& strMSG, TTLINKLINE_ARRAY& outLINES);

	/// �ؽ�Ʈ ������ ��´�.
	void GetTextSettings( TComponent* pTxtSettingComp, const TTLINKLINE_ARRAY& vLINES, TLLINESETTING_ARRAY2D& outSettings);

	CString BuildNetString( const CString& strHeader, const CString& strBody);
	CString AppendNetString( const CString& strMSG1, const CString& strMSG2);

protected:
	CTTextLinker();
	~CTTextLinker();

public:
	static CTTextLinker* GetInstance();
};
