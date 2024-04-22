#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

struct FCollectionData
{
	FString Name;
	FVector Location;
	FVector Forward;
};

class TOYPLUGIN_API FDebuggerCategory : public FGameplayDebuggerCategory
{
public:
	FDebuggerCategory();
	~FDebuggerCategory();

public:
	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

	FCollectionData PlayerCharacterData;
	FCollectionData ForwardActorData;
	FCollectionData DebuggerActorData;

};
