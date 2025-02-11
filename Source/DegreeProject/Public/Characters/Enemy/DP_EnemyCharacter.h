#pragma once

#include "CoreMinimal.h"
#include "Characters/DP_BaseCharacter.h"
#include "DP_EnemyCharacter.generated.h"

UCLASS()
class DEGREEPROJECT_API ADP_EnemyCharacter : public ADP_BaseCharacter
{
	GENERATED_BODY()

public:
	ADP_EnemyCharacter();

protected:
	virtual void BeginPlay() override;
};
