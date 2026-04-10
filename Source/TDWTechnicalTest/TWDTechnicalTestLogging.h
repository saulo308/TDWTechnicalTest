// Copyright Saulo Soares. All rights reserved.

#pragma once

DECLARE_LOG_CATEGORY_EXTERN(LogTDWTechnicalTest, Log, All);

#define TWDLog_INFO(FMT, ...) UE_LOG(LogTDWTechnicalTest, Log, (FMT), ##__VA_ARGS__)
#define TWDLog_WARNING(FMT, ...) UE_LOG(LogTDWTechnicalTest, Warning, (FMT), ##__VA_ARGS__)
#define TWDLog_ERROR(FMT, ...) UE_LOG(LogTDWTechnicalTest, Error, (FMT), ##__VA_ARGS__)
#define TWDLog_VERBOSE(FMT, ...) UE_LOG(LogTDWTechnicalTest, Verbose, (FMT), ##__VA_ARGS__)
#define TWDLog_VERYVERBOSE(FMT, ...) UE_LOG(LogTDWTechnicalTest, VeryVerbose, (FMT), ##__VA_ARGS__)