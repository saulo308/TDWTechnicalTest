// Copyright Saulo Soares. All rights reserved.

#include "AbilityDataBase.h"
#include "AbilityDataFragment.h"
#include "TDWTechnicalTest/TWDTechnicalTestLogging.h"

const UAbilityDataFragment* UAbilityDataBase::FindFragmentByClass(
	TSubclassOf<UAbilityDataFragment> FragmentClass) const
{
	if (!FragmentClass)
	{
		TDWTestLog_ERROR(TEXT("Can't find invalid fragment class on ability "
			"definition [%s]."), *AbilityUniqueId.ToString());
		return nullptr;
	}

	// Foreach ability fragment, try to find the desired one
	for (const auto& Fragment : AbilityFragments)
	{
		if (!Fragment)
		{
			TDWTestLog_ERROR(TEXT("Invalid fragment found on ability "
				"definition [%s]."), *AbilityUniqueId.ToString());
			continue;
		}
		
		if (Fragment->IsA(FragmentClass))
		{
			return Fragment;
		}
	}

	return nullptr;
}
