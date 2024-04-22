#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMeshActor_Copied.generated.h"


UCLASS()
class TOY_API ACMeshActor_Copied : public AActor
{
	GENERATED_BODY()

public:
	ACMeshActor_Copied();

	virtual void OnConstruction(const FTransform& Transform) override;


protected:
	virtual void BeginPlay() override;


public:
	void SetPositions(const TArray<FVector>& InPositions);
	void SetIndices(const TArray<int32>& InIndices);
	void SetNormals(const TArray<FVector>& InNormals);
	void SetUVs(const TArray<FVector2D>& InUVs);
	void SetColors(const TArray<FColor>& InColors);


private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* ProcMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceConstant* Material;


private:
	TArray<FVector> Positions;
	TArray<int32> Indices;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FColor> Colors;

};
