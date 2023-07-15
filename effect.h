#pragma once
enum class EFFECT_TYPE : short {
	INVALID = -1,
	ADDHP,
	SUBHP,
	MAX
};

enum class EFFECT_TARGET_TYPE : short {
	INVALID = -1,
	SELF,
	ALLY,
	ENEMY,
};