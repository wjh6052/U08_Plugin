#include "CMeshActor_Copied.h"
#include "Global.h"

#include "Materials/MaterialInstanceConstant.h"
#include "ProceduralMeshComponent.h"



ACMeshActor_Copied::ACMeshActor_Copied()
{
	bRunConstructionScriptOnDrag = false;

	CHelpers::CreateSceneComponent(this, &ProcMesh, "ProcMesh");
}


void ACMeshActor_Copied::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ProcMesh->CreateMeshSection(0, Positions, Indices, Normals, UVs, Colors, TArray<FProcMeshTangent>(), true);

	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&Material, "MaterialInstanceConstant'/Game/Materials/MAT_Master_Inst.MAT_Master_Inst'");
	ProcMesh->SetMaterial(0, Material);
}


void ACMeshActor_Copied::BeginPlay()
{
	Super::BeginPlay();

}


void ACMeshActor_Copied::SetPositions(const TArray<FVector>& InPositions)
{
	Positions = InPositions;
}


void ACMeshActor_Copied::SetIndices(const TArray<int32>& InIndices)
{
	Indices = InIndices;
}


void ACMeshActor_Copied::SetNormals(const TArray<FVector>& InNormals)
{
	Normals = InNormals;
}


void ACMeshActor_Copied::SetUVs(const TArray<FVector2D>& InUVs)
{
	UVs = InUVs;
}

void ACMeshActor_Copied::SetColors(const TArray<FColor>& InColors)
{
	Colors = InColors;
}


