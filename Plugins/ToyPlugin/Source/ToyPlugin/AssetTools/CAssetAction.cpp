#include "CAssetAction.h"
#include "CDataAsset.h"


FCAssetAction::FCAssetAction(EAssetTypeCategories::Type InCategory)
	:Category(InCategory)
{
}


FText FCAssetAction::GetName() const
{
	return FText::FromString("Awesome DataAsset");
}


UClass* FCAssetAction::GetSupportedClass() const
{
	return UCDataAsset::StaticClass();
}


FColor FCAssetAction::GetTypeColor() const
{
	return FColor::Red;
}


uint32 FCAssetAction::GetCategories()
{
	return Category;
}
