#include "stdafx.h"
#include "resource.h"
#include "TNationOption.h"

BOOL CTNationOption::GERMANY = FALSE;
BOOL CTNationOption::FRANCE = FALSE;
BOOL CTNationOption::ENGLISH = FALSE;
BOOL CTNationOption::JAPAN = FALSE;
BOOL CTNationOption::POLAND = FALSE;
BOOL CTNationOption::TAIWAN = FALSE;
BOOL CTNationOption::CZECH = FALSE;
BOOL CTNationOption::ITALY = FALSE;
BOOL CTNationOption::SPAIN = FALSE;
BOOL CTNationOption::UNITEDKINGDOM = FALSE;
BOOL CTNationOption::GREECE = FALSE;
BOOL CTNationOption::RUSSIA = FALSE;
BOOL CTNationOption::ROMANIA = FALSE;
BOOL CTNationOption::UNITEDSTATE = FALSE;
BOOL CTNationOption::HUNGARY = FALSE;
BOOL CTNationOption::TURKEY = FALSE;
BOOL CTNationOption::PORTUGAL = FALSE;
BOOL CTNationOption::KOR = FALSE;

BOOL CTNationOption::MODIFY_WORD_BREAK = FALSE;
BOOL CTNationOption::CAMERA_QUAKE = FALSE;
BOOL CTNationOption::ADD_SLIDE = FALSE;
BOOL CTNationOption::USE_STATE_FRAME_WIDE = FALSE;
BOOL CTNationOption::JAPAN_IME = FALSE;
BOOL CTNationOption::TAIWAN_IME = FALSE;
BOOL CTNationOption::MODIFY_DIRECTLOGIN = FALSE;
BOOL CTNationOption::PASSWORD_MD5 = FALSE;
BOOL CTNationOption::INSTALL_XTRAP = FALSE;
BOOL CTNationOption::INSTALL_APEX = FALSE;
BOOL CTNationOption::INSTALL_HACKSHIELD = FALSE;
BOOL CTNationOption::USE_WEB_CASHSHOP = FALSE;
BOOL CTNationOption::INSTALL_GAMEGUARD = FALSE;
BOOL CTNationOption::WAITING_REVIVAL_ITEM = TRUE;

CString CTNationOption::m_strAppTitle;

void CTNationOption::Clear()
{
	CTNationOption::GERMANY = FALSE;
	CTNationOption::ENGLISH = FALSE;
	CTNationOption::JAPAN = FALSE;
	CTNationOption::POLAND = FALSE;
	CTNationOption::FRANCE = FALSE;
	CTNationOption::TAIWAN = FALSE;
	CTNationOption::CZECH = FALSE;
	CTNationOption::ITALY = FALSE;
	CTNationOption::SPAIN = FALSE;
	CTNationOption::UNITEDKINGDOM = FALSE;
	CTNationOption::GREECE = FALSE;
	CTNationOption::RUSSIA = FALSE;
	CTNationOption::ROMANIA = FALSE;
	CTNationOption::UNITEDSTATE = FALSE;
	CTNationOption::HUNGARY = FALSE;
	CTNationOption::TURKEY = FALSE;
	CTNationOption::PORTUGAL = FALSE;
	CTNationOption::KOR = FALSE;

	CTNationOption::MODIFY_WORD_BREAK = FALSE;
	CTNationOption::CAMERA_QUAKE = FALSE;
	CTNationOption::ADD_SLIDE = FALSE;
	CTNationOption::USE_STATE_FRAME_WIDE = FALSE;
	CTNationOption::JAPAN_IME = FALSE;
	CTNationOption::MODIFY_DIRECTLOGIN = FALSE;
	CTNationOption::PASSWORD_MD5 = FALSE;
	CTNationOption::INSTALL_XTRAP = FALSE;
	CTNationOption::INSTALL_APEX = FALSE;
	CTNationOption::INSTALL_HACKSHIELD = FALSE;
	CTNationOption::USE_WEB_CASHSHOP = FALSE;
	CTNationOption::WAITING_REVIVAL_ITEM = TRUE;

	m_strAppTitle.Empty();
}

void CTNationOption::SetNation( INT nNation )
{
	Clear();

	// Default "4Story"
	m_strAppTitle.LoadString( AFX_IDS_APP_TITLE );

	switch( nNation )
	{
	case TNATION_JAPAN:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::JAPAN = TRUE;
		CTNationOption::JAPAN_IME = TRUE;
	
		CTNationOption::MODIFY_DIRECTLOGIN = TRUE;
		break;

	case TNATION_GERMANY:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::GERMANY = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;
		CTNationOption::CAMERA_QUAKE = TRUE;
		CTNationOption::INSTALL_HACKSHIELD = TRUE;
		CTNationOption::USE_WEB_CASHSHOP = TRUE;

		break;

	case TNATION_POLAND:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::POLAND = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;
		CTNationOption::CAMERA_QUAKE = TRUE;
		TEdit::m_nCountryFlag = TEdit::COUNTRY_FLAG_POLAND;
			CTNationOption::INSTALL_HACKSHIELD = TRUE;
	
		CTNationOption::USE_WEB_CASHSHOP = TRUE;
		break;

	case TNATION_GREECE:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::GREECE = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;
		CTNationOption::CAMERA_QUAKE = TRUE;
		TEdit::m_nCountryFlag = TEdit::COUNTRY_FLAG_GREECE;
	CTNationOption::INSTALL_HACKSHIELD = TRUE;

		CTNationOption::USE_WEB_CASHSHOP = TRUE;
		break;

	case TNATION_ENGLISH:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::ENGLISH = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;

			CTNationOption::INSTALL_HACKSHIELD = TRUE;
		CTNationOption::CAMERA_QUAKE = TRUE;
		CTNationOption::PASSWORD_MD5 = TRUE;
		CTNationOption::USE_WEB_CASHSHOP = TRUE;

		m_strAppTitle.LoadString( AFX_IDS_APP_TITLE_GLOBAL );

		break;

	case TNATION_FRANCE:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::FRANCE = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;
		CTNationOption::CAMERA_QUAKE = TRUE;
		TEdit::m_nCountryFlag = TEdit::COUNTRY_FLAG_FRANCE;

		CTNationOption::INSTALL_HACKSHIELD = TRUE;
		CTNationOption::USE_WEB_CASHSHOP = TRUE;
		break;

	case TNATION_CZECH:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::CZECH = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;
		CTNationOption::CAMERA_QUAKE = TRUE;
		TEdit::m_nCountryFlag = TEdit::COUNTRY_FLAG_CZECH;
//	CTNationOption::INSTALL_HACKSHIELD = TRUE;
		CTNationOption::INSTALL_GAMEGUARD = TRUE;
		CTNationOption::USE_WEB_CASHSHOP = TRUE;

		break;

	case TNATION_ITALY:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::ITALY = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;
		CTNationOption::CAMERA_QUAKE = TRUE;

		TEdit::m_nCountryFlag = TEdit::COUNTRY_FLAG_ITALY;
			CTNationOption::INSTALL_HACKSHIELD = TRUE;
		CTNationOption::USE_WEB_CASHSHOP = TRUE;
		break;

	case TNATION_SPAIN:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::SPAIN = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;
		CTNationOption::CAMERA_QUAKE = TRUE;
		TEdit::m_nCountryFlag = TEdit::COUNTRY_FLAG_SPAIN;
		CTNationOption::INSTALL_HACKSHIELD = TRUE;
		
		CTNationOption::USE_WEB_CASHSHOP = TRUE;
		break;

	case TNATION_UNITEDKINGDOM:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::UNITEDKINGDOM = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;
		CTNationOption::CAMERA_QUAKE = TRUE;
		
		CTNationOption::INSTALL_HACKSHIELD = TRUE;
		CTNationOption::USE_WEB_CASHSHOP = TRUE;
		break;

	case TNATION_TAIWAN:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::TAIWAN = TRUE;
		CTNationOption::TAIWAN_IME = TRUE;
		CTNationOption::MODIFY_DIRECTLOGIN = TRUE;
	
			CTNationOption::INSTALL_HACKSHIELD = TRUE;
		CTNationOption::INSTALL_APEX = TRUE;
		break;

	case TNATION_RUSSIA:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::RUSSIA = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;
		CTNationOption::CAMERA_QUAKE = TRUE;
		CTNationOption::USE_WEB_CASHSHOP = TRUE;
	// ���Ӱ��� ��ġ.
		TEdit::m_nCountryFlag = TEdit::COUNTRY_FLAG_RUSSIA;
		CTNationOption::WAITING_REVIVAL_ITEM = TRUE;
			CTNationOption::INSTALL_HACKSHIELD = TRUE;

		m_strAppTitle.LoadString( AFX_IDS_APP_TITLE_RUSSIA );

		break;

	case TNATION_ROMANIA:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::ROMANIA = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;
		CTNationOption::CAMERA_QUAKE = TRUE;

		TEdit::m_nCountryFlag = TEdit::COUNTRY_FLAG_ROMANIA;
			CTNationOption::INSTALL_HACKSHIELD = TRUE;
		CTNationOption::USE_WEB_CASHSHOP = TRUE;
		break;

	case TNATION_UNITEDSTATE:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::UNITEDSTATE = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;

		CTNationOption::CAMERA_QUAKE = TRUE;
		CTNationOption::INSTALL_HACKSHIELD = TRUE;
		CTNationOption::USE_WEB_CASHSHOP = TRUE;

		m_strAppTitle.LoadString( AFX_IDS_APP_TITLE_GOA );

		break;

	case TNATION_HUNGARY:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::HUNGARY = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;

		CTNationOption::CAMERA_QUAKE = TRUE;
		TEdit::m_nCountryFlag = TEdit::COUNTRY_FLAG_HUNGARY;
		CTNationOption::INSTALL_HACKSHIELD = TRUE;
		CTNationOption::USE_WEB_CASHSHOP = TRUE;

		m_strAppTitle.LoadString( AFX_IDS_APP_TITLE_GOA );

		break;

	case TNATION_TURKEY:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::TURKEY = TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;
		CTNationOption::CAMERA_QUAKE = TRUE;
	
		TEdit::m_nCountryFlag = TEdit::COUNTRY_FLAG_TURKEY;
		CTNationOption::INSTALL_HACKSHIELD = TRUE;
		CTNationOption::USE_WEB_CASHSHOP = TRUE;
		break;

	case TNATION_PORTUGAL:
		CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::PORTUGAL= TRUE;
		CTNationOption::MODIFY_WORD_BREAK = TRUE;
		CTNationOption::CAMERA_QUAKE = TRUE;
	
		TEdit::m_nCountryFlag = TEdit::COUNTRY_FLAG_PORTUGAL;
		CTNationOption::INSTALL_HACKSHIELD = TRUE;
		CTNationOption::USE_WEB_CASHSHOP = TRUE;
		break;

	default:
	case TNATION_KOREA:

        CTNationOption::INSTALL_XTRAP = FALSE;
		CTNationOption::KOR = TRUE;
		CTNationOption::USE_WEB_CASHSHOP = FALSE;
			CTNationOption::INSTALL_HACKSHIELD = TRUE;
		
		break;
	}
}

BOOL CTNationOption::SetNation( CString strNation )
{
	if( strNation == _T("GERMANY") )
	{
		SetNation( TNATION_GERMANY );
		return TRUE;
	}
	else if( strNation == _T("ENGLISH") )
	{
		SetNation( TNATION_ENGLISH );
		return TRUE;
	}
	else if( strNation == _T("JAPAN") )
	{
		SetNation( TNATION_JAPAN );
		return TRUE;
	}
	else if( strNation == _T("POLAND") )
	{
		SetNation( TNATION_POLAND );
		return TRUE;
	}
	else if( strNation == _T("FRANCE") )
	{
		SetNation( TNATION_FRANCE );
		return TRUE;
	}
	else if ( strNation == _T("TAIWAN") )
	{
		SetNation( TNATION_TAIWAN );
		return TRUE;
	}
	else if ( strNation == _T("CZECH") )
	{
		SetNation( TNATION_CZECH );
		return TRUE;
	}
	else if ( strNation == _T("ITALY") )
	{
		SetNation( TNATION_ITALY );
		return TRUE;
	}
	else if ( strNation == _T("SPAIN") )
	{
		SetNation( TNATION_SPAIN );
		return TRUE;
	}
	else if ( strNation == _T("UNITEDKINGDOM") )
	{
		SetNation( TNATION_UNITEDKINGDOM );
		return TRUE;
	}
	else if ( strNation == _T("GREECE") )
	{
		SetNation( TNATION_GREECE );
		return TRUE;
	}
	else if ( strNation == _T("RUSSIA") )
	{
		SetNation( TNATION_RUSSIA );
		return TRUE;
	}
	else if ( strNation == _T("ROMANIA") )
	{
		SetNation( TNATION_ROMANIA );
		return TRUE;
	}
	else if ( strNation == _T("UNITEDSTATE") )
	{
		SetNation( TNATION_UNITEDSTATE );
		return TRUE;
	}
	else if ( strNation == _T("HUNGARY") )
	{
		SetNation( TNATION_HUNGARY );
		return TRUE;
	}
	else if ( strNation == _T("TURKEY") )
	{
		SetNation( TNATION_TURKEY );
		return TRUE;
	}
	else if ( strNation == _T("PORTUGAL") )
	{
		SetNation( TNATION_PORTUGAL );
		return TRUE;
	}
	else if( strNation == _T("KOREA") ||
		strNation.IsEmpty() )
	{
		SetNation( TNATION_KOREA );
		return TRUE;
	}

	return FALSE;
}
