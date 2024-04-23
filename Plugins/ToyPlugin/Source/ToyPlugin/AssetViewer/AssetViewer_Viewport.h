#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class TOYPLUGIN_API SAssetViewer_Viewport : public SEditorViewport, public FGCObject
{
public:
	SAssetViewer_Viewport();

	void Construct(const FArguments& InArgs);

	TSharedRef<class FAdvancedPreviewScene> GetScene();

public:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;



protected:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;


private:
	TSharedPtr<class FAdvancedPreviewScene> Scene;
	TSharedPtr<class FAssetViewer_Viewport_Client> ViewportClient;


private:
	class UStaticMeshComponent* AssetMesh;
	class UStaticMeshComponent* FloorMesh;
};
