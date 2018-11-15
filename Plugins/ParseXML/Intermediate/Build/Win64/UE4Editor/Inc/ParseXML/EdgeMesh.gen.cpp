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
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
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
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_vertices_MetaData[] = {
				{ "ModuleRelativePath", "Public/EdgeMesh.h" },
			};
#endif
			static const UE4CodeGen_Private::FArrayPropertyParams NewProp_vertices = { UE4CodeGen_Private::EPropertyClass::Array, "vertices", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010800000000000, 1, nullptr, STRUCT_OFFSET(AEdgeMesh, vertices), METADATA_PARAMS(NewProp_vertices_MetaData, ARRAY_COUNT(NewProp_vertices_MetaData)) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_vertices_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "vertices", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_vertices,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_vertices_Inner,
			};
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<AEdgeMesh>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&AEdgeMesh::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900080u,
				nullptr, 0,
				PropPointers, ARRAY_COUNT(PropPointers),
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AEdgeMesh, 607596857);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AEdgeMesh(Z_Construct_UClass_AEdgeMesh, &AEdgeMesh::StaticClass, TEXT("/Script/ParseXML"), TEXT("AEdgeMesh"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEdgeMesh);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
