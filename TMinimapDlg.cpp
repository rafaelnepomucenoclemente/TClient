#include "StdAfx.h"
#include "TClientGame.h"

LPDIRECT3DTEXTURE9 CTMinimapDlg::m_pTMINIMAP = NULL;
LPDIRECT3DTEXTURE9 CTMinimapDlg::m_pTMASK = NULL;
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
#define D3DFVF_TL (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
#define VERTEX_FVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
struct D3DTLVERTEX
{	
	float fX;	
	float fY;	
	float fZ;	
	float fRHW;	
	D3DCOLOR Color;	
	float fU;	
	float fV;
};

static const int CIRCLE_RESOLUTION = 64;
CTMinimapDlg::CTMinimapDlg( TComponent *pParent, LP_FRAMEDESC pDesc)
:CTClientUIBase( pParent, pDesc)
{
	static DWORD dwCompID[] = {
		ID_CTRLINST_MAX,
		ID_CTRLINST_WORLD,
		ID_CTRLINST_MINIMAP,
		ID_CTRLINST_ZOOM};

	


	//TFrame *pTFRAME = (TFrame *) FindKid(ID_CTRLINST_MP_MY_HP);
	



	for( BYTE i=0; i<TMINIMAPCOMP_COUNT; i++)
		m_vTCOMP[i] = FindKid(dwCompID[i]);

		
	

	//m_pTITLE = FindKid(ID_CTRLINST_MAX_TITLE);
	pHPGauge = static_cast<TGauge*>( FindKid(ID_MINIMAP_HP_GAUGE) );
	pHPGauge->SetStyle(TGS_GROW_UP);


pMPGauge = static_cast<TGauge*>( FindKid(ID_CTRLINST_WORLD) );
	pMPGauge->SetStyle(TGS_GROW_UP);


pMPTEXT = static_cast<TComponent*>( FindKid(ID_CTRLINST_MAX_TITLE) );
pMPTEXT->SetTextClr(THPTEXT_COLOR);
	pMPTEXT->ShowComponent(TRUE);


	pMPTEXT2 = static_cast<TComponent*>( FindKid(ID_CTRLINST_MAX_TITLE2) );
pMPTEXT2->SetTextClr(TMPTEXT_COLOR);
	pMPTEXT2->ShowComponent(TRUE);
	
//pHPGauge->EnableComponent(TRUE);
//pHPGauge->ShowComponent(TRUE);
	m_pTOPFRAME = FindKid(ID_CTRLINST_MIN);

	m_bMinimize = FALSE;
	m_bSND = FALSE;

	m_pDevice = NULL;
	m_pTMON = NULL;
	m_pHost = NULL;
	m_pTMAP = NULL;
	m_pCAM = NULL;

	TComponent *pTAREA = FindKid(ID_CTRLINST_AREA);
	pTAREA->GetComponentRect(&m_rcAREA);

	RemoveKid(pTAREA);
	delete pTAREA;

	m_pTZOOMSCROLL = (TScroll*) m_vTCOMP[TMINIMAPCOMP_ZOOM];
	m_pTZOOMSCROLL->SetScrollPos((INT)TMINIMAP_SCALE_COUNT, (INT)TMINIMAP_SCALE_COUNT);
}
D3DTLVERTEX CreateD3DTLVERTEX (float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
{	
	D3DTLVERTEX v;	
	v.fX = X;	
	v.fY = Y;	
	v.fZ = Z;	
	v.fRHW = RHW;	
	v.Color = color;	
	v.fU = U;	
	v.fV = V;	
	return v;
}

CTMinimapDlg::~CTMinimapDlg()
{
}

void CTMinimapDlg::ResetVisible()
{
	for( BYTE i=0; i<TMINIMAPCOMP_COUNT; i++)
	{
		m_vTCOMP[i]->EnableComponent(!m_bMinimize);
		m_vTCOMP[i]->ShowComponent(!m_bMinimize);
		pHPGauge->EnableComponent(!m_bMinimize);
	pHPGauge->ShowComponent(!m_bMinimize);
	pMPGauge->EnableComponent(!m_bMinimize);
	pMPGauge->ShowComponent(!m_bMinimize);
		pMPTEXT->ShowComponent(!m_bMinimize);
	pMPTEXT2->ShowComponent(!m_bMinimize);
	}
	
	
//		m_pGauge->EnableComponent(!m_bMinimize);
//	m_pGauge->ShowComponent(!m_bMinimize);

}

BOOL CTMinimapDlg::CanWithItemUI()
{
	return TRUE;
}

BOOL CTMinimapDlg::DoMouseWheel( UINT nFlags, short zDelta, CPoint pt)
{
	if( m_bMinimize )
		return FALSE;

	CRect rc = m_rc;
	ComponentToScreen(&rc);
	if(!rc.PtInRect(pt))
		return FALSE;

	int nRange, nPos;
	m_pTZOOMSCROLL->GetScrollPos(nRange, nPos);

	nPos += zDelta > 0 ? -1 : 1;
	nPos = min( max( nPos, 0), nRange);
	m_pTZOOMSCROLL->SetScrollPos(nRange, nPos);

	return TRUE;
}

BOOL CTMinimapDlg::HitTest( CPoint pt)
{
	CRect rect(m_rcAREA);

	rect.OffsetRect(m_rc.TopLeft());
	ComponentToScreen(&rect);

	if(rect.PtInRect(pt))
		return TRUE;

	return CTClientUIBase::HitTest(pt);
}

void CTMinimapDlg::ShowComponent( BOOL bVisible)
{
	CTClientUIBase::ShowComponent(bVisible);

	if(m_bVisible)
		ResetVisible();
}

void CTMinimapDlg::RenderTMINIMAP()
{
/*
	int nRng;
	int nPos;

	m_pTZOOMSCROLL->GetScrollPos(nRng, nPos);
	m_pTMAP->m_fTSCALE = TMINIMAP_INIT_SCALE / powf(TMINIMAP_SCALE_FACTOR, (FLOAT)nPos);

	CRect rect(
		0, 0,
		TMINIMAPTEX_SIZE,
		TMINIMAPTEX_SIZE);

	rect.OffsetRect(
		m_rc.left + m_rcAREA.left - (190 - m_rcAREA.Width()) / 0.85,  //OVLIVNUJE
		m_rc.top + m_rcAREA.top - (190 - m_rcAREA.Height()) / 0.65); //ZKUSIT POØEŠIT KSD

	/*TNLVERTEX vRECT[] = {
		{ FLOAT(rect.left), FLOAT(rect.top), 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f},
		{ FLOAT(rect.right), FLOAT(rect.top), 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f},
		{ FLOAT(rect.left), FLOAT(rect.bottom), 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f},
		{ FLOAT(rect.right), FLOAT(rect.bottom), 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f}};
		
		
	int i;
		const int NUMPOINTS = 24*2;
        const float PI = 3.14159;
			TNLVERTEX * pkCircle;
    pkCircle = new TNLVERTEX[NUMPOINTS + 1];

	for(i=0; i<=NUMPOINTS; i++)
	{
	pkCircle[i].m_fPosX = FLOAT(rect.left);
pkCircle[i].m_fPosY = FLOAT(rect.right);
pkCircle[i].m_fPosZ = 0.5f;
pkCircle[i].m_fRHW = 1.0f;
pkCircle[i].m_dwColor = 0xFFFFFFFF;
pkCircle[i].m_fU = 0.5f;
pkCircle[i].m_fV = 0.5f;

	FLOAT fMIP = 0.0f;

//	m_pDevice->m_pDevice->SetSamplerState( 0, D3DSAMP_MIPMAPLODBIAS, *((LPDWORD) &fMIP));
//	m_pDevice->m_pDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	m_pDevice->m_pDevice->SetTexture( 0, m_pTMINIMAP);

       m_pDevice->m_pDevice->SetFVF(D3DFVF_TL);
	m_pDevice->m_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &pkCircle[0], sizeof(pkCircle[0]));
	}
	*/
	
	int nRng;
	int nPos;

	m_pTZOOMSCROLL->GetScrollPos(nRng, nPos);
	m_pTMAP->m_fTSCALE = TMINIMAP_INIT_SCALE / powf(TMINIMAP_SCALE_FACTOR, (FLOAT)nPos);

	CPoint rect(TMINIMAPTEX_SIZE);

	
	rect.Offset(
		m_rc.left + m_rcAREA.left - (190 - m_rcAREA.Width()),  //OVLIVNUJE
		m_rc.top + m_rcAREA.top - (190 - m_rcAREA.Height())); 
	
   TNLVERTEX verts[CIRCLE_RESOLUTION+1];
float WedgeAngle = ( float )( ( 2 * D3DX_PI ) / CIRCLE_RESOLUTION );
rect.x -= 110;
rect.y += 82;
    for (int i = 0; i < CIRCLE_RESOLUTION+1; i++)
    {
		  float Theta        = ( float )( i * WedgeAngle ); 

        verts[i].m_fPosX = rect.x + 97*cos(D3DX_PI*(i/(CIRCLE_RESOLUTION/2.0f)));
        verts[i].m_fPosY = rect.y + 97*sin(D3DX_PI*(i/(CIRCLE_RESOLUTION/2.0f)));
        verts[i].m_fPosZ = 0;
        verts[i].m_fRHW = 1.0f;
        verts[i].m_dwColor = 0xFFFFFFFF;
		verts[i].m_fU = (float)( 0.5 + 0.5 * cos( Theta ) );
verts[i].m_fV = (float)( 0.5 + 0.5 * sin( Theta ) );// -- ++ 
    }
		FLOAT fMIP = 0.0f;

	m_pDevice->m_pDevice->SetSamplerState( 0, D3DSAMP_MIPMAPLODBIAS, *((LPDWORD) &fMIP));
	m_pDevice->m_pDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
m_pDevice->m_pDevice->SetTexture(0, m_pTMINIMAP);
    m_pDevice->m_pDevice->SetFVF(T3DFVF_TNLVERTEX);
    m_pDevice->m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, CIRCLE_RESOLUTION, &verts, sizeof(TNLVERTEX));
  //  RestoreStates( m_pDevice->m_pDevice ); 
  /*
	const int NUMPOINTS = 64;
const float PI = 3.14159;
TNLVERTEX Circle[NUMPOINTS + 1];
int i;
float X;
float Y;
float Theta;
float WedgeAngle; //Size of angle between two points on the circle (single wedge)
//Precompute WedgeAngle
WedgeAngle = (float)((2*PI) / NUMPOINTS);
//Set up vertices for a circle
//Used <= in the for statement to ensure last point meets first point (closed circle)
for(i=0; i<NUMPOINTS+1; i++)
{
//Calculate theta for this vertex
Theta = i * WedgeAngle;
 
//Compute X and Y locations
X = (float)(rect.x + 98 * cos(Theta));
Y = (float)(rect.y - 98 * sin(Theta));
Circle[i].m_fPosX = X;
Circle[i].m_fPosY = Y;
Circle[i].m_fPosZ = 0;
Circle[i].m_fU = 0.0f;
Circle[i].m_fV = 0.0f;
Circle[i].m_fRHW = 1.0f;
Circle[i].m_dwColor = 0xFFFFFFFF;

}
//Now draw the circle
m_pDevice->m_pDevice->SetFVF(T3DFVF_TNLVERTEX);
m_pDevice->m_pDevice->SetTexture(0, m_pTMINIMAP);
//dev->SetVertexShader (D3DFVF_MIRUSVERTEX);
m_pDevice->m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, NUMPOINTS, &Circle, sizeof(TNLVERTEX));
*/
/*

void  CTMinimapDlg::RenderTMINIMAP()
{
		int nRng;
	int nPos;

	m_pTZOOMSCROLL->GetScrollPos(nRng, nPos);
	m_pTMAP->m_fTSCALE = TMINIMAP_INIT_SCALE / powf(TMINIMAP_SCALE_FACTOR, (FLOAT)nPos);

	CRect rect(
		0, 0,
		TMINIMAPTEX_SIZE,
		TMINIMAPTEX_SIZE);

	rect.OffsetRect(
		m_rc.left + m_rcAREA.left - (190 - m_rcAREA.Width()) / 0.85,  //OVLIVNUJE
		m_rc.top + m_rcAREA.top - (190 - m_rcAREA.Height()) / 0.65); //ZKUSIT POØEŠIT KSD


	const int NUMPOINTS = 400;
        const float PI = 3.14159;
		/*
			FLOAT m_fPosX;
	FLOAT m_fPosY;
	FLOAT m_fPosZ;
	
		/*
FLOAT(rect.left), FLOAT(rect.top), 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f},
		{ FLOAT(rect.right), FLOAT(rect.top), 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f},
		{ FLOAT(rect.left), FLOAT(rect.bottom), 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f},
		{ FLOAT(rect.right), FLOAT(rect.bottom),


	TNLVERTEX * pkCircle;
    pkCircle = new TNLVERTEX[NUMPOINTS + 1];
	int i;
	float X;
	float Y;
	float Theta;
	float WedgeAngle;	//Size of angle between two points on the circle (single wedge)



	//Precompute WedgeAngle
	WedgeAngle = (float)((2*PI) / NUMPOINTS);
D3DCOLOR Color = D3DCOLOR_ARGB( 80, 255, 255, 255 ); // Adjust Alpha
	//Set up vertices for a circle
	//Used <= in the for statement to ensure last point meets first point (closed circle)
	for(i=0; i<=NUMPOINTS; i++)
	{
		//Calculate theta for this vertex
		Theta = i * WedgeAngle;
		

		//Compute X and Y locations
		X = 100;
		Y = -100;


pkCircle[i].m_fPosX = X;
pkCircle[i].m_fPosY = Y;
pkCircle[i].m_fPosZ = 0.5f;
pkCircle[i].m_fRHW = 1.0f;
pkCircle[i].m_dwColor = 0xFFFFFFFF;
pkCircle[i].m_fU = 0.5f;
pkCircle[i].m_fV = 0.5f;



	
	}
const BYTE bBlue[60] = 
{ 
	0x42, 0x4D, 0x3C, 0x00,0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 
	0x28, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 
	0x00, 0x01,0x00, 0x00, 0x00, 0x01, 0x00, 
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 
	0x12, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00 
};


LPDIRECT3DTEXTURE9 Blue = NULL;


	if( Blue == NULL )
		D3DXCreateTextureFromFileInMemory( m_pDevice->m_pDevice, (LPCVOID)&bBlue,  60,  &Blue );

	//Now draw the circle
        m_pDevice->m_pDevice->SetFVF(D3DFVF_TL);
	m_pDevice->m_pDevice->SetTexture(0, m_pTMINIMAP);
	m_pDevice->m_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &pkCircle[0], sizeof(pkCircle[0]));

}//Draw2DCircle

*/
}

	void DrawCircle(IDirect3DDevice9* Device, float CX, float CY, float Radius, D3DCOLOR Colour)
{
	/*
    static const int Resolution = 10;
    TNLVERTEX Vertices[Resolution];

    for (int I = 0; I < Resolution; ++I)
    {
        Vertices[I].m_fPosX = CX + Radius * cos(3.141592654f * (I / (Resolution / 2.0f)));
        Vertices[I].m_fPosY = CY + Radius * sin(3.141592654f * (I / (Resolution / 2.0f)));
        Vertices[I].m_fPosZ = 0.0f;
        Vertices[I].m_fRHW = 1.0f;
        Vertices[I].m_dwColor = Colour;
        Vertices[I].m_fU = 0.0f;
        Vertices[I].m_fV = 0.0f;
    }

    Device->SetFVF(VERTEX_FVF_TEX);
	//Device->SetTexture(0, CTMinimapDlg::m_pTMINIMAP);
    Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, Resolution - 2, Vertices, sizeof(TNLVERTEX));
	*/
}	
HRESULT CTMinimapDlg::Render( DWORD dwTickCount)
{

	CTClientChar* pMainChar = CTClientGame::GetInstance()->GetMainChar();
	if( !pMainChar->m_bFlash )
	{
		if( m_bVisible && !m_bMinimize )
		{
			m_pTMAP->ResetTMINIMAP(
				m_pTMINIMAP,
				m_pTMON,
				m_pTRSCS,
				m_pHost,
				m_pDevice,
				m_pCAM);
			RenderTMINIMAP();
		//	DrawCircle(m_pDevice->m_pDevice,100,100,1.2f,0xFFFFFFFF);
		}

		return CTClientUIBase::Render(dwTickCount);
	}

	return S_OK;
}
