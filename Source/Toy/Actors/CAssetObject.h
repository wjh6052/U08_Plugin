#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAssetObject.generated.h"


UCLASS()
class TOY_API UCAssetObject : public UObject
{
	GENERATED_BODY()
	

private:
	UPROPERTY(EditAnywhere)
		FVector Location;

	UPROPERTY(EditAnywhere)
		FName Content = TEXT("HAHA");

	UPROPERTY(EditAnywhere, Category = "Shader", meta = (ClampMax = 1.00, ClampMin = 0.00))
		float Alpha = 0.1f;
};
