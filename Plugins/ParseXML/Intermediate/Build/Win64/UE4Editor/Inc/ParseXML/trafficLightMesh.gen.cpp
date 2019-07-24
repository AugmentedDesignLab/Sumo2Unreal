// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ParseXML/Public/trafficLightMesh.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodetrafficLightMesh() {}
// Cross Module References
	PARSEXML_API UClass* Z_Construct_UClass_AtrafficLightMesh_NoRegister();
	PARSEXML_API UClass* Z_Construct_UClass_AtrafficLightMesh();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_ParseXML();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	void AtrafficLightMesh::StaticRegisterNativesAtrafficLightMesh()
	{
	}
	UClass* Z_Construct_UClass_AtrafficLightMesh_NoRegister()
	{
		return AtrafficLightMesh::StaticClass();
	}
	struct Z_Construct_UClass_AtrafficLightMesh_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_trafficLightComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_trafficLightComponent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AtrafficLightMesh_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ParseXML,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AtrafficLightMesh_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "trafficLightMesh.h" },
		{ "ModuleRelativePath", "Public/trafficLightMesh.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AtrafficLightMesh_Statics::NewProp_trafficLightComponent_MetaData[] = {
		{ "Category", "trafficLightMesh" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/trafficLightMesh.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AtrafficLightMesh_Statics::NewProp_trafficLightComponent = { UE4CodeGen_Private::EPropertyClass::Object, "trafficLightComponent", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000080009, 1, nullptr, STRUCT_OFFSET(AtrafficLightMesh, trafficLightComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AtrafficLightMesh_Statics::NewProp_trafficLightComponent_MetaData, ARRAY_COUNT(Z_Construct_UClass_AtrafficLightMesh_Statics::NewProp_trafficLightComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AtrafficLightMesh_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AtrafficLightMesh_Statics::NewProp_trafficLightComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AtrafficLightMesh_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AtrafficLightMesh>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AtrafficLightMesh_Statics::ClassParams = {
		&AtrafficLightMesh::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x009000A0u,
		nullptr, 0,
		Z_Construct_UClass_AtrafficLightMesh_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UClass_AtrafficLightMesh_Statics::PropPointers),
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_AtrafficLightMesh_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AtrafficLightMesh_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AtrafficLightMesh()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AtrafficLightMesh_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AtrafficLightMesh, 3138462961);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AtrafficLightMesh(Z_Construct_UClass_AtrafficLightMesh, &AtrafficLightMesh::StaticClass, TEXT("/Script/ParseXML"), TEXT("AtrafficLightMesh"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AtrafficLightMesh);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
