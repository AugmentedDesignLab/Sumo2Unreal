// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "SumoToUnrealGameModeBase.h"
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
	UClass* Z_Construct_UClass_ASumoToUnrealGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_AGameModeBase,
				(UObject* (*)())Z_Construct_UPackage__Script_SumoToUnreal,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
				{ "IncludePath", "SumoToUnrealGameModeBase.h" },
				{ "ModuleRelativePath", "SumoToUnrealGameModeBase.h" },
				{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<ASumoToUnrealGameModeBase>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&ASumoToUnrealGameModeBase::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900288u,
				nullptr, 0,
				nullptr, 0,
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASumoToUnrealGameModeBase, 2154810942);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASumoToUnrealGameModeBase(Z_Construct_UClass_ASumoToUnrealGameModeBase, &ASumoToUnrealGameModeBase::StaticClass, TEXT("/Script/SumoToUnreal"), TEXT("ASumoToUnrealGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASumoToUnrealGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
