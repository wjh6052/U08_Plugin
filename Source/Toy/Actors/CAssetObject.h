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
};
