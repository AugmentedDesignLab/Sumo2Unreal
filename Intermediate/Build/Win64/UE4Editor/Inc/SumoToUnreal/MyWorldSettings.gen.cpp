// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SumoToUnreal/MyWorldSettings.h"
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
	struct Z_Construct_UClass_AMyWorldSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMyWorldSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AWorldSettings,
		(UObject* (*)())Z_Construct_UPackage__Script_SumoToUnreal,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyWorldSettings_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Actor Advanced Display Events Object Attachment Info Input Blueprint Layers Tags Replication Input Movement Collision Utilities|Transformation" },
		{ "IncludePath", "MyWorldSettings.h" },
		{ "ModuleRelativePath", "MyWorldSettings.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMyWorldSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyWorldSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AMyWorldSettings_Statics::ClassParams = {
		&AMyWorldSettings::StaticClass,
		"game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AMyWorldSettings_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AMyWorldSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMyWorldSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AMyWorldSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AMyWorldSettings, 3226840761);
	template<> SUMOTOUNREAL_API UClass* StaticClass<AMyWorldSettings>()
	{
		return AMyWorldSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AMyWorldSettings(Z_Construct_UClass_AMyWorldSettings, &AMyWorldSettings::StaticClass, TEXT("/Script/SumoToUnreal"), TEXT("AMyWorldSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMyWorldSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
