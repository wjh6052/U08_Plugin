#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"


class TOYPLUGIN_API SAssetViewer_Viewport : public SEditorViewport, public FGCObject
{
public:
	SAssetViewer_Viewport();

	void Construct(const FArguments& InArgs);


public:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;


protected:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;


private:
	class UStaticMeshComponent* AssetMesh;
	class UStaticMeshComponent* FloorMesh;
};
