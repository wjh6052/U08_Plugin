#include "AssetViewer.h"
#include "Global.h"


TSharedPtr<FAssetViewer> FAssetViewer::Instance = nullptr;
const static FName ToolkitName = L"AssetViewer";
const static FName ViewportTabID = L"Viewport";
const static FName PreviewTabID = L"Preview";
const static FName DetailsTabID = L"Details";


void FAssetViewer::OpenWindow(UObject* InAsset)
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow(); // 기존의 창닫기

		Instance.Reset();
		Instance = nullptr;
	}
		
	Instance = MakeShareable(new FAssetViewer());
	Instance->OpenWindow_International(InAsset);







}

void FAssetViewer::Shutdown()
{
	if (Instance.IsValid())
		Instance->CloseWindow(); // 기존의 창닫기
}

void FAssetViewer::OpenWindow_International(UObject* InAsset)
{
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("AssetViewer_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			//Toolbar
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			//(대)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->SetSizeCoefficient(0.7f)

				//(중)Viewport
				->Split
				(
					FTabManager::NewStack()
					->AddTab(ViewportTabID, ETabState::OpenedTab)
				)//End(중)(Viewport)

				//(중)
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.3f)
					//(소)Preview
					->Split
					(
						FTabManager::NewStack()
						->AddTab(PreviewTabID, ETabState::OpenedTab)
					)//End(소)Preview


					//(소)Details
					->Split
					(FTabManager::NewStack()
						->AddTab(DetailsTabID, ETabState::OpenedTab)

					)//End(소)Details

				)//End(중)
			)//End(대)
		);




	FAssetEditorToolkit::InitAssetEditor
	(
		EToolkitMode::Standalone,
		TSharedPtr<IToolkitHost>(),
		ToolkitName,
		layout,
		true,
		true,
		InAsset
	);

}

void FAssetViewer::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab tab = FOnSpawnTab::CreateSP(this, &FAssetViewer::Spawn_ViewportTab);
	TabManager->RegisterTabSpawner(ViewportTabID, tab);
}

FName FAssetViewer::GetToolkitFName() const
{
	return ToolkitName;
}

FText FAssetViewer::GetBaseToolkitName() const
{
	return FText::FromName(ToolkitName);
}

FString FAssetViewer::GetWorldCentricTabPrefix() const
{
	return ToolkitName.ToString();
}

FLinearColor FAssetViewer::GetWorldCentricTabColorScale() const
{
	return FLinearColor::Yellow;
}

TSharedRef<SDockTab> FAssetViewer::Spawn_ViewportTab(const FSpawnTabArgs& inArg)
{

	return SNew(SDockTab)
		[
			SNew(SButton)
			.Text(FText::FromString("Test"))
		];
}
