#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"


class TOYPLUGIN_API FAssetViewer : public FAssetEditorToolkit
{
public:
	static void OpenWindow(UObject* InAsset);
	static void Shutdown();


private:
	void OpenWindow_International(UObject* InAsset);


public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

public:
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

private:
	TSharedRef<SDockTab> Spawn_ViewportTab(const FSpawnTabArgs& inArg);


private:
	static TSharedPtr<FAssetViewer> Instance;

};
