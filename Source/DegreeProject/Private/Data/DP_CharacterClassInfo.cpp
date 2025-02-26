#include "Data/DP_CharacterClassInfo.h"

FCharacterClassDefaultInfo UDP_CharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}