/*
 * PraticusQuaero.hpp
 *
 *  Created on: May 25, 2014
 *      Author: lex
 */

#ifndef PRATICUSQUAERO_HPP_
#define PRATICUSQUAERO_HPP_

#include "../OculusPraticus.hpp"

const std::string jpgDir = "../Templates";

typedef enum
{
	QUAERO_NO_ORIENATATION = -1,
	QUAERO_PARENT_CONTOUR = 0,
	QUAERO_CHILD_CONTOUR,
}ContourPosition;


/*
 * SubQuaero represents a single parent/children contour with calculated moments
 */

class SubQuaero
{
public:
	SubQuaero();

	~SubQuaero();

	ContourPosition m_position;

	vector <Point>  m_contour;

	Moments m_contourMoments;

	double m_huMoments[7];

};

/*
 * QuaeroEx represents a single figure currently involved in work
 */

class QuaeroEx
{
public:
	QuaeroEx();

	~QuaeroEx();

	uint m_type;

	uint m_subtype;

	uint m_numOfChildrens;

	SubQuaero* m_outQuaero;

	list<SubQuaero*> m_innerQuaero;

	string m_quaeroName;
	//Note: m_outQuaero should be filled first
	bool FillParentQuaero();
	//Note: m_innerQuaero list should be filled first
	bool FillChildQuaero();
};


class PraticusQuaero: protected OculusPraticus
{
public:
	OculusPraticus* CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );

	PraticusQuaero();

	PraticusQuaero( OculusPraefectus* praefectus, PraticusType _praticusType, string _praticusName );

	virtual ~PraticusQuaero();
	// find a templates from JPG in specific directory
	void PrimordialisQuaero(std::string dirName);

	uint m_minContourArea;

	uint m_minContourLength;

	double m_huMatchCriteria;

	bool m_allowChildlessContours;

protected:

	virtual int Processus( );

	bool ExtractQuaeroFromImage( std::string filePath );
	//method returns number of the top contour
	int FindOutContourFromTemplateImage( vector<Vec4i> &frameContoursHierarchy, uint contourSize );

	std::list<QuaeroEx*> m_quaeroList;


};



#endif /* PRATICUSQUAERO_HPP_ */
