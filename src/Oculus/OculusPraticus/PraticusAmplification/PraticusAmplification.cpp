/*
 * PraticusAmplification.cpp
 *
 *  Created on: May 24, 2014
 *      Author: lex
 */

#include "PraticusAmplification.hpp"

PraticusAmplification::PraticusAmplification( OculusPraefectus* _praefectus,
								PraticusType _praticusType,
								string _praticusName ):OculusPraticus(_praefectus, _praticusType, _praticusName),
													   m_workFrame(NULL)
{
	//TODO: implement method below
	//imageQulityOperators = m_praefectus->OculusGetIQConfiguration();

	return;
}

PraticusAmplification::~PraticusAmplification()
{

}

void PraticusAmplification::ApplyImageQuality()
{
	return;
}


OculusPraticus* PraticusAmplification::CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	OculusPraticus* amplification = new PraticusAmplification( _praefectus, _praticusType, _praticusName);

	return amplification;
}

int PraticusAmplification::Processus()
{
	Imaginis* workFrame;
	RecieveStatus result = ImaginisRecieve(0, &workFrame);

	if ( ( result == IMAGE_RECIEVE_STATUS_NO_DATA ) ||
		 ( result == IMAGE_RECIEVE_STATUS_ERROR ) )
	{
		return 0;
	}
	cout << GetPraticusName() << ": image received " << workFrame->frameNumber << endl;

	m_workFrame = workFrame;

	ApplyImageQuality();

	ImaginisSend(0, workFrame);

	return 0;
}

OculusPraticus* CreatePraticusAmplification( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	cout << __FUNCTION__ << endl;

	PraticusAmplification* amplification;

	OculusPraticus* praticus = amplification->PraticusAmplification::CreatePraticus( _praefectus, _praticusType, _praticusName );

	return praticus;
}

