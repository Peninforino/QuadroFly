/*
 * PraticusAufero.hpp
 *
 *  Created on: May 25, 2014
 *      Author: lex
 */

#ifndef PRATICUSAUFERO_HPP_
#define PRATICUSAUFERO_HPP_

#include "../OculusPraticus.hpp"

class PraticusAufero: protected OculusPraticus
{
public:
	virtual OculusPraticus* CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );
	PraticusAufero();

	PraticusAufero( OculusPraefectus* praefectus, PraticusType _praticusType, string _praticusName );

	virtual ~PraticusAufero();

protected:

	virtual int Processus( );
};



#endif /* PRATICUSAUFERO_HPP_ */
