/*
 * PraticusHaurire.hpp
 *
 *  Created on: May 25, 2014
 *      Author: lex
 */

#ifndef PRATICUSHAURIRE_HPP_
#define PRATICUSHAURIRE_HPP_

#include "../OculusPraticus.hpp"

class PraticusHaurire: protected OculusPraticus
{
public:
	virtual OculusPraticus* CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );
	PraticusHaurire();

	PraticusHaurire( OculusPraefectus* praefectus, PraticusType _praticusType, string _praticusName );

	virtual ~PraticusHaurire();

protected:

	virtual int Processus( );
};


#endif /* PRATICUSHAURIRE_HPP_ */
