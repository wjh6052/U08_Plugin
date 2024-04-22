#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"


class TOYPLUGIN_API FAssetViewer_Viewport_Client : public FEditorViewportClient
{
public:
	FAssetViewer_Viewport_Client(class FPreviewScene* InScene, const TSharedRef<class SAssetViewer_Viewport> InViewport);
};
