#pragma once

class CTChatTabButton : public TButton
{
protected:
	static const DWORD FONT_COLOR_NORMAL;		///< ���� ���õ��� ������ ���� ��Ʈ ��
	static const DWORD FONT_COLOR_PUSH;			///< ���� ���É������� ��Ʈ ��
	static const DWORD FONT_COLOR_HOVER;		///< ������ Ŀ���� �ö�������� ��Ʈ ��

	CTChatFrame*	m_pHost;					///< �� ���� ���� ������
	CTChatList*		m_pList;					///< �� �ǰ� ��ũ�� ����Ʈ
	INT				m_iSlot;					///< �� ���� ���� ��ȣ ( �� ��ȣ�� ���� ���� ��ġ�� �����ȴ� )
	BOOL			m_bSelect;					///< �� ���� ���õǾ����� ����
	
	DWORD			m_dwTotalTick;				///< ��� �ð�
	BOOL			m_bHovering;				///< �� ���� Ŀ���� �ö�Դ��� ����
	BOOL			m_bNewMsg;					///< �ش� �ǰ� ����� ����Ʈ�� ���ο� �޽����� �����ߴ��� ����

public:
	/// �־��� ���Թ�ȣ�� �´� ���� ��ġ������ ��´�.
	static void SetTabSlotRect(INT iSlot, const CRect& rcTab);

public:
	/// �� �ʱ�ȭ. ������ ���ϰ� ����Ʈ�� �����Ѵ�.
	void Init(INT iSlot, CTChatList* pList);
	/// ���� ���Ž�Ų��. �������ڴ� ���� ���ź��� ���ݱ��� ����� �ð��� �ǹ��Ѵ�.
	void Update(DWORD dwTick);

	/// �־��� ����Ʈ�� ��ũ�Ѵ�.
	void LinkWithList(CTChatList* pList);
	/// ������ ���Ѵ�.
	void SetSlot(INT iSlot);
	/// �� ���� �����ϰų� �������� �Ѵ�.
	void SetSelect(BOOL bSel);
	
	/// ���ο� �޽����� ������ �ǿ� �뺸�Ѵ�.
	void NotifyNewMsg();
	
public:
	CTChatList* GetChatList() const			{ return m_pList; }
	INT GetSlot() const						{ return m_iSlot; }
	BOOL IsOuter() const					{ return m_pList->IsOuter(); }
	BOOL IsSelect() const					{ return m_bSelect; }
	INT GetChatListIndex() const			{ return m_pList->GetIndexInGroup(); }

public:
	virtual void OnMouseMove(UINT nFlags, CPoint pt);

	virtual void OnLButtonUp(UINT nFlags, CPoint pt)			{ TComponent::OnLButtonUp(nFlags,pt); }
	virtual void OnRButtonUp(UINT nFlags, CPoint pt)			{ TComponent::OnRButtonUp(nFlags,pt); }
	virtual void OnRButtonDown(UINT nFlags, CPoint pt)			{ TComponent::OnRButtonDown(nFlags,pt); }
	virtual void OnLButtonDown(UINT nFlags, CPoint pt)			{ TComponent::OnLButtonDown(nFlags,pt); }
	virtual void OnLButtonDblClk(UINT nFlags, CPoint pt)		{ TComponent::OnLButtonDblClk(nFlags,pt); }

protected:
	/// ���� ���¿� �°� ��Ʈ Į�� �缳���Ѵ�.
	void ResetFontColor();

public:
	CTChatTabButton::CTChatTabButton(CTChatFrame* pHost, LP_FRAMEDESC pDesc);
};
