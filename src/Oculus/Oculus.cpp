/*
 * Oculus.cpp
 *
 *  Created on: Apr 7, 2014
 *      Author: lex
 */


#include "OculusConfigurations.hpp"
#include "OculusPraticus/OculusPraticus.hpp"
#include "OculusPraticus/PraticusQuaero/PraticusQuaero.hpp"
#include <assert.h>

OculusPraefectus* OculusPraefectus::praefectusEx = NULL;

OculusPraefectus::OculusPraefectus():m_currentOculusConfig(NULL)
{
}



OculusPraticus* OculusPraefectus::OculusCreatePraticusById( PraticusType praticusId, string praticusName )
{
	switch ( praticusId )
	{
		case PRATICUS_SOURCE:
		{
			//create source
			return CreatePraticusSource( this, praticusId, praticusName );
		}
		case PRATICUS_AMPLIFICATION:
		{
			//create amplification - image quality
			return CreatePraticusAmplification( this, praticusId, praticusName );
		}
		case PRATICUS_MITTENTIS:
		{
			//create mittentis - wifi streaming
			return CreatePraticusMittentis( this, praticusId, praticusName );
		}
		case PRATICUS_QUAERO:
		{
			//create quaero - template recognition
			return CreatePraticusQuaero( this, praticusId, praticusName );
		}
		case PRATICUS_HISTORIAM:
		{
			//create historiam - motion history
			return CreatePraticusHistoriam( this, praticusId, praticusName );
		}
		case PRATICUS_HAURIRE:
		{
			//create haurare - image display
			return CreatePraticusHaurire( this, praticusId, praticusName );
		}
		case PRATICUS_AUFERO:
		{
			//create aufero - cleanup
			return CreatePraticusAufero( this, praticusId, praticusName );
		}
		case PRATICUS_NULL:
		{
			return NULL;
		}
		default:
		{
			assert( 0 );
		}
	}
	return NULL;
}

bool OculusPraefectus::OculusCreatePraticus( )
{
	assert(m_currentOculusConfig);
	cout << __FUNCTION__ << endl;
	OculuspraticusList.clear();

	for ( int i =0; i < PRATICUS_MAX && m_currentOculusConfig->praticusList[i].praticusId != PRATICUS_MAX; i++ )
	{
		cout << "Going to create Praticus type " << m_currentOculusConfig->praticusList[i].praticusId << endl;

		OculusPraticus* praticus = OculusCreatePraticusById( m_currentOculusConfig->praticusList[i].praticusId,
															 m_currentOculusConfig->praticusList[i].praticusName );

		OculuspraticusList.push_back( praticus );
	}
	cout << __FUNCTION__ << " succeed"<< endl;
	return true;
}

OculusPraticus* OculusPraefectus::OculusGetPraticusByType( PraticusType praticusType )
{
	assert( OculuspraticusList.empty() != true );
	assert( praticusType < PRATICUS_MAX );
	list<OculusPraticus*>::iterator it;

	for ( it = OculuspraticusList.begin(); it!=OculuspraticusList.end(); ++it )
	{
		if ( (*it)->GetPraticusType() == praticusType )
		{
			return *it;
		}
	}
	return NULL;
}

bool OculusPraefectus::OculusConnectPraticus( )
{
	assert(m_currentOculusConfig);
	cout << __FUNCTION__ << endl;

	for ( int i =0; i < PRATICUS_MAX && m_currentOculusConfig->connectionList[i].secondPraticus != PRATICUS_MAX; i++ )
	{
		OculusPraticus* first = OculusGetPraticusByType(m_currentOculusConfig->connectionList[i].firstPraticus);

		OculusPraticus* second = OculusGetPraticusByType(m_currentOculusConfig->connectionList[i].secondPraticus);

		PraticusQueue* queue = PraticusQueue::CreateQueueBetween( first,
														  m_currentOculusConfig->connectionList[i].firstPraticusOut,
														  second,
														  m_currentOculusConfig->connectionList[i].secondPraticusIn,
														  m_currentOculusConfig->connectionList[i].qSize );

		OculusConnectionsList.push_back( queue );
	}
	cout << __FUNCTION__ << " succeed" << endl;
	return true;
}

bool OculusPraefectus::OculusFindConfigurationType( OcPraefectusType praefectusType )
{
	cout << __FUNCTION__ << endl;

	assert( praefectusType < OC_PRAEFECTUS_TYPE_MAX );
	assert( mainOculusConfiguration != NULL );
	m_currentOculusConfig = &mainOculusConfiguration[praefectusType];

	cout << __FUNCTION__ << " succeed" << endl;

	return true;

}

bool OculusPraefectus::OculusInitPraefectus( OcPraefectusType praefectusType )
{
	cout << __FUNCTION__ << endl;

	bool result = OculusFindConfigurationType( praefectusType );
	if ( result == false )
	{
		cout << __FUNCTION__ << " failed to get Oculus configuration" << endl;
		return false;
	}

	result = OculusCreatePraticus();
	if ( result == false )
	{
		cout << __FUNCTION__ << " failed to create Praticuses" << endl;
		return false;
	}

	result = OculusConnectPraticus();
	if ( result == false )
	{
		cout << __FUNCTION__ << " failed to connect Praticuses" << endl;
		return false;
	}
	return true;
}

bool OculusPraefectus::OculusPraticusAnimatis()
{
	list<OculusPraticus*>::iterator it;

	for ( it = OculuspraticusList.begin(); it!=OculuspraticusList.end(); ++it )
	{
		cout << __FUNCTION__ << " going to alive " << (*it)->GetPraticusName() << endl;
		(*it)->SetPraticusState( PRATICUS_STATE_RUN );
	}

	return true;
}

bool OculusPraefectus::OculusSpawnPraticusesTasks()
{
	list<OculusPraticus*>::iterator it;

	for ( it = OculuspraticusList.begin(); it!=OculuspraticusList.end(); ++it )
	{
		cout << __FUNCTION__ << " going to spawn Task for " << (*it)->GetPraticusName() << endl;
		(*it)->Facere();
	}

	return true;
}

bool OculusPraefectus::OculusPraestarePraeviamInstallation( OculusParameters* ocParams )
{
	m_currentFlowConfig = ocParams;

	OculusPraticus* quaeroPraticus = OculusGetPraticusByType(PRATICUS_QUAERO);
	if ( quaeroPraticus != NULL )
	{
		PraticusQuaero* quaero = NULL;
		quaero = dynamic_cast<PraticusQuaero*>( quaeroPraticus );
		quaero->PrimordialisQuaero( m_currentFlowConfig->templateDir );
	}
	return true;
}

void OculusPraefectus::OculusDumpAllPraticuses()
{
	cout << __FUNCTION__ << " start" << endl;

	if ( ( OculuspraticusList.empty() == true ) &&
		 ( OculusConnectionsList.empty() == true ) )
	{
		return;
	}

	list<OculusPraticus*>::iterator it;

	for ( it = OculuspraticusList.begin(); it != OculuspraticusList.end(); ++it)
	{
		cout << "Praticus " << (*it)->GetPraticusName() << endl;
		for (uint i = 0; i < maxPraticusConnections; i++)
		{
			PraticusQueue* inQueue = (*it)->GetInputQueue( i );
			if ( inQueue != NULL)
			{
				cout << "Input connection " << i << " from " << inQueue->GetSourcePraticus()->GetPraticusName() << endl;
			}
			else
			{
				cout << "Input connection " << i << " is empty" << endl;
			}
		}
		for (uint i = 0; i < maxPraticusConnections; i++)
		{
			PraticusQueue* outQueue = (*it)->GetOutputQueue( i );
			if ( outQueue != NULL)
			{
				cout << "Output connection " << i << " from " << outQueue->GetTragetPraticus()->GetPraticusName() << endl;
			}
			else
			{
				cout << "Output connection " << i << " is empty" << endl;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

bool CreateOculus( OcPraefectusType ocType, hOculus &hPraefectus)
{
	cout << __FUNCTION__ << endl;
	//get handler
	hPraefectus = hPraefectus->OculusGetPraefectus( );

	bool result = true;
	//init internal state
	result = hPraefectus->OculusInitPraefectus( ocType );

	return result;
}

bool ConfigOculus( hOculus hPraefectus, OculusParameters* ocParams )
{
	if ( hPraefectus == NULL)
	{
		return false;
	}
	else
	{
		return hPraefectus->OculusPraestarePraeviamInstallation( ocParams );
	}

}

bool RunOculus( hOculus hPraefectus )
{
	bool result = hPraefectus->OculusSpawnPraticusesTasks();

	hPraefectus->OculusPraticusAnimatis();

	return result;
}



