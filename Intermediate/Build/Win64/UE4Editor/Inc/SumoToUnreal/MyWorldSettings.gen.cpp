// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "MyWorldSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyWorldSettings() {}
// Cross Module References
	SUMOTOUNREAL_API UClass* Z_Construct_UClass_AMyWorldSettings_NoRegister();
	SUMOTOUNREAL_API UClass* Z_Construct_UClass_AMyWorldSettings();
	ENGINE_API UClass* Z_Construct_UClass_AWorldSettings();
	UPackage* Z_Construct_UPackage__Script_SumoToUnreal();
// End Cross Module References
	void AMyWorldSettings::StaticRegisterNativesAMyWorldSettings()
	{
	}
	UClass* Z_Construct_UClass_AMyWorldSettings_NoRegister()
	{
		return AMyWorldSettings::StaticClass();
	}
	UClass* Z_Construct_UClass_AMyWorldSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_AWorldSettings,
				(UObject* (*)())Z_Construct_UPackage__Script_SumoToUnreal,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Actor Advanced Display Events Object Attachment Info Input Blueprint Layers Tags Replication Input Movement Collision Utilities|Transformation" },
				{ "IncludePath", "MyWorldSettings.h" },
				{ "ModuleRelativePath", "MyWorldSettings.h" },
				{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<AMyWorldSettings>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&AMyWorldSettings::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900284u,
				nullptr, 0,
				nullptr, 0,
				"game",
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AMyWorldSettings, 2575118210);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AMyWorldSettings(Z_Construct_UClass_AMyWorldSettings, &AMyWorldSettings::StaticClass, TEXT("/Script/SumoToUnreal"), TEXT("AMyWorldSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMyWorldSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
