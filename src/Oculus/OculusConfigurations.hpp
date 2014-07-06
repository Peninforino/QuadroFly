/*
 * OculusConfigurations.hpp
 *
 *  Created on: Apr 7, 2014
 *      Author: lex
 */
#ifndef OCULUSCONFIGURATIONS_HPP_
#define OCULUSCONFIGURATIONS_HPP_


#include "../Includes/OculusDefinitions.hpp"


static PraticusConfiguration praticusConfigForOculusDefalut[] =
{
	PraticusConfiguration(PRATICUS_SOURCE,         "ImageSource" ),
	PraticusConfiguration(PRATICUS_AMPLIFICATION,  "ImageAmplificator" ),
	PraticusConfiguration(PRATICUS_MITTENTIS,      "ImageMitentiator" ),
	PraticusConfiguration(PRATICUS_QUAERO,         "ImageQuaero" ),
	PraticusConfiguration(PRATICUS_HISTORIAM,      "ImageHistoriam" ),
	PraticusConfiguration(PRATICUS_HAURIRE,        "ImageHaurire" ),
	PraticusConfiguration(PRATICUS_AUFERO,         "ImageAufero" ),
	PraticusConfiguration(PRATICUS_MAX,            "")
};

static PraticusConnection praticusConnectionsForOculusDefault[] =
{
	PraticusConnection(PRATICUS_SOURCE,        0, PRATICUS_AMPLIFICATION, 0, 3 ),
	PraticusConnection(PRATICUS_AMPLIFICATION, 0, PRATICUS_MITTENTIS,     0, 3 ),
	PraticusConnection(PRATICUS_MITTENTIS,     0, PRATICUS_QUAERO,        0, 3 ),
	PraticusConnection(PRATICUS_QUAERO,        0, PRATICUS_HISTORIAM,     0, 10 ),
	PraticusConnection(PRATICUS_HISTORIAM,     0, PRATICUS_HAURIRE,       0, 3 ),
	PraticusConnection(PRATICUS_HAURIRE,       0, PRATICUS_AUFERO,        0, 3 ),
	PraticusConnection(PRATICUS_AUFERO,        0, PRATICUS_MAX,           0, 0 )
};

static PraticusConfiguration praticusConfigForOculusWithoutDisplay[] =
{
	PraticusConfiguration(PRATICUS_SOURCE,         "ImageSource" ),
	PraticusConfiguration(PRATICUS_AMPLIFICATION,  "ImageAmplificator" ),
	PraticusConfiguration(PRATICUS_MITTENTIS,      "ImageMitentiator" ),
	PraticusConfiguration(PRATICUS_QUAERO,         "ImageQuaero" ),
	PraticusConfiguration(PRATICUS_HISTORIAM,      "ImageHistoriam" ),
	PraticusConfiguration(PRATICUS_AUFERO,         "ImageAufero" ),
	PraticusConfiguration(PRATICUS_MAX,            "" )
};

static PraticusConnection praticusConnectionsForOculusWithoutDisplay[] =
{
	PraticusConnection(PRATICUS_SOURCE,        0, PRATICUS_AMPLIFICATION, 0, 3 ),
	PraticusConnection(PRATICUS_AMPLIFICATION, 0, PRATICUS_MITTENTIS,     0, 3 ),
	PraticusConnection(PRATICUS_MITTENTIS,     0, PRATICUS_QUAERO,        0, 3 ),
	PraticusConnection(PRATICUS_QUAERO,        0, PRATICUS_HISTORIAM,     0, 10 ),
	PraticusConnection(PRATICUS_HISTORIAM,     0, PRATICUS_AUFERO,        0, 3 ),
	PraticusConnection(PRATICUS_AUFERO,        0, PRATICUS_MAX,           0, 0 )
};

static OculusConfiguration mainOculusConfiguration[] =
{
	{
		praticusConfigForOculusDefalut,
		praticusConnectionsForOculusDefault,
		OC_PRAEFECTUS_TYPE_DEFAULT
	},
	{
		praticusConfigForOculusWithoutDisplay,
		praticusConnectionsForOculusWithoutDisplay,
		OC_PRAEFECTUS_TYPE_WITHOUT_DISPLAY
	}

};

////////////////////////////////////////////////////////////////////////////////////////

static VideoParameters baseVideoParam =
{
	0,   //deviceNum
	640, //videoWidth
	480, //videoHeight
	30 //desiredFPS
};

GaussianBlurParameter baseGausBlurParam =
{
	cv::Size(3,3), //kernSize
	0, //sigmaX
	0 //sigmaY
};

IQParameters baseIQParam[] =

{
	{
		IQ_TYPE_GAUSSIAN_BLUR,
		(void*)&baseGausBlurParam
	},
	{
		IQ_TYPE_MAX,
		NULL
	}
};

OculusParameters baseOculusParam =
{
	&baseVideoParam, //videoParam
	baseIQParam, //IQParameters
	"Templates" //templateDir
};

#endif
