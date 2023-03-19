#pragma once


class CTBowRegister : public CTClientUIBase
{

public:

	TButton*	m_pRegister;
	TComponent* m_pText;


public:


public:
	CTBowRegister( TComponent *pParent, LP_FRAMEDESC pDesc );
	virtual ~CTBowRegister();
};