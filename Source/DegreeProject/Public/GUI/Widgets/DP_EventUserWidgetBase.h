#pragma once

#include "CoreMinimal.h"
#include "DP_MainEventHandlerSubsystem.h"
#include "DP_UserWidgetBase.h"
#include "Core/Events/DP_Event.h"
#include "Core/Events/DP_EventHandler.h"
#include "Kismet/GameplayStatics.h"
#include "DP_EventUserWidgetBase.generated.h"

UCLASS()
class DEGREEPROJECT_API UDP_EventUserWidgetBase : public UDP_UserWidgetBase, public IDP_Event
{
	GENERATED_BODY()

public:
	virtual void OnBegin(bool bFirstTime) override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;
	virtual bool IsDone() override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category="Widget Events")
	void OnBeginBP(bool bFirstTime);

	UFUNCTION(BlueprintImplementableEvent, Category="Widget Events")
	void OnUpdateBP();

	UFUNCTION(BlueprintImplementableEvent, Category="Widget Events")
	void OnEndBP();
};


template <typename WidgetT = UUserWidget, typename OwnerType = UGameInstance>
static WidgetT* CreateAndPushEventWidget(OwnerType OwningObject, TSubclassOf<UUserWidget> UserWidgetClass = WidgetT::StaticClass(),  FName WidgetName = NAME_None)
{
	static_assert(TIsDerivedFrom<WidgetT, UDP_EventUserWidgetBase>::IsDerived, "WidgetT must derive from UDP_EventUserWidgetBase");
	
	if (!UserWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("CreateAndPushEventWidget: UserWidgetClass is null"));
		return nullptr;
	}

	WidgetT* UserWidget = CreateWidget<WidgetT>(OwningObject, UserWidgetClass, WidgetName);
	
	OwningObject->GetSubsystem<UDP_MainEventHandlerSubsystem>()->GetMainEventHandler()->PushEvent(UserWidget);
	
	return UserWidget;
}