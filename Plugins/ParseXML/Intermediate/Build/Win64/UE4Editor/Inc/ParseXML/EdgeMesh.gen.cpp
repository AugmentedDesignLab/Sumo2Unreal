// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/EdgeMesh.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEdgeMesh() {}
// Cross Module References
	PARSEXML_API UClass* Z_Construct_UClass_AEdgeMesh_NoRegister();
	PARSEXML_API UClass* Z_Construct_UClass_AEdgeMesh();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_ParseXML();
// End Cross Module References
	void AEdgeMesh::StaticRegisterNativesAEdgeMesh()
	{
	}
	UClass* Z_Construct_UClass_AEdgeMesh_NoRegister()
	{
		return AEdgeMesh::StaticClass();
	}
	UClass* Z_Construct_UClass_AEdgeMesh()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_AActor,
				(UObject* (*)())Z_Construct_UPackage__Script_ParseXML,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "EdgeMesh.h" },
				{ "ModuleRelativePath", "Public/EdgeMesh.h" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<AEdgeMesh>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&AEdgeMesh::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900080u,
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
	IMPLEMENT_CLASS(AEdgeMesh, 3640320518);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AEdgeMesh(Z_Construct_UClass_AEdgeMesh, &AEdgeMesh::StaticClass, TEXT("/Script/ParseXML"), TEXT("AEdgeMesh"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEdgeMesh);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
