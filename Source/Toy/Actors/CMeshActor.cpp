#include "CMeshActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACMeshActor::ACMeshActor()
{
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");

	UStaticMesh* meshAsset;
	CHelpers::GetAsset<UStaticMesh>(&meshAsset, "StaticMesh'/Game/ThirdPerson/Meshes/Linear_Stair_StaticMesh.Linear_Stair_StaticMesh'");
	Mesh->SetStaticMesh(meshAsset);

	UMaterialInstanceConstant* materialAsset;
	CHelpers::GetAsset<UMaterialInstanceConstant>(&materialAsset, "MaterialInstanceConstant'/Game/Materials/MAT_Master_Inst.MAT_Master_Inst'");
	
	Material = materialAsset;
	Mesh->SetMaterial(0, Material);
}

void ACMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

#if WITH_EDITOR
void ACMeshActor::ShuffleMaterial()
{
	int32 random = UKismetMathLibrary::RandomIntegerInRange(0, (int32)EMaterialType::Max - 1);

	//Texture Params
	for (const FTextureParameterValue texture : Material->TextureParameterValues)
	{
		if (texture.ParameterInfo.Name.Compare("BaseMap") == 0)
			Material->SetTextureParameterValueEditorOnly(texture.ParameterInfo, MaterialParams[random].BaseMap);

		if (texture.ParameterInfo.Name.Compare("RoughnessMap") == 0)
			Material->SetTextureParameterValueEditorOnly(texture.ParameterInfo, MaterialParams[random].RoughnessMap);

		if (texture.ParameterInfo.Name.Compare("NormalMap") == 0)
			Material->SetTextureParameterValueEditorOnly(texture.ParameterInfo, MaterialParams[random].NormalMap);
	}


	//Scalar Params
	for (const FScalarParameterValue scalar : Material->ScalarParameterValues)
	{
		if (scalar.ParameterInfo.Name.Compare("Metallic") == 0)
			Material->SetScalarParameterValueEditorOnly(scalar.ParameterInfo, MaterialParams[random].Metallic);

		if (scalar.ParameterInfo.Name.Compare("Roughness_Min") == 0)
			Material->SetScalarParameterValueEditorOnly(scalar.ParameterInfo, MaterialParams[random].RoughnessMin);

		if (scalar.ParameterInfo.Name.Compare("Roughness_Max") == 0)
			Material->SetScalarParameterValueEditorOnly(scalar.ParameterInfo, MaterialParams[random].RoughnessMax);
	}
}
#endif

