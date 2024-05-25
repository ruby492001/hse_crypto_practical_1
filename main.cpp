#include <iostream>
#include "simple_substitution_cipher.h"
#include "affine_cipher.h"
#include "affine_recurrent_cipher.h"


void print_help()
{
     std::cout << "Usage: program ${crypt/decrypt} ${crypt_type} ${args}" << std::endl;
     std::cout << "substitution_cipher args: src_alphabet dst_alphabet text_to_execute" << std::endl;
     std::cout << "affine_cipher args: alphabet α β text_to_execute" << std::endl;
     std::cout << "affine_recurrent_cipher args: alphabet α1 β1 α2 β2 text_to_execute" << std::endl;
}


int main( int argc, char** argv )
{
     if( argc < 2 )
     {
          std::cout << "Incorrect usage" << std::endl;
          return -1;
     }

     if( std::string( argv[ 1 ] ) == "help" )
     {
          print_help();
          return 0;
     }
     if( argc < 3 )
     {
          std::cout << "Incorrect usage" << std::endl;
          return -1;
     }

     bool isCrypt;    // если true - шифрование, если false - расшифрование
     if( std::string( argv[ 1 ] ) == "crypt" )
     {
          isCrypt = true;
     }
     else if( std::string( argv[ 1 ] ) == "decrypt" )
     {
          isCrypt = false;
     }
     else
     {
          std::cout << "Incorrect usage" << std::endl;
          return -1;
     }

     if( std::string( argv[ 2 ] ) == "substitution_cipher" )
     {
          if( argc < 6 )
          {
               std::cout << "Incorrect usage" << std::endl;
               return -1;
          }
          if( isCrypt )
          {
               std::cout << SimpleSubstitutionCipher::cryptText( argv[ 3 ], argv[ 4 ], argv[ 5 ] );
          }
          else
          {
               std::cout << SimpleSubstitutionCipher::decryptText( argv[ 3 ], argv[ 4 ], argv[ 5 ] );
          }
     }
     else if( std::string( argv[ 2 ] ) == "affine_cipher" )
     {
          if( argc < 7 )
          {
               std::cout << "Incorrect usage" << std::endl;
               return -1;
          }
          if( isCrypt )
          {
               std::cout << AffineCipher::cryptText( argv[ 3 ], { std::stoll( argv[ 4 ] ), std::stoll( argv[ 5 ] ) }, argv[ 6 ]);
          }
          else
          {
               std::cout << AffineCipher::decryptText( argv[ 3 ], { std::stoll( argv[ 4 ] ), std::stoll( argv[ 5 ] ) }, argv[ 6 ]);
          }
     }
     else if( std::string( argv[ 2 ] ) == "affine_recurrent_cipher" )
     {
          if( argc < 9 )
          {
               std::cout << "Incorrect usage" << std::endl;
               return -1;
          }
          if( isCrypt )
          {
               std::cout << AffineRecurrentCipher::cryptText( argv[ 3 ], { std::stoll( argv[ 4 ] ), std::stoll( argv[ 5 ] ) },
                                                              { std::stoll( argv[ 6 ] ), std::stoll( argv[ 7 ] ) }, argv[ 8 ] );
          }
          else
          {
               std::cout << AffineRecurrentCipher::decryptText( argv[ 3 ], { std::stoll( argv[ 4 ] ), std::stoll( argv[ 5 ] ) },
                                                              { std::stoll( argv[ 6 ] ), std::stoll( argv[ 7 ] ) }, argv[ 8 ] );
          }
     }
     else
     {
          std::cout << "Incorrect usage" << std::endl;
          return -1;
     }

     return 0;
}