#include <stdexcept>
#include <algorithm>
#include "simple_substitution_cipher.h"

SimpleSubstitutionCipher::SimpleSubstitutionCipher( const std::string& srcAlphabet, const std::string& dstAlphabet )
: srcAlphabet_( srcAlphabet ), dstAlphabet_( dstAlphabet )
{
     validateAlphabets();
}


std::string SimpleSubstitutionCipher::cryptText( const std::string& openText )
{
     std::string result;
     /// проходимся по всем символам и выполняем шифрование -> сопоставляем каждый символ из исходного алфавита в символы 'целевого' алфавита
     /// сопоставление происходит по индексу символа из исходного алфавита в 'целевой'
     for( char sym: openText )
     {
          size_t idx = srcAlphabet_.find( sym );
          if( idx == std::string::npos )
          {
               throw std::runtime_error( std::string( "Symbol " ) + sym + " does not contain in source alphabet" );
          }
          result += dstAlphabet_[ idx ];
     }

     return result;
}


std::string SimpleSubstitutionCipher::decryptText( const std::string& cryptedText )
{
     std::string result;
     /// выполняем обратное преобразование относительно того преобразования, которое было в методе cryptText
     for( char sym: cryptedText )
     {
          size_t idx = dstAlphabet_.find( sym );
          if( idx == std::string::npos )
          {
               throw std::runtime_error( std::string( "Symbol " ) + sym + " does not contain in destination alphabet" );
          }
          result += srcAlphabet_[ idx ];
     }
     return result;
}


std::string SimpleSubstitutionCipher::cryptText( const std::string& srcAlphabet, const std::string& dstAlphabet,
                                                 const std::string& openText )
{
     SimpleSubstitutionCipher cipher( srcAlphabet, dstAlphabet );
     return cipher.cryptText( openText );
}


std::string SimpleSubstitutionCipher::decryptText( const std::string& srcAlphabet, const std::string& dstAlphabet,
                                                   const std::string& cryptedText )
{
     SimpleSubstitutionCipher cipher( srcAlphabet, dstAlphabet );
     return cipher.decryptText( cryptedText );
}


void SimpleSubstitutionCipher::validateAlphabets()
{
     if( repeatExists( srcAlphabet_ ))
     {
          throw std::runtime_error( "In source alphabet exists repeat of symbol!" );
     }
     if( repeatExists( dstAlphabet_ ) )
     {
          throw std::runtime_error( "In destination alphabet exists repeat of symbol!" );
     }
     if( srcAlphabet_.size() != dstAlphabet_.size() )
     {
          throw std::runtime_error( "The size of the source and destination arrays are not the same" );
     }
}


bool SimpleSubstitutionCipher::repeatExists( const std::string& str )
{
     for( char sym: str )
     {
          /// если символ входит в строку больше, чем 1 раз - возращаем true
          if( std::count( str.begin(), str.end(), sym ) != 1 )
          {
               return true;
          }
     }
     return false;
}
