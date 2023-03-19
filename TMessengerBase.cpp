#include "Stdafx.h"
#include "TMessengerBase.h"
#include "TSoulmateFrame.h"
#include "TMsgGroupList.h"
#include "TMsgChatMemberList.h"
#include "TClientWnd.h"
#include "TClientGame.h"
#include "TMessengerChat.h"
#include "Resource.h"

// ======================================================================
CTMessengerBase::CTMessengerBase(TComponent* pParent, LP_FRAMEDESC pDesc)
:	ITInnerFrame(pParent,pDesc,TMESSENGER_FRAME_MESSENGER), 
	m_pGroupList(NULL)
{
	//m_pAddMemberBtn = FindKid(ID_CTRLINST_BTN_ADD);
	//m_pBlockListBtn = FindKid(ID_CTRLINST_BTN_BLOCK);

	m_menu[TNM_DBLCLICK] = GM_NEW_MESSENGER_CHAT;
	//m_pBlockListBtn->m_menu[TNM_LCLICK] = GM_TOGGLE_BLOCKLIST;
}
// ----------------------------------------------------------------------
CTMessengerBase::~CTMessengerBase()
{
}
// ======================================================================
void CTMessengerBase::SetMsgGroupList(CTMsgGroupList* pList)
{
	ASSERT(!m_pGroupList && "�� �Լ��� �̹� �ѹ� ȣ��ƽ��ϴ�.");

	TComponent* pComp = FindKid(ID_CTRLINST_GROUPLIST);
	ASSERT(pComp && "�ʿ��� �ڽ� ��Ʈ���� �������� �ʽ��ϴ�.");

	CPoint pt;
	pComp->GetComponentPos(&pt);
	pList->MoveComponent(pt);

	RemoveKid(pComp);
	AddKid(pList);

    m_pGroupList = pList;
	delete pComp;
}
// ----------------------------------------------------------------------
/*void CTMessengerBase::SetMsgChatMemberList(CTMsgChatMemberList* pList)
{
	ASSERT(!m_pChatList && "�� �Լ��� �̹� �ѹ� ȣ��ƽ��ϴ�.");

	TComponent* pComp = FindKid(ID_CTRLINST_COMMLIST);
	ASSERT(pComp && "�ʿ��� �ڽ� ��Ʈ���� �������� �ʽ��ϴ�.");

	CPoint pt;
	pComp->GetComponentPos(&pt);
	pList->MoveComponent(pt);

	RemoveKid(pComp);
	AddKid(pList);

	m_pChatList = pList;
	delete pComp;
}*/
// ======================================================================

// ======================================================================
void CTMessengerBase::OnLButtonDown(UINT nFlags, CPoint pt)
{
	ITInnerFrame::OnLButtonDown(nFlags,pt);
}
// ----------------------------------------------------------------------
void CTMessengerBase::OnRButtonDown(UINT nFlags, CPoint pt)
{
	ITInnerFrame::OnRButtonDown(nFlags,pt);
}
// ----------------------------------------------------------------------
void CTMessengerBase::OnLButtonDblClk(UINT nFlags, CPoint pt)
{
	CTMsgGroupList::CItem* pItem = m_pGroupList->GetHitItem(pt);
	if( pItem && pItem->GetType() == CTMsgGroupList::ITYPE_MEMBER )
		SAFE_NOTIFY(m_id, TNM_DBLCLICK, 0);
}