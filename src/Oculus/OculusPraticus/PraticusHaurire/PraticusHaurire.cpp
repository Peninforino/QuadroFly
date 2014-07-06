/*
 * PraticusHaurire.cpp
 *
 *  Created on: May 25, 2014
 *      Author: lex
 */

#include "PraticusHaurire.hpp"

PraticusHaurire::PraticusHaurire( OculusPraefectus* _praefectus,
								PraticusType _praticusType,
								string _praticusName ):OculusPraticus(_praefectus, _praticusType, _praticusName)
{
	return;
}

PraticusHaurire::~PraticusHaurire()
{

}


OculusPraticus* PraticusHaurire::CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	OculusPraticus* haurire = new PraticusHaurire( _praefectus, _praticusType, _praticusName);

	return haurire;
}

int PraticusHaurire::Processus()
{
	Imaginis* workFrame;
	RecieveStatus result = ImaginisRecieve(0, &workFrame);

	if ( ( result == IMAGE_RECIEVE_STATUS_NO_DATA ) ||
		 ( result == IMAGE_RECIEVE_STATUS_ERROR ) )
	{
		return 0;
	}
	cout << GetPraticusName() << ": image received" << workFrame->frameNumber << endl;

	ImaginisSend(0, workFrame);

	return 0;
}

OculusPraticus* CreatePraticusHaurire( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	cout << __FUNCTION__ << endl;

	PraticusHaurire* haurire;

	OculusPraticus* praticus = haurire->PraticusHaurire::CreatePraticus( _praefectus, _praticusType, _praticusName );

	return praticus;

}


