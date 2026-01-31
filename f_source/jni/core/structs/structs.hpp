#pragma once

#include "vectors.hpp"

enum class WeaponType {
    None, // 0
	AK47, // 1
	Vector, // 2
	DesertEagle, // 3
	FAMAS, // 4
	M4A1, // 5
    M40, // 6
	FragGrenade, // 7
	FiveSeven, // 8
	Spas12, // 9
	MP7, // 10
	C4, // 11
	P250, // 12
	M98, // 13
	Knife, // 14
	CX70, // 15
	A91, // 16
	SmokeGrenade, // 17
	Flashbang, // 18
	PP2000, // 19
	MP5K, // 20
	Karambit, // 21
	ButterflyKnife, // 22
	Tec9, // 23
	M1014, // 24
	RFB, // 25
	Glock, // 26
	Uzi, // 27
	FAL, // 28
	Hatchet, // 29
	MP9, // 30
	P90, // 31
	AWP, // 32
	Huntsman, // 33
	Beretta, // 34
	BrassKnuckles, // 35
	USP45, // 36
	TecmixKnife, // 37
	KukriKnife, // 38
	IncendiaryGrenade // 39
};

struct RaycastHit {
    Vector3 m_Point; // 0x10
	Vector3 m_Normal; // 0x1C
	uint m_FaceID; // 0x28
	float m_Distance; // 0x2C
	Vector2 m_UV; // 0x30
	int m_Collider; // 0x38
};

static const char* weapon_names[] = {
	"None", "AK47", "Vector", "DesertEagle", 
	"FAMAS", "M4A1", "M40", "FragGrenade", "FiveSeven", 
	"Spas12", "MP7", "C4", "P250", "M98",
	"Knife", "CX70", "A91", "SmokeGrenade",
	"Flashbang", "PP2000", "MP5K", "Karambit", 
	"ButterflyKnife", "Tec9", "M1014", "RFB", 
	"Glock", "Uzi", "FAL", "Hatchet", "MP9", "P90",
	"AWP", "Huntsman", "Beretta", "BrassKnuckles",
	"USP45", "TecmixKnife", "KukriKnife", "IncendiaryGrenade"
};

static int weapon_id[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
	31, 32, 33, 34, 35, 36, 37, 38, 39
};