#pragma once

namespace Token
{
	typedef unsigned int Type;
	static const size_t Size = sizeof(Type);

	enum Value : Type
	{
		Marker					= 0xAAAAAAAA,

		SymmetricBilateral		= 0xAAAABB00,		// Z
		SymmetricDorsoVentral	= 0xAAAABB11,		// Y
		SymmetricLongitudinal	= 0xAAAABB22,		// X

		ObjectBox				= 0xAAAABA00,
		ObjectCapsule			= 0xAAAABA01,
		ObjectCone				= 0xAAAABA10,
		ObjectCylinder			= 0xAAAABA11


	};



};