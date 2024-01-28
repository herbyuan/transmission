#include <iostream>
#include <fstream>
#include <evhttp.h>
#include <string.h>
#include <memory>
#include <vector>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define HTTP_CERT_PEM "D:/cert/cert.pem"
#define HTTP_KEY_PEM "D:/cert/key.pem"

int main()
{
    // CRYPTO_set_mem_functions(reinterpret_cast<void *(*)(size_t, const char *, int)>(MyZeroMalloc), reinterpret_cast<void *(*)(void *, size_t, const char *, int)>(realloc), reinterpret_cast<void (*)(void *, const char *, int)>(free));
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();


    // std::ifstream ifs("D:/cert/cert.pem");
    // std::string content( (std::istreambuf_iterator<char>(ifs) ),
    //                  (std::istreambuf_iterator<char>() ) );
    // std::cout << content << std::endl;
    // ifs.close();

    SSL_CTX* m_ctx = SSL_CTX_new(SSLv23_server_method());
    if(m_ctx == nullptr)
    {
        printf("%s\n", ERR_error_string(ERR_get_error(), NULL));
    }
    
    SSL_CTX_set_security_level(m_ctx, 0);
    if (1 != SSL_CTX_use_certificate_file(m_ctx, HTTP_CERT_PEM, SSL_FILETYPE_PEM))
    {
        printf("SSL_CTX_use_certificate_chain_file fail\n");
        printf("Cannot use Certificate File:%s\n", ERR_error_string(ERR_get_error(), NULL ));
        // ERR_print_errors_fp(stderr);
    }
    else if (1 != SSL_CTX_use_PrivateKey_file(m_ctx, HTTP_KEY_PEM, SSL_FILETYPE_PEM))
    {
        printf("SSL_CTX_use_PrivateKey_file fail\n");
    }
    else if (1 != SSL_CTX_check_private_key(m_ctx))
    {
        printf("SSL_CTX_check_private_key fail\n");
    }

    printf("OK\n");

    return 0;
}