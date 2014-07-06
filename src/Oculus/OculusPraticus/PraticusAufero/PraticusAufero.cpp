/*
 * PraticusAufero.cpp
 *
 *  Created on: May 25, 2014
 *      Author: lex
 */

#include "PraticusAufero.hpp"

PraticusAufero::PraticusAufero( OculusPraefectus* _praefectus,
								PraticusType _praticusType,
								string _praticusName ):OculusPraticus(_praefectus, _praticusType, _praticusName)
{
	return;
}

PraticusAufero::~PraticusAufero()
{

}


OculusPraticus* PraticusAufero::CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	OculusPraticus* aufero = new PraticusAufero( _praefectus, _praticusType, _praticusName);

	return aufero;
}

int PraticusAufero::Processus()
{
	Imaginis* workFrame;
	RecieveStatus result = ImaginisRecieve(0, &workFrame);

	if ( ( result == IMAGE_RECIEVE_STATUS_NO_DATA ) ||
		 ( result == IMAGE_RECIEVE_STATUS_ERROR ) )
	{
		return 0;
	}
	cout << GetPraticusName() << ": image received" << workFrame->frameNumber << endl;

	delete workFrame;

	return 0;
}

OculusPraticus* CreatePraticusAufero( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	cout << __FUNCTION__ << endl;

	PraticusAufero* aufero;

	OculusPraticus* praticus = aufero->PraticusAufero::CreatePraticus( _praefectus, _praticusType, _praticusName );

	return praticus;
}



