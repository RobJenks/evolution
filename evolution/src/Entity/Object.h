#pragma once

#include "Component.h"


namespace Components
{

	class Object : public Component
	{
	public:

		virtual auto write_dna(DnaWriter& writer) const -> void;

	};

}