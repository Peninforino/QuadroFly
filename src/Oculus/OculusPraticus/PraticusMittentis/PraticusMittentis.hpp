/*
 * PraticusMittentis.hpp
 *
 *  Created on: May 25, 2014
 *      Author: lex
 */

#ifndef PRATICUSMITTENTIS_HPP_
#define PRATICUSMITTENTIS_HPP_

#include "../OculusPraticus.hpp"

class PraticusMittentis: protected OculusPraticus
{
public:
	OculusPraticus* CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );
	PraticusMittentis();

	PraticusMittentis( OculusPraefectus* praefectus, PraticusType _praticusType, string _praticusName );

	virtual ~PraticusMittentis();

protected:

	virtual int Processus( );
};


#endif /* PRATICUSMITTENTIS_HPP_ */
