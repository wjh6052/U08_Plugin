#include "DebuggerCategory.h"
#include "GameFramework/Character.h"
#include "CanvasItem.h"
#include "GameFramework/PlayerController.h"

FDebuggerCategory::FDebuggerCategory()
{
}

FDebuggerCategory::~FDebuggerCategory()
{
}

void FDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);

	ACharacter* player = OwnerPC->GetPawn<ACharacter>();
	
	//Player
	{
		PlayerCharacterData.Name = player->GetName();
		PlayerCharacterData.Location = player->GetActorLocation();
		PlayerCharacterData.Forward = player->GetActorForwardVector();
	}

	//Forward
	{
		FHitResult hitResult;

		FVector start = player->GetActorLocation();
		FVector end = start + player->GetActorForwardVector() * 1e+4f;

		FCollisionQueryParams param;
		param.AddIgnoredActor(player);

		player->GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, param);

		if (hitResult.IsValidBlockingHit())
		{
			ForwardActorData.Name = hitResult.GetActor()->GetName();
			ForwardActorData.Location = hitResult.GetActor()->GetActorLocation();
			ForwardActorData.Forward = hitResult.GetActor()->GetActorForwardVector();
		}
		else
		{
			ForwardActorData.Name = "";
			ForwardActorData.Location = FVector::ZeroVector;
			ForwardActorData.Forward = FVector::ZeroVector;

		}
	}

	//DebuggerActor
	if (!!DebugActor)
	{
		DebuggerActorData.Name = DebugActor->GetName();
		DebuggerActorData.Location = DebugActor->GetActorLocation();
		DebuggerActorData.Forward = DebugActor->GetActorForwardVector();
	}
	else
	{
		DebuggerActorData.Name = "";
		DebuggerActorData.Location = FVector::ZeroVector;
		DebuggerActorData.Forward = FVector::ZeroVector;
	}
}

void FDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);

	FCanvasTileItem item(FVector2D(10, 10), FVector2D(300, 215), FLinearColor(0, 0, 0, 0.5f));
	item.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend;
	CanvasContext.DrawItem(item, CanvasContext.CursorX, CanvasContext.CursorY);

	CanvasContext.Printf(FColor::Green, L"--Player Data--");
	CanvasContext.Printf(FColor::White, L"	Name : %s", *PlayerCharacterData.Name);
	CanvasContext.Printf(FColor::White, L"	Location : %s", *PlayerCharacterData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"	Forward : %s", *PlayerCharacterData.Forward.ToString());
	CanvasContext.Printf(FColor::White, L"");

	CanvasContext.Printf(FColor::Green, L"--Forward Actor--");
	CanvasContext.Printf(FColor::White, L"	Name : %s", *ForwardActorData.Name);
	CanvasContext.Printf(FColor::White, L"	Location : %s", *ForwardActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"	Forward : %s", *ForwardActorData.Forward.ToString());
	CanvasContext.Printf(FColor::White, L"");

	CanvasContext.Printf(FColor::Green, L"--Debugger Actor--");
	CanvasContext.Printf(FColor::White, L"	Name : %s", *DebuggerActorData.Name);
	CanvasContext.Printf(FColor::White, L"	Location : %s", *DebuggerActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"	Forward : %s", *DebuggerActorData.Forward.ToString());
}

TSharedRef<FGameplayDebuggerCategory> FDebuggerCategory::MakeInstance()
{
	return MakeShareable(new FDebuggerCategory());
}
