#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CDataAsset.generated.h"


UCLASS()
class TOYPLUGIN_API UCDataAsset : public UObject
{
	GENERATED_BODY()
	

public:
	FORCEINLINE TSubclassOf<UObject> GetEquipmentClass() { return EquipmentClass; }
	FORCEINLINE class UAnimMontage* GetEquipmentMontage() { return EquipmentMontage; }
	FORCEINLINE float GetPlayRate() { return PlayRate; }
	FORCEINLINE class USkeletalMesh* GetSkeletalMesh() { return SkelMesh; }

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UObject> EquipmentClass;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* EquipmentMontage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		class USkeletalMesh* SkelMesh;




};
