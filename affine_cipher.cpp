#include "affine_cipher.h"
#include <stdexcept>


AffineCipher::AffineCipher( const std::string& alphabet, const std::pair< int64_t, int64_t >& key )
:alphabet_( alphabet ), key_( key )
{
}


std::string AffineCipher::cryptText( const std::string& openText )
{
     // проверяем, что обратный элемент для a по mod( n ) существует. Если не существует - будет брошено исключение
     modInverse( key_.first, alphabet_.size() );

     std::string result;
     // проходимся по каждому символу и выполняем его зашифрование по алгоритму афинного шифра
     for( char sym: openText )
     {
          size_t idx = alphabet_.find( sym );
          if( idx == std::string::npos )
          {
               throw std::runtime_error( std::string( "Symbol " ) + sym + " does not contain in source alphabet" );
          }
          int64_t y = ( key_.first * idx + key_.second ) % alphabet_.size();
          result += alphabet_[ y ];
     }
     return result;
}


std::string AffineCipher::decryptText( const std::string& cryptedText )
{
     // рассчитываем обратный элемент к a. Если обратного элемента не существует - будет брошено исключение
     int64_t reverse_a = modInverse( key_.first, alphabet_.size() );

     std::string result;
     // проходимся по каждому символу и выполняем его расшифрование по алгоритму афинного шифра
     for( char sym: cryptedText )
     {
          int64_t idx = alphabet_.find( sym );
          if( idx == std::string::npos )
          {
               throw std::runtime_error( std::string( "Symbol " ) + sym + " does not contain in source alphabet" );
          }

          // добавление alphabet_.size() ( или n в терминологии семинара ) происходит чтобы избежать отрицательных значений
          int64_t x = ( reverse_a * ( idx - key_.second + alphabet_.size() ) ) % alphabet_.size();
          result += alphabet_[ x ];
     }
     return result;
}


std::string AffineCipher::cryptText( const std::string& alphabet, const std::pair< int64_t, int64_t >& key,
                                     const std::string& openText )
{
     AffineCipher cipher( alphabet, key );
     return cipher.cryptText( openText );
}


std::string AffineCipher::decryptText( const std::string& alphabet, const std::pair<int64_t, int64_t>& key,
                                       const std::string& cryptedText )
{
     AffineCipher cipher( alphabet, key );
     return cipher.decryptText( cryptedText );
}


std::tuple< int64_t, int64_t, int64_t > AffineCipher::extendedGCD( int64_t a, int64_t b )
{
     if( b == 0 )
     {
          return { a, 1, 0 };
     }
     auto [ g, x1, y1 ] = extendedGCD( b, a % b );
     int x = y1;
     int y = x1 - ( a / b ) * y1;
     return { g, x, y };
}


int64_t AffineCipher::modInverse( int64_t a, int64_t m )
{
     auto[ g, x, y ] = extendedGCD(a, m);
     if( g != 1 )
     {
          throw std::runtime_error( "There is no inverse element" );
     }
     return ( x % m + m ) % m; // Приведение к положительному числу
}
