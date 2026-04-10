// Copyright Saulo Soares. All rights reserved.

#pragma once

DECLARE_LOG_CATEGORY_EXTERN(LogTDWTechnicalTest, Log, All);

#define TDWTestLog_INFO(FMT, ...) UE_LOG(LogTDWTechnicalTest, Log, (FMT), ##__VA_ARGS__)
#define TDWTestLog_WARNING(FMT, ...) UE_LOG(LogTDWTechnicalTest, Warning, (FMT), ##__VA_ARGS__)
#define TDWTestLog_ERROR(FMT, ...) UE_LOG(LogTDWTechnicalTest, Error, (FMT), ##__VA_ARGS__)
#define TDWTestLog_VERBOSE(FMT, ...) UE_LOG(LogTDWTechnicalTest, Verbose, (FMT), ##__VA_ARGS__)
#define TDWTestLog_VERYVERBOSE(FMT, ...) UE_LOG(LogTDWTechnicalTest, VeryVerbose, (FMT), ##__VA_ARGS__)