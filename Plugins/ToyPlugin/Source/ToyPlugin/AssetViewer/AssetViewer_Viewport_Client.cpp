#include "AssetViewer_Viewport_Client.h"
#include "AssetViewer_Viewport.h"


FAssetViewer_Viewport_Client::FAssetViewer_Viewport_Client(FPreviewScene* InScene, const TSharedRef<SAssetViewer_Viewport> InViewport)
	:FEditorViewportClient(nullptr, InScene, StaticCastSharedRef<SAssetViewer_Viewport>(InViewport))
{
	SetViewMode(VMI_Lit);


	//기본으로 비출 카메라 위치
	SetViewRotation(FRotator(-40, -90, 0));
	SetViewLocationForOrbiting(FVector(0, 0, 75), 1000.0f);

}
