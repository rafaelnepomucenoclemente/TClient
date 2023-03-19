#pragma once

class CTItemUpCashDlg;
class CTItemUpCashSlot;
class CTClientItem;

class CTItemUpCashSlot : public CTCtrlListSlot
{
	
public:
	TImageList*		m_pIcon;
	TComponent*		m_pName;
	TComponent*		m_pExplanation;

public:
	virtual void ShowComponent(BOOL bShow);
	virtual void Select(BOOL bSel);

public:
	CTItemUpCashSlot()
		: m_pIcon(NULL), m_pName(NULL)
	{}
		virtual ~CTItemUpCashSlot() {}
};


class CTItemUpCashDlg :	public CTClientUIBase
{
public:
	

	enum	{	MAX_ITEM_SLOT = 3	};	
	enum
	{
		MODE_ITEMUP = 0,
		MODE_REFINE,
		MODE_TOTAL
	};
	enum 
	{
		MAINTAIN_POTIONOFFORTUNE = 905,				// ����� ����100%
		MAINTAIN_POTIONOFFORTUNE150 = 921,				// ����� ����150%
		MAINTAIN_POTIONOFFORTUNE200 = 922,				// ����� ����200%
		MAINTAIN_PROTECTIONOFUPGRADING = 919,		// ��ȭ ��ȣ��
		MAINTAIN_LEGENDENCHARTBOOK = 911,			// ������ ���� ������
		MAINTAIN_LEGENDREFINEBOOK = 912,			// ������ ���� ������
		MAINTAIN_MAGICTRANSFERSPELL = 913,			// �����Ӽ� ���� �ֹ���
	};

	enum
	{
		CASHITEM_POTIONOFFORTUNE = 7609,			// ����� ����
		CASHITEM_PROTECTIONOFUPGRADING = 7654,		// ��ȭ ��ȣ��
		CASHITEM_LEGENDENCHARTBOOK = 7611,			// ������ ���� ������
		CASHITEM_LEGENDREFINEBOOK = 7612,			// ������ ���� ������
		CASHITEM_MAGICTRANSFERSPELL = 7613,			// �����Ӽ� ���� �ֹ���
	};

	TComponent*		m_pTopMessage;		// ��� �޽���
	TComponent*		m_pBottonMessage;	// �ϴ� �޽���
	TComponent*		m_pBottonMessage2;	// �ϴ� �޽���

	TEdit*			m_pItemMessage;		// ������ ���� ���

	INT				m_nSlotNum;
	INT				m_nMode;
	CTCtrlList*		m_pList;


	std::vector<CTClientItem*>	m_vItems;
	std::vector<CString>		m_vExplanation;
	
	

public:

	void	AddItem( LPTITEM pItem, CString strString );
	
	void	SetMode( INT nMode );
	INT		GetMode();

	void	Clear();



public:
	CTItemUpCashDlg(TComponent* pParent, LP_FRAMEDESC pDesc);
	virtual ~CTItemUpCashDlg(void);

	void OnLButtonDown(UINT nFlags, CPoint pt);
	virtual ITDetailInfoPtr GetTInfoKey( const CPoint& point );
	virtual void ShowComponent( BOOL bVisible = TRUE);

};
