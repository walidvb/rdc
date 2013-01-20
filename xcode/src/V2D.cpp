#include "V2D.h"

//Constructors    -------------------------------------


V2D::V2D()
: x(0), y(0) {}

V2D::V2D(float x, float y)
: x(x), y(y) {}

V2D::V2D(  V2D const& v) {
	*this = v;
}


//get&set methods -------------------------------------

void V2D::getCoords(float& x, float& y) const
{
	x = this->x;
	y = this->y;
}

float V2D::getX() const
{
	return this->x;
}

float V2D::getY() const
{
	return this->y;
}


float V2D::getNorm() const
{
	float norm(x*x + y*y);
	return norm;
}

V2D V2D::normalize()
{
	return (*this)/sqrt(getNorm());
}

void V2D::setCoords(float x, float y)
{
	this->x = x;
	this->y = y;
}

void V2D::setX(float x){
	this->x = x;
}

void V2D::setY(float y){
	
	this->y = y;
}

/*---------------------------------------------------------------------------*/
// internal operators
V2D V2D::operator+(const V2D& v) const
{
	float x,y;
	v.getCoords(x,y);
	return V2D( (this->x+x),(this->y+y) );
}


V2D V2D::operator-(const V2D& v) const
{
	float x,y;
	v.getCoords(x,y);
	
	return V2D( (this->x-x),(this->y-y) );
}

V2D V2D::operator*(const float& d) const
{
	return V2D( (x*d),(y*d) );
}

V2D V2D::operator/(const float& d) const
{
	return V2D( (x/d),(y/d) );
}

float V2D::operator|(const V2D& v) const
{
	float x,y;
	v.getCoords(x,y);
	
	return ( this->x*x + this->y*y );
}


V2D V2D::operator-(void) const
{
	V2D v( (-x) , (-y) );
	return v;
}

void V2D::operator+=(const V2D& v)
{
	float x,y;
	v.getCoords(x,y);
	this->x += x;
	this->y += y;
}

void V2D::operator-=(const V2D& v)
{
	float x,y;
	v.getCoords(x,y);
	this->x -= x;
	this->y -= y;
}

void V2D::operator*=(const float d)
{
	x *= d;
	y *= d;
}

void V2D::operator/=(const float d)
{
	x /= d;
	y /= d;
}



/*---------------------------------------------------------------------------*/
// external operators
V2D operator*(const float& d, const V2D& v)
{
	return (v * d);
}

ostream& operator<<(ostream& o, const V2D& v)
{
	o << " (" << v.x << ", " << v.y << ")";
	return o;
}

bool V2D::operator==(V2D& v)	{
	if (this->x == v.getX() && this->y == v.getY() )
		return true;
	else return false;
}

bool V2D::operator!=(V2D& v)	{
	if (this->x != v.getX() || this->y != v.getY() )
		return true;
	else return false;
}

/*---------------------------------------------------------------------------*/
// EOF
