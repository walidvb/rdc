/*---------------------------------------------------------------
 
 Creation:	21.03.2007
 Description:		2 dimension vector class
 Methodes:			Construct/Destruct
                    get & set coordonnees
                    regular operators
 ---------------------------------------------------------------*/

#ifndef V2Dh
#define V2Dh

#include <iostream>
#include <cmath>

using namespace std;

class V2D
{
public:
	//Constructors
	
    V2D();
    V2D(float x, float y);
    V2D( V2D const& v);
    ~V2D() {}
    
public:
    void getCoords(float& x, float& y) const;
    void setCoords(float x, float y);
    
    float getNorm() const ;													//!< returns ||v||^2
    float getX() const  ;
    float getY() const ;
    void setX(float x);
    void setY(float y);
    V2D normalize();														//!< returns unit vector
    
	//operators
    friend V2D operator*(const float& d, const V2D& v); //!< u = d * v
    friend ostream& operator<<(ostream& o, const V2D& v);    //!< "(x,y,z)"
    
    V2D operator+(const V2D& v) const;		//!< u = v + w
    V2D operator-(const V2D& v) const;		//!< u = v - w
    V2D operator*(const float& d) const;			//!< u = v * d
    V2D operator/(const float& d) const;			//!< u = v / w
    float    operator|(const V2D& v) const;       //!< d = v produit scalaire w
    V2D operator-(void) const;						//!< v = -w
    void operator+=(const V2D& v);					//!< v += w
    void operator-=(const V2D& v);					//!< v -= w
    void operator*=(const float d);						//!< v *= d
    void operator/=(const float d);						//!< v /= d
    bool operator==(V2D& v);						//!< v == w
    bool operator!=(V2D& v);						//!< v != w
    
	//attributes
private:
    float x;
    float y;
    float norm();
};

#endif

/*---------------------------------------------------------------------------*/

// EOF
