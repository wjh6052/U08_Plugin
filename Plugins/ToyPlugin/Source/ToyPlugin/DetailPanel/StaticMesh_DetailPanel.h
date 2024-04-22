#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"


struct FBinaryData
{
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> UVs;
	TArray<int32> Indices;

	friend FArchive& operator<<(FArchive& InArchive, FBinaryData& InData)
	{
		return InArchive
			<< InData.Positions
			<< InData.Normals
			<< InData.UVs
			<< InData.Colors
			<< InData.Indices;
	}
};



class TOYPLUGIN_API FStaticMesh_DetailPanel : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	
private:
	FReply OnClicked_ShuffleMatrial();
	FReply OnClicked_SaveMesh();

private:
	TArray<TWeakObjectPtr<UObject>> Objects;
};
