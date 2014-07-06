/*
 * PraticusHistoriam.cpp
 *
 *  Created on: May 25, 2014
 *      Author: lex
 */

#include "PraticusHistoriam.hpp"

PraticusHistoriam::PraticusHistoriam( OculusPraefectus* _praefectus,
								PraticusType _praticusType,
								string _praticusName ):OculusPraticus(_praefectus, _praticusType, _praticusName)
{
	return;
}

PraticusHistoriam::~PraticusHistoriam()
{

}


OculusPraticus* PraticusHistoriam::CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	OculusPraticus* historiam = new PraticusHistoriam( _praefectus, _praticusType, _praticusName);

	return historiam;
}

int PraticusHistoriam::Processus()
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

OculusPraticus* CreatePraticusHistoriam( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	cout << __FUNCTION__ << endl;

	PraticusHistoriam* historiam;

	OculusPraticus* praticus = historiam->PraticusHistoriam::CreatePraticus( _praefectus, _praticusType, _praticusName );

	return praticus;
}



