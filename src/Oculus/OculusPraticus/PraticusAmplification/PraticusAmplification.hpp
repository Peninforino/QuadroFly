/*
 * PraticusAmplification.hpp
 *
 *  Created on: May 24, 2014
 *      Author: lex
 */

#ifndef PRATICUSAMPLIFICATION_HPP_
#define PRATICUSAMPLIFICATION_HPP_

#include "../OculusPraticus.hpp"

class PraticusAmplification: protected OculusPraticus
{
public:
	virtual OculusPraticus* CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );
	PraticusAmplification();

	PraticusAmplification( OculusPraefectus* praefectus, PraticusType _praticusType, string _praticusName );

	virtual ~PraticusAmplification();

protected:
	//TODO: implement this parameter which will describe all necessary IQ operations
	bool imageQulityOperators;
	//this method applies image quality operations
	void ApplyImageQuality();

	Imaginis* m_workFrame;

	virtual int Processus( );
};

/* AmplificationMembrum - represents any IQ filter
 *
 */
class AmplificationMembrum
{

};

/* AmplificationCapitis - IQ manager
 *
 */
class AmplificationCapitis
{

};



#endif /* PRATICUSAMPLIFICATION_HPP_ */
