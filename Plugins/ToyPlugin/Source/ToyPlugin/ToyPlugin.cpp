#include "ToyPlugin.h"
#include "LevelEditor.h"
#include "GameplayDebugger.h"
#include "AssetToolsModule.h"

#include "Toolbar/ButtonCommand.h"
#include "Toolbar/IconStyle.h"
#include "Actors/CMeshActor.h"
#include "DebuggerCategory/DebuggerCategory.h"
#include "DetailPanel/StaticMesh_DetailPanel.h"
#include "AssetViewer/AssetViewer.h"
#include "AssetTools/CAssetAction.h"

#define LOCTEXT_NAMESPACE "FToyPluginModule"


void FToyPluginModule::StartupModule()
{
	UE_LOG(LogTemp, Error, TEXT("Startup Toy Plugin"));

	//Toolbar
	{
		FIconStyle::Get();

		FButtonCommand::Register();
		Extender = MakeShareable(new FExtender());

		FToolBarExtensionDelegate toolBarLoadMeshDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FToyPluginModule::AddToolBar_LoadMesh);
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().Command, toolBarLoadMeshDelegate);

		FToolBarExtensionDelegate toolBarOpenViewerDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FToyPluginModule::AddToolBar_OpenViewer);
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().Command, toolBarOpenViewerDelegate);

		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
	}

	//GamePlayDebuggerCategory
	{
		IGameplayDebugger::FOnGetCategory makeCategoryInstanceDelegate = IGameplayDebugger::FOnGetCategory::CreateStatic(&FDebuggerCategory::MakeInstance);

		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get();
		gameplayDebugger.Get().RegisterCategory("AwesomeCategory", makeCategoryInstanceDelegate, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
		gameplayDebugger.NotifyCategoriesChanged();
	}

	//DetailPanel
	{
		FPropertyEditorModule& properyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		properyEditor.RegisterCustomClassLayout
		(
			ACMeshActor::StaticClass()->GetFName(),
			FOnGetDetailCustomizationInstance::CreateStatic(&FStaticMesh_DetailPanel::MakeInstance)
		);
	}

	//AssetTools
	{
		IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		EAssetTypeCategories::Type category = assetTools.RegisterAdvancedAssetCategory(NAME_None, FText::FromString("Awesome"));
		AssetTypeAction = MakeShareable(new FCAssetAction(category));
		assetTools.RegisterAssetTypeActions(AssetTypeAction.ToSharedRef());
	}
}

void FToyPluginModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Shutdown Toy Plugin"));


	if (IGameplayDebugger::IsAvailable())
		IGameplayDebugger::Get().UnregisterCategory("AwesomeCategory");

	FIconStyle::Shutdown();
	FAssetViewer::Shutdown();
}

void FToyPluginModule::AddToolBar_LoadMesh(FToolBarBuilder& InBuilder)
{
	InBuilder.AddSeparator();
	InBuilder.AddToolBarButton
	(
		FButtonCommand::Get().LoadMeshID,
		NAME_None,
		FText::FromString("Load Mesh"),
		FText::FromString("Load Mesh Data"),
		FIconStyle::Get()->LoadMeshIcon
	);
}

void FToyPluginModule::AddToolBar_OpenViewer(FToolBarBuilder& InBuilder)
{
	InBuilder.AddToolBarButton
	(
		FButtonCommand::Get().OpenViewerID,
		NAME_None,
		FText::FromString("Open Viewer"),
		FText::FromString("Open Static Mesh Asset Viewer"),
		FIconStyle::Get()->OpenViewerIcon
	);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToyPluginModule, ToyPlugin)