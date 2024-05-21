#include "affine_recurrent_cipher.h"
#include <stdexcept>


AffineRecurrentCipher::AffineRecurrentCipher( const std::string& alphabet, const std::pair< int64_t, int64_t >& key1,
                                              const std::pair< int64_t, int64_t >& key2 )
:alphabet_( alphabet )
{
     keyList_.push_back( key1 );
     keyList_.push_back( key2 );
}


std::string AffineRecurrentCipher::cryptText( const std::string& openText )
{
     std::string result;
     // проходимся по каждому символу и выполняем его зашифрование по алгоритму афинного рекурентного шифра
     for( int idx = 0; idx < openText.size(); idx++ )
     {
          if( idx >= keyList_.size() )
          {
               // если не первый и не второй элемент -> генерируем ключ из предыдущих двух ключей
               // если ранее ключи были рассчитаны дублирования не произойдет - мы не войдем в блок if и будем использовать ранее сгенерированные
               int64_t a = ( keyList_.rbegin()->first * ( keyList_.rbegin() + 1 )->first ) % ( int64_t )alphabet_.size();
               int64_t b = ( keyList_.rbegin()->second + ( keyList_.rbegin() + 1 )->second ) % ( int64_t )alphabet_.size();
               keyList_.push_back( { a, b } );
          }

          auto key = keyList_[ idx ];
          // проверяем, что обратный элемент для a по mod( n ) существует. Если не существует - будет брошено исключение
          modInverse( key.first, alphabet_.size() );

          size_t symIdx = alphabet_.find( openText[ idx ] );
          if( symIdx == std::string::npos )
          {
               throw std::runtime_error( std::string( "Symbol " ) + openText[ idx ] + " does not contain in source alphabet" );
          }

          int64_t y = ( key.first * symIdx + key.second ) % alphabet_.size();
          result += alphabet_[ y ];
     }
     return result;
}


std::string AffineRecurrentCipher::decryptText( const std::string& cryptedText )
{
     std::string result;
     // проходимся по каждому символу и выполняем его расшифрование по алгоритму афинного шифра
     for( int idx = 0; idx < cryptedText.size(); idx++ )
     {
          if( idx >= keyList_.size() )
          {
               // если не первый и не второй элемент -> генерируем ключ из предыдущих двух ключей
               // если ранее ключи были рассчитаны дублирования не произойдет - мы не войдем в блок if и будем использовать ранее сгенерированные
               int64_t a = ( keyList_.rbegin()->first * ( keyList_.rbegin() + 1 )->first ) % ( int64_t )alphabet_.size();
               int64_t b = ( keyList_.rbegin()->second + ( keyList_.rbegin() + 1 )->second ) % ( int64_t )alphabet_.size();
               keyList_.push_back( { a, b } );
          }

          auto key = keyList_[ idx ];
          // рассчитываем обратный элемент к a. Если обратного элемента не существует - будет брошено исключение
          int64_t reverse_a = modInverse( key.first, alphabet_.size() );

          int64_t symIdx = alphabet_.find( cryptedText[ idx ] );
          if( symIdx == std::string::npos )
          {
               throw std::runtime_error( std::string( "Symbol " ) + cryptedText[ idx ] + " does not contain in source alphabet" );
          }

          // добавление alphabet_.size() ( или n в терминологии семинара ) происходит чтобы избежать отрицательных значений
          int64_t x = ( reverse_a * ( symIdx - key.second + alphabet_.size() ) ) % alphabet_.size();
          result += alphabet_[ x ];
     }
     return result;
}


std::string AffineRecurrentCipher::cryptText( const std::string& alphabet, const std::pair< int64_t, int64_t >& key1,
                                              const std::pair< int64_t, int64_t >& key2, const std::string& openText )
{
     AffineRecurrentCipher cipher( alphabet, key1, key2 );
     return cipher.cryptText( openText );
}


std::string AffineRecurrentCipher::decryptText( const std::string& alphabet, const std::pair< int64_t, int64_t >& key1,
                                                const std::pair< int64_t, int64_t >& key2, const std::string& cryptedText )
{
     AffineRecurrentCipher cipher( alphabet, key1, key2 );
     return cipher.decryptText( cryptedText );
}


std::tuple< int64_t, int64_t, int64_t > AffineRecurrentCipher::extendedGCD( int64_t a, int64_t b )
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


int64_t AffineRecurrentCipher::modInverse( int64_t a, int64_t m )
{
     auto[ g, x, y ] = extendedGCD(a, m);
     if( g != 1 )
     {
          throw std::runtime_error( "There is no inverse element" );
     }
     return ( x % m + m ) % m; // Приведение к положительному числу
}
