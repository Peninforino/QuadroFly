/*
 * PraticusMittentis.cpp
 *
 *  Created on: May 25, 2014
 *      Author: lex
 */

#include "PraticusMittentis.hpp"

PraticusMittentis::PraticusMittentis( OculusPraefectus* _praefectus,
								PraticusType _praticusType,
								string _praticusName ):OculusPraticus(_praefectus, _praticusType, _praticusName)
{
	return;
}

PraticusMittentis::~PraticusMittentis()
{

}


OculusPraticus* PraticusMittentis::CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	OculusPraticus* mittentis = new PraticusMittentis( _praefectus, _praticusType, _praticusName);

	return mittentis;
}

int PraticusMittentis::Processus()
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

OculusPraticus* CreatePraticusMittentis( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	cout << __FUNCTION__ << endl;

	PraticusMittentis* mittentis;

	OculusPraticus* praticus = mittentis->PraticusMittentis::CreatePraticus( _praefectus, _praticusType, _praticusName );

	return praticus;
}



