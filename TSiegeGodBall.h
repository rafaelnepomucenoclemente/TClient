#pragma once


//! GodBall Class.
/*!
*	@brief	������Ż�������� ������ ���� Ŭ����.
*			( ���ٵ�� �پ Ÿ���� Mount ���Ѿ���.. )
*
*	@date	2009/08/21
*	@author	�� ����
*
*/
class CTGodBall : public CTClientObjBase
{
public :	// DEFINITION.
	
	typedef map< DWORD, LPOBJECT > MAP_RESOURCE_BALL;
	typedef MAP_RESOURCE_BALL::iterator MAP_BALL_ITOR;

private :	// MEMBER DATA.

	WORD						m_wBallID;			//!< ����ID..
	BOOL						m_bInGround;		//!< �ʿ� �������� true..
	BYTE						m_bCamp;			//!< ������ or ������ ����..
	BOOL						m_bValid;			//!< ��ȿ���� ���� ������ TRUE..

	/*! @note	��Ʈ������ : m_dwID, m_strName, m_fRot, m_dwOBJID, m_dwIconID, m_dwSfxID.. */
	LPTGODBALL					m_pBallInfo;

	static MAP_RESOURCE_BALL	m_mapResBall;		//!< ����������Ʈ ���ҽ�����..

private :	// PRIVATE FUNCTION.

	/*!  */
	LPOBJECT					FindObject( DWORD dwObjID, CTachyonRes* pResource );

public :

								CTGodBall();
	virtual						~CTGodBall();

public :	// MEMBER FUNCTION.

	/*!  */
	BOOL						InitGodBall( WORD wID, CD3DDevice* pDevice, CTachyonRes* pResource );
	/*!  */
	void						AddGodBall( BYTE bCamp, D3DXVECTOR3& vPosition, BOOL bInGround );
	/*!  */
	void						TakeGodBall();
	/*!  */
	void						DelGodBall();
	/*!  */
	void						StartBallAction();
	/*!  */
	void						Release();

public :	// VIRTUAL FUNCTION.

	virtual CString				GetName();

public :	// INLINE FUNCTION.

	WORD						GetBallID() const;
	BOOL						InGround() const;
	BYTE						GetCamp() const;
	LPTGODBALL					GetBallInfo() const;
	BOOL						IsValid() const;
	BOOL						IsVisible() const;

	void						SetBallID( WORD wBallID );
	void						SetCamp( BYTE bCamp );
	void						SetGroundPosition( D3DXVECTOR3& vPosition );
	void						SetValid( BOOL bValid );
};
