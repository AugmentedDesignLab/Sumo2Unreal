// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SumoToUnreal/SumoToUnrealGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSumoToUnrealGameModeBase() {}
// Cross Module References
	SUMOTOUNREAL_API UClass* Z_Construct_UClass_ASumoToUnrealGameModeBase_NoRegister();
	SUMOTOUNREAL_API UClass* Z_Construct_UClass_ASumoToUnrealGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_SumoToUnreal();
// End Cross Module References
	void ASumoToUnrealGameModeBase::StaticRegisterNativesASumoToUnrealGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_ASumoToUnrealGameModeBase_NoRegister()
	{
		return ASumoToUnrealGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ASumoToUnrealGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASumoToUnrealGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_SumoToUnreal,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASumoToUnrealGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "SumoToUnrealGameModeBase.h" },
		{ "ModuleRelativePath", "SumoToUnrealGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASumoToUnrealGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASumoToUnrealGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASumoToUnrealGameModeBase_Statics::ClassParams = {
		&ASumoToUnrealGameModeBase::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002A8u,
		METADATA_PARAMS(Z_Construct_UClass_ASumoToUnrealGameModeBase_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ASumoToUnrealGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASumoToUnrealGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASumoToUnrealGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASumoToUnrealGameModeBase, 2603363135);
	template<> SUMOTOUNREAL_API UClass* StaticClass<ASumoToUnrealGameModeBase>()
	{
		return ASumoToUnrealGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASumoToUnrealGameModeBase(Z_Construct_UClass_ASumoToUnrealGameModeBase, &ASumoToUnrealGameModeBase::StaticClass, TEXT("/Script/SumoToUnreal"), TEXT("ASumoToUnrealGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASumoToUnrealGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
