/*---------------------------------------------------------------
 
 Date de Creation:	21.03.2007
 Description:		Classe vecteur permettant le positionnement par 3 coordonnées
 Methodes:			Construct/Destruct
 get & set coordonnees
 
 Modification:
 28.03.07:		suppression de la methode affiche et compare en faveur d' operateurs
 20.04.07:		Ajout et suppression de l'operateur < et >, car il n'est pas utile, vu qu'on ne peut pas associer tous
 les cas ou une part sort de l'enceinte, mais on doit dissocier selon la paroi qu'elle traverse.
 ---------------------------------------------------------------*/

#ifndef V2Dh
#define V2Dh

#include <iostream>
#include <cmath>

using namespace std;

class V2D
{
public:
	//Constructeurs
	
    V2D();
    V2D(double x, double y);
    V2D( V2D const& v);
    ~V2D() {}
    
	//Methodes Publiques
    
    void getCoords(double& x, double& y) const;
    void setCoords(double x, double y);
    
    double getNorm() const ;													//!< returns ||v||^2
    double getX() const  ;
    double getY() const ;
    void setX(double x);
    void setY(double y);
    V2D normalize();														//!< returns unit vector
    
	//operateurs
    friend V2D operator*(const double& d, const V2D& v); //!< u = d * v
    friend ostream& operator<<(ostream& o, const V2D& v);    //!< "(x,y,z)"
    
    V2D operator+(const V2D& v) const;		//!< u = v + w
    V2D operator-(const V2D& v) const;		//!< u = v - w
    V2D operator*(const double& d) const;			//!< u = v * d
    V2D operator/(const double& d) const;			//!< u = v / w
    double    operator|(const V2D& v) const;       //!< d = v produit scalaire w
    V2D operator-(void) const;						//!< v = -w
    void operator+=(const V2D& v);					//!< v += w
    void operator-=(const V2D& v);					//!< v -= w
    void operator*=(const double d);						//!< v *= d
    void operator/=(const double d);						//!< v /= d
    bool operator==(V2D& v);						//!< v == w
    bool operator!=(V2D& v);						//!< v != w
    
	//attributs
private:
    double x;
    double y;
    double norm();
};

#endif

/*---------------------------------------------------------------------------*/

/*! \class V2D
 \brief Classe vecteur permettant le positionnement par 3 coordonnees.
 */
// EOF
