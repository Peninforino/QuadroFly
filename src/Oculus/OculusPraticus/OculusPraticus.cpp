
/*
 * OculusPraticus.cpp
 *
 *  Created on: Feb 26, 2014
 *      Author: lex
 */

#include "OculusPraticus.hpp"

#define DEBUG_QUEUE_CONNECTION 0
/////////////////////////////////////////////////////////////////////////////

void OculusPraticus::Facere()
{
	m_taskExecuter = boostThrPtr(new boost::thread(boost::bind(&OculusPraticus::PraticusCuram, this)));
	return;
}

int OculusPraticus::Abortum()
{
	cout << m_praticusName << " terminated" << endl;
	return 0;
}

OculusPraticus::OculusPraticus():m_actualTimeStamp(0),
								 m_praticusName(""),
								 m_praticusType(PRATICUS_MAX),
								 m_praticusState(PRATICUS_STATE_IDLE),
								 m_praefectus(NULL)
{
	for ( uint i = 0; i < maxPraticusConnections; i++ )
	{
		m_inputQueue[i] = NULL;
		m_outputQueue[i] = NULL;
	}

	return;
}

OculusPraticus::OculusPraticus(OculusPraefectus* praefectus,
							   PraticusType _praticusType,
							   string _praticusName ):
								m_actualTimeStamp(0),
								m_praticusName(_praticusName),
								m_praticusType(_praticusType),
								m_praticusState(PRATICUS_STATE_IDLE),
								m_praefectus(praefectus)
{
	for ( uint i = 0; i < maxPraticusConnections; i++ )
	{
		m_inputQueue[i] = NULL;
		m_outputQueue[i] = NULL;
	}

	return;
}

bool OculusPraticus::SetInputQueue (PraticusQueue* inQ, uint inNum )
{
	assert(inNum <= maxPraticusConnectionNum);
	#if DEBUG_QUEUE_CONNECTION
		cout << GetPraticusName() << "::" << __FUNCTION__ << " received " << inQ << " as input # " << inNum << endl;
	#endif
	m_inputQueue[inNum] = inQ;

	return true;
}

bool OculusPraticus::SetOutputQueue (PraticusQueue* outQ, uint outNum )
{
	assert(outNum <= maxPraticusConnectionNum);
	#if DEBUG_QUEUE_CONNECTION
		cout << GetPraticusName() << "::" << __FUNCTION__ << " received " << outQ << " as output # " << outNum << endl;
	#endif
	m_outputQueue[outNum] = outQ;

	return true;
}

OculusPraticus::~OculusPraticus()
{
	return;
}

RecieveStatus OculusPraticus::ImaginisRecieve( uint inQNum, Imaginis** Image )
{
	assert( inQNum <= maxPraticusConnectionNum );
	RecieveStatus res = m_inputQueue[inQNum]->Recieve(Image);
	return res;
}

DeliverStatus OculusPraticus::ImaginisSend( uint outQNum , Imaginis* image )
{
	assert( outQNum <= maxPraticusConnectionNum );
	cout << GetPraticusName() << " going to call to " << m_outputQueue[outQNum] << " to deliver sample" << endl;
	DeliverStatus res = m_outputQueue[outQNum]->Deliver(image);
	return res;
}

DeliverStatus OculusPraticus::ImaginisSend( Imaginis* image )
{
	DeliverStatus res = IMAGE_DELIVER_STATUS_NORMAL;
	for ( uint i = 0; i < maxPraticusConnections; i++)
	{
		if ( m_outputQueue[i] != NULL )
		{
			res = m_outputQueue[i]->Deliver(image);
		}
	}
	return res;
}

void OculusPraticus::PraticusCuram()
{
	while ( m_praticusState != PRATICUS_STATE_ABORT )
	{
		try
		{
			if ( m_praticusState == PRATICUS_STATE_RUN )
			{
				Processus();
				boost::this_thread::interruption_point();
			}
		}
		catch(boost::thread_interrupted&)
		{
			Abortum();
		}
	}
	Abortum();
	return;
}

/////////////////////////////////////////////////////////////////////////////

PraticusQueue::PraticusQueue( uint _qLimit ): m_qLimit( _qLimit ), m_sourcePraticus(NULL), m_targetPraticus(NULL), m_qSize(0)
{

}

bool PraticusQueue::ConnectSource( OculusPraticus* _firstPraticus, uint firstOut )
{
	assert( _firstPraticus != NULL );
	#if DEBUG_QUEUE_CONNECTION
		cout << __FUNCTION__ <<": going to connect " << _firstPraticus->GetPraticusName() << " " << firstOut <<
			" as a source" << endl;
	#endif
	return _firstPraticus->SetOutputQueue(this, firstOut);
}

bool PraticusQueue::ConnectDesctination( OculusPraticus* _secondPraticus, uint secondIn )
{
	assert( _secondPraticus != NULL );
	#if DEBUG_QUEUE_CONNECTION
		cout << __FUNCTION__ <<": going to connect " << _secondPraticus->GetPraticusName() << " " << secondIn <<
			" as a destination" << endl;
	#endif
	return _secondPraticus->SetInputQueue( this, secondIn );
}

PraticusQueue* PraticusQueue::CreateQueueBetween( OculusPraticus* first, uint firstOut, OculusPraticus* second, uint secondIn, uint qSize )
{
	PraticusQueue* queue = new PraticusQueue( qSize );

	queue->ConnectSource( first, firstOut );
	queue->ConnectDesctination( second, secondIn );

	queue->SetSourcePraticus( first );
	queue->SetTargetPraticus( second );

	cout << __FUNCTION__ << " created queue (" << qSize << ") between " << first->GetPraticusName() << " and " << second->GetPraticusName() << endl;
	return queue;
}

DeliverStatus PraticusQueue::Deliver( Imaginis* Image )
{
	if ( m_qSize + 1 > m_qLimit)
	{
		return IMAGE_DELIVER_STATUS_FULL;
	}
	cout << "Going to deliver Image# " << Image->frameNumber << " from " << m_sourcePraticus->GetPraticusName() << " to " << m_targetPraticus->GetPraticusName() << endl;
	queueProtectionMutex.lock();
	m_queue.push( Image );
	m_qSize++;
	queueProtectionMutex.unlock();

	return IMAGE_DELIVER_STATUS_NORMAL;
}

RecieveStatus PraticusQueue::Recieve( Imaginis** Image )
{
	if ( m_qSize == 0 )
	{
		return IMAGE_RECIEVE_STATUS_NO_DATA;
	}

	queueProtectionMutex.lock();
	Imaginis* result = m_queue.front();
	m_queue.pop();
	m_qSize--;
	queueProtectionMutex.unlock();

	(*Image) = result;

	return IMAGE_RECIEVE_STATUS_NORMAL;

}

////////////////////////////////////////////////////////////////////////////////

Imaginis::Imaginis(uint _width, uint _height): width(_width), height(_height), frameNumber(0), frameEpoch(0), timeStamp(0)
{
	image = new Mat(Size(width, height), CV_8UC3);
}

Imaginis::Imaginis()
{
	image = NULL;
}

Imaginis::~Imaginis()
{
	image->release();
}

