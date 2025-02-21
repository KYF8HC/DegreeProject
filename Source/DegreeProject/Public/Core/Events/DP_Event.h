#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DP_Event.generated.h"

UINTERFACE()
class UDP_Event : public UInterface
{
	GENERATED_BODY()


};

class DEGREEPROJECT_API IDP_Event
{
	GENERATED_BODY()

public:
	virtual void OnBegin(bool bFirstTime) = 0;
	virtual void OnUpdate() = 0;
	virtual void OnEnd() = 0;
	virtual bool IsDone() = 0;
	
};
