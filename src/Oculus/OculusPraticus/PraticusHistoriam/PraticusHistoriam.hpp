/*
 * PraticusHistoriam.hpp
 *
 *  Created on: May 25, 2014
 *      Author: lex
 */

#ifndef PRATICUSHISTORIAM_HPP_
#define PRATICUSHISTORIAM_HPP_

#include "../OculusPraticus.hpp"

class PraticusHistoriam: protected OculusPraticus
{
public:
	OculusPraticus* CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );
	PraticusHistoriam();

	PraticusHistoriam( OculusPraefectus* praefectus, PraticusType _praticusType, string _praticusName );

	virtual ~PraticusHistoriam();

protected:

	virtual int Processus( );
};


#endif /* PRATICUSHISTORIAM_HPP_ */
