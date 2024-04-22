#include "IconStyle.h"
#include "Styling/SlateStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FIconStyle> FIconStyle::Instance = nullptr;

TSharedPtr<FIconStyle> FIconStyle::Get()
{
	if (Instance == nullptr)
		Instance = MakeShareable(new FIconStyle());

	return Instance;
}

void FIconStyle::Shutdown()
{
	if (Instance.IsValid())
		Instance.Reset();
}

FIconStyle::FIconStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

	FString path = IPluginManager::Get().FindPlugin("ToyPlugin")->GetBaseDir();
	path /= "Resources";
	StyleSet->SetContentRoot(path);

	RegisterIcon("LoadMesh", path / "Icon.png", LoadMeshIcon);
	RegisterIcon("OpenViewer", path / "Icon2.png", OpenViewerIcon);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

FIconStyle::~FIconStyle()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSetName);
	
	if (StyleSet.IsValid())
		StyleSet.Reset();
}

void FIconStyle::RegisterIcon(const FString& InName, const FString& InPath, FSlateIcon& OutIcon)
{
	FSlateImageBrush* brush = new FSlateImageBrush(InPath, FVector2D(48));

	FString name = StyleSetName.ToString() + "." + InName;
	StyleSet->Set(FName(name), brush);
	
	OutIcon = FSlateIcon(StyleSetName, FName(name));
}