#pragma once

class Token
{
public:

	typedef unsigned int Type;
	static const size_t	 Size = sizeof(Type);

	static const Type Marker		 = 0xAAAAAAAA;
	
	static const Type ObjectBox		 = 0xAAAABA00;
	static const Type ObjectCapsule  = 0xAAAABA01;
	static const Type ObjectCone	 = 0xAAAABA10;
	static const Type ObjectCylinder = 0xAAAABA11;





};