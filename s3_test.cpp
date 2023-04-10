#include <aws/s3/S3Client.h>
#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/transfer/TransferManager.h>
#include <aws/transfer/TransferHandle.h>
#include <iostream>
#include <fstream>

/*
 *  usage: ./s3_test srcFile bucketName destFile region
 *  this function is using tranfer manager to copy a local file to the bucket
 */
int main(int argc, char *argv[])
{
    if(argc != 5){
        std::cout << "usage: ./s3_test srcFile bucketName destFile region\n";
        return 1;
    }
    std::string fileName = argv[1]; //local FileName to be uploaded to s3 bucket
    std::string bucketName = argv[2];  //bucketName, make sure that bucketName exists
    std::string objectName = argv[3];
    std::string region = argv[4];
    Aws::SDKOptions options;
    options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = region;
  
    auto s3_client = std::make_shared<Aws::S3::S3Client>(config);

    auto thread_executor = Aws::MakeShared<Aws::Utils::Threading::DefaultExecutor>("s3_test");
    Aws::Transfer::TransferManagerConfiguration transferConfig(thread_executor.get());
    transferConfig.s3Client = s3_client;
    auto buffer = Aws::MakeShared<Aws::FStream>("PutObjectInputStream", fileName.c_str(), std::ios_base::in | std::ios_base::binary);

    auto transferManager = Aws::Transfer::TransferManager::Create(transferConfig);
    auto transferHandle = transferManager->UploadFile(buffer,
                            bucketName.c_str(), objectName.c_str(), "multipart/form-data",
                            Aws::Map<Aws::String, Aws::String>());
                                                          
    transferHandle->WaitUntilFinished();
    thread_executor = nullptr;
    Aws::ShutdownAPI(options);  
}