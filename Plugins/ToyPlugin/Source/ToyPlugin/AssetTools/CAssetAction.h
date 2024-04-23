#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "AssetTypeActions_Base.h"


class TOYPLUGIN_API FCAssetAction : public FAssetTypeActions_Base
{
public:
	FCAssetAction(EAssetTypeCategories::Type InCategory);


public:
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type Category;
};
